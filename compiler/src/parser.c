#define _POSIX_C_SOURCE 200809L
#include "../include/parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void adv(Parser* p){
    if(p->previous) token_free(p->previous);
    p->previous=p->current;
    p->current=lexer_next_token(p->lexer);
}
static int chk(Parser* p,TokenType t){ return p->current->type==t; }
static int mat(Parser* p,TokenType t){ if(chk(p,t)){adv(p);return 1;}return 0; }

static Token* exp_tok(Parser* p,TokenType type,const char* msg){
    if(!chk(p,type)){
        fprintf(stderr,"\n[HOLEXA ERROR HLX100] Line %d: %s\n",p->current->line,msg);
        fprintf(stderr,"  Expected: %s\n",token_type_name(type));
        fprintf(stderr,"  Found:    %s ('%s')\n\n",
            token_type_name(p->current->type),p->current->value);
        p->had_error=1;
        return p->current;
    }
    adv(p);
    return p->previous;
}

static ASTNode* parse_stmt(Parser* p);
static ASTNode* parse_expr(Parser* p);
static ASTNode* parse_blk(Parser* p);

static ASTNode* parse_blk(Parser* p){
    int ln=p->current->line;
    exp_tok(p,TOK_LBRACE,"Expected '{'");
    ASTNode* blk=ast_node_new(NODE_BLOCK,ln);
    while(!chk(p,TOK_RBRACE)&&!chk(p,TOK_EOF)){
        ASTNode* s=parse_stmt(p);
        if(s) ast_node_add_child(blk,s);
    }
    exp_tok(p,TOK_RBRACE,"Expected '}'");
    return blk;
}

static ASTNode* parse_dot_chain(Parser* p, ASTNode* left, int ln){
    while(mat(p,TOK_DOT)){
        Token* mbr=exp_tok(p,TOK_IDENT,"Expected name after '.'");
        ASTNode* dt=ast_node_new(NODE_BINOP,ln);
        dt->str_val=strdup(".");
        ast_node_add_child(dt,left);
        if(mat(p,TOK_LPAREN)){
            ASTNode* mc=ast_node_new(NODE_CALL,ln);
            mc->str_val=strdup(mbr->value);
            while(!chk(p,TOK_RPAREN)&&!chk(p,TOK_EOF)){
                ast_node_add_child(mc,parse_expr(p));
                if(!chk(p,TOK_RPAREN)) exp_tok(p,TOK_COMMA,"Expected ','");
            }
            exp_tok(p,TOK_RPAREN,"Expected ')'");
            ast_node_add_child(dt,mc);
        } else {
            ASTNode* fld=ast_node_new(NODE_IDENT,ln);
            fld->str_val=strdup(mbr->value);
            ast_node_add_child(dt,fld);
        }
        left=dt;
    }
    return left;
}

static ASTNode* parse_primary(Parser* p){
    int ln=p->current->line;

    if(chk(p,TOK_MINUS)){
        adv(p);
        if(chk(p,TOK_INT)){
            ASTNode* nd=ast_node_new(NODE_INT,ln);
            nd->int_val=-atoll(p->current->value);
            adv(p); return nd;
        }
        if(chk(p,TOK_FLOAT)){
            ASTNode* nd=ast_node_new(NODE_FLOAT,ln);
            nd->float_val=-atof(p->current->value);
            adv(p); return nd;
        }
        ASTNode* neg=ast_node_new(NODE_UNOP,ln);
        neg->str_val=strdup("-");
        ast_node_add_child(neg,parse_primary(p));
        return neg;
    }

    if(mat(p,TOK_INT)){
        ASTNode* nd=ast_node_new(NODE_INT,ln);
        nd->int_val=atoll(p->previous->value); return nd;
    }
    if(mat(p,TOK_FLOAT)){
        ASTNode* nd=ast_node_new(NODE_FLOAT,ln);
        nd->float_val=atof(p->previous->value); return nd;
    }
    if(mat(p,TOK_STRING)){
        ASTNode* nd=ast_node_new(NODE_STRING,ln);
        nd->str_val=strdup(p->previous->value); return nd;
    }
    if(mat(p,TOK_TRUE)) { ASTNode* nd=ast_node_new(NODE_BOOL,ln); nd->bool_val=1; return nd; }
    if(mat(p,TOK_FALSE)){ ASTNode* nd=ast_node_new(NODE_BOOL,ln); nd->bool_val=0; return nd; }
    if(mat(p,TOK_NONE))  return ast_node_new(NODE_NONE,ln);

    if(mat(p,TOK_SELF)){
        ASTNode* nd=ast_node_new(NODE_IDENT,ln);
        nd->str_val=strdup("self");
        return parse_dot_chain(p,nd,ln);
    }

    if(mat(p,TOK_IDENT)){
        char* nm=strdup(p->previous->value);
        ASTNode* nd;
        if(mat(p,TOK_LPAREN)){
            nd=ast_node_new(NODE_CALL,ln);
            nd->str_val=nm;
            while(!chk(p,TOK_RPAREN)&&!chk(p,TOK_EOF)){
                ast_node_add_child(nd,parse_expr(p));
                if(!chk(p,TOK_RPAREN)) exp_tok(p,TOK_COMMA,"Expected ','");
             }
            exp_tok(p,TOK_RPAREN,"Expected ')'");
        } else {
            nd=ast_node_new(NODE_IDENT,ln);
            nd->str_val=nm;
        }
        return parse_dot_chain(p,nd,ln);
    }

    if(mat(p,TOK_LPAREN)){
        ASTNode* e=parse_expr(p);
        exp_tok(p,TOK_RPAREN,"Expected ')'");
        return e;
    }

    fprintf(stderr,"[HOLEXA ERROR HLX101] Line %d: Unexpected token '%s'\n",
        ln,p->current->value);
    p->had_error=1;
    adv(p);
    return ast_node_new(NODE_NONE,ln);
}

static ASTNode* parse_mul(Parser* p){
    ASTNode* lft=parse_primary(p);
    while(chk(p,TOK_STAR)||chk(p,TOK_SLASH)||chk(p,TOK_PERCENT)){
        char* op=strdup(p->current->value);
        int ln=p->current->line; adv(p);
        ASTNode* b=ast_node_new(NODE_BINOP,ln);
        b->str_val=op;
        ast_node_add_child(b,lft);
        ast_node_add_child(b,parse_primary(p));
        lft=b;
    }
    return lft;
}

static ASTNode* parse_add(Parser* p){
    ASTNode* lft=parse_mul(p);
    while(chk(p,TOK_PLUS)||chk(p,TOK_MINUS)){
        char* op=strdup(p->current->value);
        int ln=p->current->line; adv(p);
        ASTNode* b=ast_node_new(NODE_BINOP,ln);
        b->str_val=op;
        ast_node_add_child(b,lft);
        ast_node_add_child(b,parse_mul(p));
        lft=b;
    }
    return lft;
}

static ASTNode* parse_cmp(Parser* p){
    ASTNode* lft=parse_add(p);
    while(chk(p,TOK_EQ)||chk(p,TOK_NEQ)||chk(p,TOK_LT)||
          chk(p,TOK_GT)||chk(p,TOK_LTE)||chk(p,TOK_GTE)){
        char* op=strdup(p->current->value);
        int ln=p->current->line; adv(p);
        ASTNode* b=ast_node_new(NODE_BINOP,ln);
        b->str_val=op;
        ast_node_add_child(b,lft);
        ast_node_add_child(b,parse_add(p));
        lft=b;
    }
    return lft;
}

static ASTNode* parse_expr(Parser* p){
    ASTNode* lft=parse_cmp(p);
    while(chk(p,TOK_AND)||chk(p,TOK_OR)){
        char* op=strdup(p->current->value);
        int ln=p->current->line; adv(p);
        ASTNode* b=ast_node_new(NODE_BINOP,ln);
        b->str_val=op;
        ast_node_add_child(b,lft);
        ast_node_add_child(b,parse_cmp(p));
        lft=b;
    }
    return lft;
}

static ASTNode* parse_let(Parser* p){
    int ln=p->previous->line;
    Token* nm=exp_tok(p,TOK_IDENT,"Expected variable name");
    ASTNode* nd=ast_node_new(NODE_LET,ln);
    nd->str_val=strdup(nm->value);
    if(mat(p,TOK_COLON)) adv(p);
    exp_tok(p,TOK_ASSIGN,"Expected '='");
    ast_node_add_child(nd,parse_expr(p));
    return nd;
}

static ASTNode* parse_const(Parser* p){
    int ln=p->previous->line;
    Token* nm=exp_tok(p,TOK_IDENT,"Expected const name");
    ASTNode* nd=ast_node_new(NODE_CONST,ln);
    nd->str_val=strdup(nm->value);
    if(mat(p,TOK_COLON)) adv(p);
    exp_tok(p,TOK_ASSIGN,"Expected '='");
    ast_node_add_child(nd,parse_expr(p));
    return nd;
}

static ASTNode* parse_fn(Parser* p){
    int ln=p->previous->line;
    Token* nm=exp_tok(p,TOK_IDENT,"Expected function name");
    ASTNode* nd=ast_node_new(NODE_FUNCTION,ln);
    nd->str_val=strdup(nm->value);
    exp_tok(p,TOK_LPAREN,"Expected '('");
    while(!chk(p,TOK_RPAREN)&&!chk(p,TOK_EOF)){
        if(chk(p,TOK_IDENT)||chk(p,TOK_SELF)){
            ASTNode* prm=ast_node_new(NODE_IDENT,ln);
            prm->str_val=strdup(p->current->value);
            ast_node_add_child(nd,prm);
            adv(p);
        }
        if(mat(p,TOK_COLON)) adv(p);
        if(chk(p,TOK_COMMA)) adv(p);
    }
    exp_tok(p,TOK_RPAREN,"Expected ')'");
    if(mat(p,TOK_ARROW)) adv(p);
    ast_node_add_child(nd,parse_blk(p));
    return nd;
}

static ASTNode* parse_class(Parser* p){
    int ln=p->previous->line;
    Token* nm=exp_tok(p,TOK_IDENT,"Expected class name");
    ASTNode* nd=ast_node_new(NODE_CLASS,ln);
    nd->str_val=strdup(nm->value);
    exp_tok(p,TOK_LBRACE,"Expected '{'");
    while(!chk(p,TOK_RBRACE)&&!chk(p,TOK_EOF)){
        if(mat(p,TOK_FN)){
            ast_node_add_child(nd,parse_fn(p));
        } else if(chk(p,TOK_IDENT)){
            adv(p);
            if(mat(p,TOK_COLON)) adv(p);
        } else { adv(p); }
    }
    exp_tok(p,TOK_RBRACE,"Expected '}'");
    return nd;
}

static ASTNode* parse_if(Parser* p){
    int ln=p->previous->line;
    ASTNode* nd=ast_node_new(NODE_IF,ln);
    ast_node_add_child(nd,parse_expr(p));
    ast_node_add_child(nd,parse_blk(p));
    if(mat(p,TOK_ELSE)){
        if(mat(p,TOK_IF)) ast_node_add_child(nd,parse_if(p));
        else ast_node_add_child(nd,parse_blk(p));
    }
    return nd;
}

static ASTNode* parse_while(Parser* p){
    int ln=p->previous->line;
    ASTNode* nd=ast_node_new(NODE_WHILE,ln);
    ast_node_add_child(nd,parse_expr(p));
    ast_node_add_child(nd,parse_blk(p));
    return nd;
}

static ASTNode* parse_for(Parser* p){
    int ln=p->previous->line;
    Token* vr=exp_tok(p,TOK_IDENT,"Expected variable in 'for'");
    ASTNode* nd=ast_node_new(NODE_FOR,ln);
    nd->str_val=strdup(vr->value);
    exp_tok(p,TOK_IN,"Expected 'in'");
    ast_node_add_child(nd,parse_expr(p));
    if(mat(p,TOK_DOTDOT)) ast_node_add_child(nd,parse_expr(p));
    ast_node_add_child(nd,parse_blk(p));
    return nd;
}

static ASTNode* parse_try(Parser* p){
    int ln=p->previous->line;
    ASTNode* nd=ast_node_new(NODE_TRY,ln);
    ast_node_add_child(nd,parse_blk(p));
    if(mat(p,TOK_CATCH)){
        if(chk(p,TOK_IDENT)) adv(p);
        ast_node_add_child(nd,parse_blk(p));
    }
    if(mat(p,TOK_FINALLY)) ast_node_add_child(nd,parse_blk(p));
    return nd;
}

static ASTNode* parse_stmt(Parser* p){
    if(mat(p,TOK_LET))     return parse_let(p);
    if(mat(p,TOK_CONST))   return parse_const(p);
    if(mat(p,TOK_FN))      return parse_fn(p);
    if(mat(p,TOK_CLASS))   return parse_class(p);
    if(mat(p,TOK_IF))      return parse_if(p);
    if(mat(p,TOK_WHILE))   return parse_while(p);
    if(mat(p,TOK_FOR))     return parse_for(p);
    if(mat(p,TOK_TRY))     return parse_try(p);
    if(mat(p,TOK_RETURN)){
        int ln=p->previous->line;
        ASTNode* nd=ast_node_new(NODE_RETURN,ln);
        if(!chk(p,TOK_RBRACE)&&!chk(p,TOK_EOF))
            ast_node_add_child(nd,parse_expr(p));
        return nd;
    }

    if(mat(p,TOK_BREAK))    return ast_node_new(NODE_BREAK,   p->previous->line);
    if(mat(p,TOK_CONTINUE)) return ast_node_new(NODE_CONTINUE,p->previous->line);
    if(mat(p,TOK_LOOP)){
        ASTNode* nd=ast_node_new(NODE_LOOP,p->previous->line);
        ast_node_add_child(nd,parse_blk(p));
        return nd;
    }

    // Assignment or expression
    if(chk(p,TOK_IDENT)){
        char* nm=strdup(p->current->value);
        int ln=p->current->line;
        adv(p);

        // Assignment: x = expr
        if(chk(p,TOK_ASSIGN)){
            adv(p);
            ASTNode* nd=ast_node_new(NODE_LET,ln);
            nd->str_val=nm;
            ast_node_add_child(nd,parse_expr(p));
            return nd;
        }

        // Function call: name(args)
        if(chk(p,TOK_LPAREN)){
            ASTNode* cl=ast_node_new(NODE_CALL,ln);
            cl->str_val=nm;
            adv(p);
            while(!chk(p,TOK_RPAREN)&&!chk(p,TOK_EOF)){
                ast_node_add_child(cl,parse_expr(p));
                if(!chk(p,TOK_RPAREN)) exp_tok(p,TOK_COMMA,"Expected ','");
            }
            exp_tok(p,TOK_RPAREN,"Expected ')'");
            return parse_dot_chain(p,cl,ln);
        }

        // Dot chain: obj.method()
        if(chk(p,TOK_DOT)){
            ASTNode* id=ast_node_new(NODE_IDENT,ln);
            id->str_val=nm;
            return parse_dot_chain(p,id,ln);
        }

        // Just identifier
        ASTNode* id=ast_node_new(NODE_IDENT,ln);
        id->str_val=nm;
        return id;
    }

    return parse_expr(p);
}

Parser* parser_new(Lexer* lexr){
    Parser* p=malloc(sizeof(Parser));
    p->lexer=lexr; p->previous=NULL;
    p->had_error=0;
    p->current=lexer_next_token(lexr);
    return p;
}

ASTNode* parser_parse(Parser* p){
    ASTNode* prog=ast_node_new(NODE_PROGRAM,1);
    while(!chk(p,TOK_EOF)){
        ASTNode* s=parse_stmt(p);
        if(s) ast_node_add_child(prog,s);
    }
    return prog;
}

void parser_free(Parser* p){
    if(!p) return;
    if(p->current)  token_free(p->current);
    if(p->previous) token_free(p->previous);
    free(p);
}
