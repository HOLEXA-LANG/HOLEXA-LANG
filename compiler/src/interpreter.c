#define _POSIX_C_SOURCE 200809L
#include "../include/interpreter.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

static Value* val_new(ValueType t){
    Value* v=malloc(sizeof(Value));
    v->type=t; v->return_type=t;
    v->int_val=0; v->float_val=0.0;
    v->bool_val=0; v->str_val=NULL;
    v->fn_node=NULL;
    return v;
}
static Value* val_int(long long n){ Value* v=val_new(VAL_INT); v->int_val=n; return v; }
static Value* val_float(double f){ Value* v=val_new(VAL_FLOAT); v->float_val=f; return v; }
static Value* val_string(const char* s){ Value* v=val_new(VAL_STRING); v->str_val=strdup(s?s:""); return v; }
static Value* val_bool(int b){ Value* v=val_new(VAL_BOOL); v->bool_val=b; return v; }
static Value* val_none(void){ return val_new(VAL_NONE); }

static Value* val_copy(Value* v){
    if(!v) return val_none();
    Value* c=val_new(v->type);
    c->return_type=v->return_type;
    c->int_val=v->int_val;
    c->float_val=v->float_val;
    c->bool_val=v->bool_val;
    c->fn_node=v->fn_node;
    c->str_val=v->str_val?strdup(v->str_val):NULL;
    return c;
}
static void val_free(Value* v){ if(!v) return; if(v->str_val) free(v->str_val); free(v); }

static char* val_to_str(Value* v){
    char buf[128];
    if(!v) return strdup("none");
    if(v->type==VAL_INT)   { snprintf(buf,sizeof(buf),"%lld",v->int_val); return strdup(buf); }
    if(v->type==VAL_FLOAT) { snprintf(buf,sizeof(buf),"%g",v->float_val); return strdup(buf); }
    if(v->type==VAL_BOOL)  return strdup(v->bool_val?"true":"false");
    if(v->type==VAL_STRING)return strdup(v->str_val?v->str_val:"");
    return strdup("none");
}
static int val_truthy(Value* v){
    if(!v) return 0;
    if(v->type==VAL_BOOL)   return v->bool_val!=0;
    if(v->type==VAL_INT)    return v->int_val!=0;
    if(v->type==VAL_FLOAT)  return v->float_val!=0.0;
    if(v->type==VAL_STRING) return v->str_val&&strlen(v->str_val)>0;
    return 0;
}
static Value* make_return(Value* v){
    Value* r=val_copy(v);
    r->return_type=v->type;
    r->type=VAL_RETURN;
    return r;
}
static Value* unwrap_return(Value* v){
    if(!v||v->type!=VAL_RETURN) return v;
    Value* inner=val_copy(v);
    inner->type=v->return_type;
    val_free(v);
    return inner;
}

static Env* env_new(Env* parent){
    Env* e=malloc(sizeof(Env));
    e->count=0; e->parent=parent;
    for(int i=0;i<MAX_ENV_VARS;i++){ e->names[i]=NULL; e->values[i]=NULL; }
    return e;
}
static Value* env_get(Env* e, const char* key){
    Env* cur=e;
    while(cur){
        for(int i=0;i<cur->count;i++)
            if(cur->names[i]&&strcmp(cur->names[i],key)==0)
                return cur->values[i];
        cur=cur->parent;
    }
    return NULL;
}
static void env_set(Env* e, const char* key, Value* val){
    Env* cur=e;
    while(cur){
        for(int i=0;i<cur->count;i++){
            if(cur->names[i]&&strcmp(cur->names[i],key)==0){
                val_free(cur->values[i]);
                cur->values[i]=val;
                return;
            }
        }
        cur=cur->parent;
    }
    if(e->count<MAX_ENV_VARS){
        e->names[e->count]=strdup(key);
        e->values[e->count]=val;
        e->count++;
    }
}
static void env_free(Env* e){
    if(!e) return;
    for(int i=0;i<e->count;i++){
        if(e->names[i])  free(e->names[i]);
        if(e->values[i]) val_free(e->values[i]);
    }
    free(e);
}

static Value* hlx_eval(Interpreter* interp, ASTNode* nd, Env* env);

static Value* eval_binop(const char* op, Value* L, Value* R){
    if(!op||!L||!R) return val_none();
    if(strcmp(op,"+")==0&&(L->type==VAL_STRING||R->type==VAL_STRING)){
        char* ls=val_to_str(L); char* rs=val_to_str(R);
        char* res=malloc(strlen(ls)+strlen(rs)+1);
        strcpy(res,ls); strcat(res,rs);
        Value* v=val_string(res);
        free(ls); free(rs); free(res); return v;
    }
    if(strcmp(op,"and")==0) return val_bool(val_truthy(L)&&val_truthy(R));
    if(strcmp(op,"or") ==0) return val_bool(val_truthy(L)||val_truthy(R));
    double l=(L->type==VAL_FLOAT)?L->float_val:(double)L->int_val;
    double r=(R->type==VAL_FLOAT)?R->float_val:(double)R->int_val;
    int fl=(L->type==VAL_FLOAT||R->type==VAL_FLOAT);
    if(strcmp(op,"+" )==0) return fl?val_float(l+r):val_int((long long)(l+r));
    if(strcmp(op,"-" )==0) return fl?val_float(l-r):val_int((long long)(l-r));
    if(strcmp(op,"*" )==0) return fl?val_float(l*r):val_int((long long)(l*r));
    if(strcmp(op,"/" )==0){
        if(r==0.0){ fprintf(stderr,"\n[HOLEXA ERROR HLX301] Division by zero\n\n"); return val_none(); }
        return fl?val_float(l/r):val_int((long long)(l/r));
    }
    if(strcmp(op,"%" )==0) return val_int((long long)l%(long long)r);
    if(strcmp(op,"**")==0) return val_float(pow(l,r));
    if(strcmp(op,"==")==0) return val_bool(l==r);
    if(strcmp(op,"!=")==0) return val_bool(l!=r);
    if(strcmp(op,"<" )==0) return val_bool(l<r);
    if(strcmp(op,">" )==0) return val_bool(l>r);
    if(strcmp(op,"<=")==0) return val_bool(l<=r);
    if(strcmp(op,">=")==0) return val_bool(l>=r);
    return val_none();
}

static Value* call_fn(Interpreter* interp, ASTNode* fn_node,
                       int argc, ASTNode** argv, Env* call_env){
    Env* fn_env=env_new(interp->global);
    int pc=fn_node->child_count-1;
    if(pc<0) pc=0;
    for(int i=0;i<pc&&i<argc;i++){
        ASTNode* prm=fn_node->children[i];
        if(prm&&prm->type==NODE_IDENT&&prm->str_val){
            Value* arg=hlx_eval(interp,argv[i],call_env);
            if(arg->type==VAL_RETURN) arg=unwrap_return(arg);
            env_set(fn_env,prm->str_val,arg);
        }
    }
    Value* result=val_none();
    if(fn_node->child_count>0){
        val_free(result);
        result=hlx_eval(interp,fn_node->children[fn_node->child_count-1],fn_env);
    }
    env_free(fn_env);
    if(result->type==VAL_RETURN) return unwrap_return(result);
    return result;
}

static Value* hlx_eval(Interpreter* interp, ASTNode* nd, Env* env){
    if(!nd) return val_none();

    if(nd->type==NODE_INT)    return val_int(nd->int_val);
    if(nd->type==NODE_FLOAT)  return val_float(nd->float_val);
    if(nd->type==NODE_STRING) return val_string(nd->str_val?nd->str_val:"");
    if(nd->type==NODE_BOOL)   return val_bool(nd->bool_val);
    if(nd->type==NODE_NONE)   return val_none();

    if(nd->type==NODE_UNOP){
        Value* v=hlx_eval(interp,nd->child_count>0?nd->children[0]:NULL,env);
        if(v->type==VAL_RETURN) v=unwrap_return(v);
        if(nd->str_val&&strcmp(nd->str_val,"-")==0){
            if(v->type==VAL_FLOAT){ double f=-v->float_val; val_free(v); return val_float(f); }
            long long n=-v->int_val; val_free(v); return val_int(n);
        }
        if(nd->str_val&&strcmp(nd->str_val,"not")==0){
            int b=!val_truthy(v); val_free(v); return val_bool(b);
        }
        return v;
    }

    if(nd->type==NODE_IDENT){
        if(!nd->str_val) return val_none();
        if(strcmp(nd->str_val,"true") ==0) return val_bool(1);
        if(strcmp(nd->str_val,"false")==0) return val_bool(0);
        if(strcmp(nd->str_val,"none") ==0) return val_none();
        Value* v=env_get(env,nd->str_val);
        if(!v){ fprintf(stderr,"\n[HOLEXA ERROR HLX202] Undefined '%s' line %d\n\n",nd->str_val,nd->line); return val_none(); }
        return val_copy(v);
    }

    if(nd->type==NODE_LET||nd->type==NODE_CONST){
        Value* v=(nd->child_count>0)?hlx_eval(interp,nd->children[0],env):val_none();
        if(v->type==VAL_RETURN) v=unwrap_return(v);
        if(nd->str_val) env_set(env,nd->str_val,v);
        else val_free(v);
        return val_none();
    }

    if(nd->type==NODE_BINOP){
        if(nd->str_val&&strcmp(nd->str_val,".")==0){
            if(nd->child_count<2) return val_none();
            ASTNode* right=nd->children[1];
            if(right&&right->type==NODE_CALL&&right->str_val){
                Value* fn=env_get(env,right->str_val);
                if(fn&&fn->type==VAL_FUNCTION&&fn->fn_node)
                    return call_fn(interp,fn->fn_node,right->child_count,right->children,env);
            }
            return val_none();
        }
        Value* L=(nd->child_count>0)?hlx_eval(interp,nd->children[0],env):val_none();
        Value* R=(nd->child_count>1)?hlx_eval(interp,nd->children[1],env):val_none();
        if(L->type==VAL_RETURN) L=unwrap_return(L);
        if(R->type==VAL_RETURN) R=unwrap_return(R);
        Value* res=eval_binop(nd->str_val,L,R);
        val_free(L); val_free(R);
        return res;
    }

    if(nd->type==NODE_BLOCK){
        Env* be=env_new(env);
        Value* last=val_none();
        for(int i=0;i<nd->child_count;i++){
            val_free(last);
            last=hlx_eval(interp,nd->children[i],be);
            if(last->type==VAL_RETURN) break;
        }
        env_free(be);
        return last;
    }

    if(nd->type==NODE_PROGRAM){
        for(int i=0;i<nd->child_count;i++){
            ASTNode* ch=nd->children[i];
            if(!ch) continue;
            if(ch->type==NODE_FUNCTION&&ch->str_val){
                Value* fn=val_new(VAL_FUNCTION); fn->fn_node=ch;
                env_set(env,ch->str_val,fn);
            }
        }
        Value* last=val_none();
        for(int i=0;i<nd->child_count;i++){
            ASTNode* ch=nd->children[i];
            if(!ch||ch->type==NODE_FUNCTION||ch->type==NODE_CLASS) continue;
            val_free(last); last=hlx_eval(interp,ch,env);
        }
        val_free(last); return val_none();
    }

    if(nd->type==NODE_FUNCTION){
        if(nd->str_val){ Value* fn=val_new(VAL_FUNCTION); fn->fn_node=nd; env_set(env,nd->str_val,fn); }
        return val_none();
    }

    if(nd->type==NODE_CALL){
        if(!nd->str_val) return val_none();
        if(strcmp(nd->str_val,"print")==0){
            for(int i=0;i<nd->child_count;i++){
                Value* v=hlx_eval(interp,nd->children[i],env);
                if(v->type==VAL_RETURN) v=unwrap_return(v);
                char* s=val_to_str(v);
                if(i>0) printf(" ");
                printf("%s",s); free(s); val_free(v);
            }
            printf("\n"); return val_none();
        }
        if(strcmp(nd->str_val,"str")==0){
            if(nd->child_count>0){
                Value* v=hlx_eval(interp,nd->children[0],env);
                if(v->type==VAL_RETURN) v=unwrap_return(v);
                char* s=val_to_str(v); val_free(v);
                Value* r=val_string(s); free(s); return r;
            }
            return val_string("");
        }
        if(strcmp(nd->str_val,"int")==0){
            if(nd->child_count>0){
                Value* v=hlx_eval(interp,nd->children[0],env);
                if(v->type==VAL_RETURN) v=unwrap_return(v);
                long long n=(v->type==VAL_STRING)?atoll(v->str_val):(v->type==VAL_FLOAT)?(long long)v->float_val:v->int_val;
                val_free(v); return val_int(n);
            }
            return val_int(0);
        }

        if(strcmp(nd->str_val,"float")==0){
            if(nd->child_count>0){
                Value* v=hlx_eval(interp,nd->children[0],env);
                if(v->type==VAL_RETURN) v=unwrap_return(v);
                double n=(v->type==VAL_STRING)?atof(v->str_val):(v->type==VAL_INT)?(double)v->int_val:v->float_val;
                val_free(v); return val_float(n);
            }
            return val_float(0.0);
        }
        if(strcmp(nd->str_val,"len")==0){
            if(nd->child_count>0){
                Value* v=hlx_eval(interp,nd->children[0],env);
                if(v->type==VAL_RETURN) v=unwrap_return(v);
                long long n=v->str_val?(long long)strlen(v->str_val):0;
                val_free(v); return val_int(n);
            }
            return val_int(0);
        }
        if(strcmp(nd->str_val,"abs")==0){
            if(nd->child_count>0){
                Value* v=hlx_eval(interp,nd->children[0],env);
                if(v->type==VAL_RETURN) v=unwrap_return(v);
                if(v->type==VAL_FLOAT){ double f=v->float_val<0?-v->float_val:v->float_val; val_free(v); return val_float(f); }
                long long n=v->int_val<0?-v->int_val:v->int_val; val_free(v); return val_int(n);
            }
            return val_int(0);
        }
        if(strcmp(nd->str_val,"sqrt")==0){
            if(nd->child_count>0){
                Value* v=hlx_eval(interp,nd->children[0],env);
                if(v->type==VAL_RETURN) v=unwrap_return(v);
                double n=(v->type==VAL_FLOAT)?v->float_val:(double)v->int_val;
                val_free(v); return val_float(sqrt(n));
            }
            return val_float(0.0);
        }
        if(strcmp(nd->str_val,"pow")==0){
            if(nd->child_count>=2){
                Value* a=hlx_eval(interp,nd->children[0],env);
                Value* b=hlx_eval(interp,nd->children[1],env);
                if(a->type==VAL_RETURN) a=unwrap_return(a);
                if(b->type==VAL_RETURN) b=unwrap_return(b);
                double base=(a->type==VAL_FLOAT)?a->float_val:(double)a->int_val;
                double ep=(b->type==VAL_FLOAT)?b->float_val:(double)b->int_val;
                val_free(a); val_free(b); return val_float(pow(base,ep));
            }
            return val_float(0.0);
        }
        Value* fn=env_get(env,nd->str_val);
        if(!fn||fn->type!=VAL_FUNCTION||!fn->fn_node){
            fprintf(stderr,"\n[HOLEXA ERROR HLX203] Undefined function '%s' line %d\n\n",nd->str_val,nd->line);
            return val_none();
        }
        return call_fn(interp,fn->fn_node,nd->child_count,nd->children,env);
    }

    if(nd->type==NODE_RETURN){
        Value* v=(nd->child_count>0)?hlx_eval(interp,nd->children[0],env):val_none();
        if(v->type==VAL_RETURN) return v;
        Value* r=make_return(v); val_free(v); return r;
    }

    if(nd->type==NODE_IF){
        if(nd->child_count<2) return val_none();
        Value* cond=hlx_eval(interp,nd->children[0],env);
        if(cond->type==VAL_RETURN) cond=unwrap_return(cond);
        int t=val_truthy(cond); val_free(cond);
        if(t) return hlx_eval(interp,nd->children[1],env);
        if(nd->child_count>2) return hlx_eval(interp,nd->children[2],env);
        return val_none();
    }

    if(nd->type==NODE_WHILE){
        if(nd->child_count<2) return val_none();
        int lim=100000;
        while(lim-->0){
            Value* cond=hlx_eval(interp,nd->children[0],env);
            if(cond->type==VAL_RETURN) cond=unwrap_return(cond);
            int t=val_truthy(cond); val_free(cond);
            if(!t) break;
            Value* r=hlx_eval(interp,nd->children[1],env);
            if(r->type==VAL_RETURN) return r;
            val_free(r);
        }
        return val_none();
    }

    if(nd->type==NODE_FOR){
        if(nd->child_count<2) return val_none();
        Env* le=env_new(env);
        Value* sv=hlx_eval(interp,nd->children[0],le);
        if(sv->type==VAL_RETURN) sv=unwrap_return(sv);
        Value* ev=(nd->child_count>2)?hlx_eval(interp,nd->children[1],le):NULL;
        if(ev&&ev->type==VAL_RETURN) ev=unwrap_return(ev);
        ASTNode* body=nd->children[nd->child_count-1];
        long long start=sv->int_val;
        long long end=ev?ev->int_val:start+10;
        val_free(sv); if(ev) val_free(ev);
        for(long long i=start;i<end;i++){
            if(nd->str_val) env_set(le,nd->str_val,val_int(i));
            Value* r=hlx_eval(interp,body,le);
            if(r->type==VAL_RETURN){ env_free(le); return r; }
            val_free(r);
        }
        env_free(le); return val_none();
    }

    if(nd->type==NODE_LOOP){
        int lim=100000;
        while(lim-->0){
            Value* r=(nd->child_count>0)?hlx_eval(interp,nd->children[0],env):val_none();
            if(r->type==VAL_RETURN) return r;
            val_free(r);
        }
        return val_none();
    }

    if(nd->type==NODE_TRY){
        if(nd->child_count>0){ Value* r=hlx_eval(interp,nd->children[0],env); if(r->type==VAL_RETURN) return r; val_free(r); }
        return val_none();
    }

    if(nd->type==NODE_CLASS){
        if(nd->str_val){
            Value* cls=val_new(VAL_FUNCTION); cls->fn_node=nd;
            env_set(env,nd->str_val,cls);
            for(int i=0;i<nd->child_count;i++){
                ASTNode* ch=nd->children[i];
                if(ch&&ch->type==NODE_FUNCTION&&ch->str_val){
                    Value* fn=val_new(VAL_FUNCTION); fn->fn_node=ch;
                    env_set(env,ch->str_val,fn);
                }
            }
        }
        return val_none();
    }

    for(int i=0;i<nd->child_count;i++){ Value* r=hlx_eval(interp,nd->children[i],env); val_free(r); }
    return val_none();
}

Interpreter* interpreter_new(void){
    Interpreter* interp=malloc(sizeof(Interpreter));
    interp->global=env_new(NULL);
    return interp;
}

void interpreter_run(Interpreter* interp, ASTNode* nd){
    hlx_eval(interp,nd,interp->global);
    Value* mfn=env_get(interp->global,"main");
    if(mfn&&mfn->type==VAL_FUNCTION&&mfn->fn_node){
        Env* me=env_new(interp->global);
        ASTNode* fn=mfn->fn_node;
        if(fn->child_count>0){ Value* r=hlx_eval(interp,fn->children[fn->child_count-1],me); val_free(r); }
        env_free(me);
    }
}

void interpreter_free(Interpreter* interp){
    if(!interp) return;
    env_free(interp->global);
    free(interp);
}
