#define _POSIX_C_SOURCE 200809L
#include "../include/semantic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void scope_push(Semantic* s){
    if(s->scope_depth>=MAX_SCOPES-1) return;
    s->scope_depth++;
    s->scopes[s->scope_depth].count=0;
}
static void scope_pop(Semantic* s){
    if(s->scope_depth<=0) return;
    Scope* sc=&s->scopes[s->scope_depth];
    for(int i=0;i<sc->count;i++)
        if(sc->symbols[i].name){ free(sc->symbols[i].name); sc->symbols[i].name=NULL; }
    sc->count=0;
    s->scope_depth--;
}
static int valid_name(const char* n){
    if(!n||!*n||strlen(n)>64) return 0;
    for(int i=0;n[i];i++){
        unsigned char c=(unsigned char)n[i];
        if(!(isalnum(c)||c=='_')) return 0;
    }
    return 1;
}
static void def(Semantic* s,const char* name,SymbolKind k,int ln,int ic){
    if(!valid_name(name)) return;
    Scope* sc=&s->scopes[s->scope_depth];
    for(int i=0;i<sc->count;i++)
        if(sc->symbols[i].name&&strcmp(sc->symbols[i].name,name)==0) return;
    if(sc->count>=MAX_SYMBOLS) return;
    sc->symbols[sc->count].name=strdup(name);
    sc->symbols[sc->count].kind=k;
    sc->symbols[sc->count].line=ln;
    sc->symbols[sc->count].is_const=ic;
    sc->count++;
}
static int lkp(Semantic* s,const char* name){
    if(!valid_name(name)) return 1; // skip invalid
    for(int d=s->scope_depth;d>=0;d--){
        Scope* sc=&s->scopes[d];
        for(int i=0;i<sc->count;i++)
            if(sc->symbols[i].name&&strcmp(sc->symbols[i].name,name)==0)
                return 1;
    }
    return 0;
}

static int is_builtin(const char* n){
    if(!n) return 1;
    static const char* b[]={"print","input","len","str","int","float",
        "type","range","append","Error","sqrt","abs","pow",
        "new","self","none","true","false",NULL};
    for(int i=0;b[i];i++) if(strcmp(n,b[i])==0) return 1;
    return 0;
}

static void ana(Semantic* s,ASTNode* nd);

static void ana_kids(Semantic* s,ASTNode* nd){
    if(!nd) return;
    for(int i=0;i<nd->child_count;i++) ana(s,nd->children[i]);
}

static void ana(Semantic* s,ASTNode* nd){
    if(!nd) return;

    if(nd->type==NODE_PROGRAM){
        for(int i=0;i<nd->child_count;i++){
            ASTNode* c=nd->children[i];
            if(!c) continue;
            if(c->type==NODE_FUNCTION&&valid_name(c->str_val))
                def(s,c->str_val,SYM_FUNCTION,c->line,0);
            if(c->type==NODE_CLASS&&valid_name(c->str_val))
                def(s,c->str_val,SYM_CLASS,c->line,0);
        }
        ana_kids(s,nd); return;
    }

    if(nd->type==NODE_BLOCK){
        scope_push(s); ana_kids(s,nd); scope_pop(s); return;
    }

    if(nd->type==NODE_LET||nd->type==NODE_CONST){
        if(nd->child_count>0) ana(s,nd->children[0]);
        if(valid_name(nd->str_val)) def(s,nd->str_val,SYM_VARIABLE,nd->line,0);
        return;
    }

    if(nd->type==NODE_FUNCTION){
        if(valid_name(nd->str_val)) def(s,nd->str_val,SYM_FUNCTION,nd->line,0);
        scope_push(s);
        def(s,"self",SYM_PARAMETER,nd->line,0);
        for(int i=0;i<nd->child_count-1;i++){
            ASTNode* p=nd->children[i];
            if(p&&p->type==NODE_IDENT&&valid_name(p->str_val))
                def(s,p->str_val,SYM_PARAMETER,nd->line,0);
        }
        if(nd->child_count>0) ana(s,nd->children[nd->child_count-1]);
        scope_pop(s); return;
    }

    if(nd->type==NODE_CLASS){
        if(valid_name(nd->str_val)) def(s,nd->str_val,SYM_CLASS,nd->line,0);
        scope_push(s);
        for(int i=0;i<nd->child_count;i++){
            ASTNode* c=nd->children[i];
            if(c&&c->type==NODE_FUNCTION&&valid_name(c->str_val)){
                def(s,c->str_val,SYM_FUNCTION,c->line,0);
                // Register method globally too
                def(&(Semantic){.scope_depth=0},c->str_val,SYM_FUNCTION,c->line,0);
            }
        }
        const char* flds[]={"value","name","size","count","data","title",
            "done","priority","age","score","x","y","z","id","text",
            "msg","result","width","height",NULL};
        for(int i=0;flds[i];i++) def(s,flds[i],SYM_VARIABLE,nd->line,0);
        ana_kids(s,nd); scope_pop(s); return;
    }

    if(nd->type==NODE_IDENT){
        if(!valid_name(nd->str_val)) return;
        if(strcmp(nd->str_val,"self") ==0) return;
        if(strcmp(nd->str_val,"none") ==0) return;
        if(strcmp(nd->str_val,"true") ==0) return;
        if(strcmp(nd->str_val,"false")==0) return;
        if(!lkp(s,nd->str_val)){
            fprintf(stderr,"\n[HOLEXA ERROR HLX202] Line %d: Undefined variable '%s'\n\n",
                nd->line,nd->str_val);
            s->error_count++;
        }
        return;
    }

    // Dot chain — skip right side (method/field name)
    if(nd->type==NODE_BINOP&&nd->str_val&&strcmp(nd->str_val,".")==0){
        if(nd->child_count>0) ana(s,nd->children[0]);
        // skip right side — method names are always valid
        return;
    }

    if(nd->type==NODE_CALL){
        if(valid_name(nd->str_val)&&!is_builtin(nd->str_val)&&!lkp(s,nd->str_val)){
            fprintf(stderr,"\n[HOLEXA WARNING HLX301] Line %d: Function '%s' may not be defined\n\n",
                nd->line,nd->str_val);
            s->warning_count++;
        }
        ana_kids(s,nd); return;
    }

    if(nd->type==NODE_FOR){
        scope_push(s);
        if(valid_name(nd->str_val)) def(s,nd->str_val,SYM_VARIABLE,nd->line,0);
        ana_kids(s,nd); scope_pop(s); return;
    }

    if(nd->type==NODE_TRY){
        scope_push(s);
        def(s,"err",SYM_VARIABLE,nd->line,0);
        ana_kids(s,nd); scope_pop(s); return;
    }

    ana_kids(s,nd);
}

Semantic* semantic_new(void){
    Semantic* s=malloc(sizeof(Semantic));
    s->scope_depth=0; s->error_count=0; s->warning_count=0;
    for(int i=0;i<MAX_SCOPES;i++) s->scopes[i].count=0;
    const char* fns[]={"print","input","len","str","int","float","type",
        "range","append","Error","sqrt","abs","pow","new",NULL};
    for(int i=0;fns[i];i++) def(s,fns[i],SYM_FUNCTION,0,0);
    def(s,"true", SYM_VARIABLE,0,1);
    def(s,"false",SYM_VARIABLE,0,1);
    def(s,"none", SYM_VARIABLE,0,1);
    return s;
}
void semantic_analyze(Semantic* s,ASTNode* nd){ ana(s,nd); }
void semantic_free(Semantic* s){
    if(!s) return;
    for(int d=0;d<=s->scope_depth;d++){
        Scope* sc=&s->scopes[d];
        for(int i=0;i<sc->count;i++)
            if(sc->symbols[i].name){ free(sc->symbols[i].name); sc->symbols[i].name=NULL; }
    }
    free(s);
}
