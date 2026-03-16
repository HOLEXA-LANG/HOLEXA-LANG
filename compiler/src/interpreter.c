#define _POSIX_C_SOURCE 200809L
#include "../include/interpreter.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// ─────────────────────────────────────
// VALUE HELPERS
// ─────────────────────────────────────
static Value* val_int(long long v) {
    Value* val = malloc(sizeof(Value));
    val->type = VAL_INT; val->int_val = v;
    val->str_val = NULL; val->fn_node = NULL;
    return val;
}
static Value* val_float(double v) {
    Value* val = malloc(sizeof(Value));
    val->type = VAL_FLOAT; val->float_val = v;
    val->str_val = NULL; val->fn_node = NULL;
    return val;
}
static Value* val_string(const char* v) {
    Value* val = malloc(sizeof(Value));
    val->type = VAL_STRING;
    val->str_val = strdup(v ? v : "");
    val->fn_node = NULL;
    return val;
}
static Value* val_bool(int v) {
    Value* val = malloc(sizeof(Value));
    val->type = VAL_BOOL; val->bool_val = v;
    val->str_val = NULL; val->fn_node = NULL;
    return val;
}
static Value* val_none(void) {
    Value* val = malloc(sizeof(Value));
    val->type = VAL_NONE;
    val->str_val = NULL; val->fn_node = NULL;
    return val;
}
static Value* val_return(Value* inner) {
    Value* val = malloc(sizeof(Value));
    val->type = VAL_RETURN;
    val->str_val = NULL;
    val->fn_node = NULL;
    val->int_val  = inner->int_val;
    val->float_val= inner->float_val;
    val->bool_val = inner->bool_val;
    if (inner->str_val) val->str_val = strdup(inner->str_val);
    return val;
}

static void value_free(Value* v) {
    if (!v) return;
    if (v->str_val) free(v->str_val);
    free(v);
}

static char* value_to_string(Value* v) {
    char buf[256];
    if (!v) { return strdup("none"); }
    switch (v->type) {
        case VAL_INT:    snprintf(buf, sizeof(buf), "%lld", v->int_val); return strdup(buf);
        case VAL_FLOAT:  snprintf(buf, sizeof(buf), "%g",   v->float_val); return strdup(buf);
        case VAL_BOOL:   return strdup(v->bool_val ? "true" : "false");
        case VAL_NONE:   return strdup("none");
        case VAL_STRING: return strdup(v->str_val ? v->str_val : "");
        default:         return strdup("none");
    }
}

// ─────────────────────────────────────
// ENVIRONMENT
// ─────────────────────────────────────
static Env* env_new(Env* parent) {
    Env* e  = malloc(sizeof(Env));
    e->count  = 0;
    e->parent = parent;
    for (int i = 0; i < MAX_ENV_VARS; i++) {
        e->names[i]  = NULL;
        e->values[i] = NULL;
    }
    return e;
}

static void env_set(Env* e, const char* name, Value* val) {
    // Update existing
    for (int i = 0; i < e->count; i++) {
        if (e->names[i] && strcmp(e->names[i], name) == 0) {
            value_free(e->values[i]);
            e->values[i] = val;
            return;
        }
    }
    // New variable
    if (e->count < MAX_ENV_VARS) {
        e->names[e->count]  = strdup(name);
        e->values[e->count] = val;
        e->count++;
    }
}

static Value* env_get(Env* e, const char* name) {
    for (int i = 0; i < e->count; i++)
        if (e->names[i] && strcmp(e->names[i], name) == 0)
            return e->values[i];
    if (e->parent) return env_get(e->parent, name);
    return NULL;
}

static void env_free(Env* e) {
    if (!e) return;
    for (int i = 0; i < e->count; i++) {
        if (e->names[i])  free(e->names[i]);
        if (e->values[i]) value_free(e->values[i]);
    }
    free(e);
}

// ─────────────────────────────────────
// EVAL FORWARD
// ─────────────────────────────────────
static Value* eval(Interpreter* interp, ASTNode* node, Env* env);

// ─────────────────────────────────────
// BUILT-IN: print
// ─────────────────────────────────────
static Value* builtin_print(ASTNode* node, Env* env, Interpreter* interp) {
    for (int i = 0; i < node->child_count; i++) {
        Value* v = eval(interp, node->children[i], env);
        char*  s = value_to_string(v);
        printf("%s", s);
        free(s);
        value_free(v);
    }
    printf("\n");
    return val_none();
}

// ─────────────────────────────────────
// EVAL BINARY OPERATION
// ─────────────────────────────────────
static Value* eval_binop(const char* op, Value* left, Value* right) {
    // String concatenation
    if (strcmp(op, "+") == 0 &&
        (left->type == VAL_STRING || right->type == VAL_STRING)) {
        char* ls = value_to_string(left);
        char* rs = value_to_string(right);
        char* result = malloc(strlen(ls) + strlen(rs) + 1);
        strcpy(result, ls);
        strcat(result, rs);
        Value* v = val_string(result);
        free(ls); free(rs); free(result);
        return v;
    }

    // Numeric operations
    double l = (left->type  == VAL_FLOAT) ? left->float_val  : (double)left->int_val;
    double r = (right->type == VAL_FLOAT) ? right->float_val : (double)right->int_val;
    int is_float = (left->type == VAL_FLOAT || right->type == VAL_FLOAT);

    if (strcmp(op, "+")  == 0) return is_float ? val_float(l+r) : val_int((long long)(l+r));
    if (strcmp(op, "-")  == 0) return is_float ? val_float(l-r) : val_int((long long)(l-r));
    if (strcmp(op, "*")  == 0) return is_float ? val_float(l*r) : val_int((long long)(l*r));
    if (strcmp(op, "/")  == 0) {
        if (r == 0) { fprintf(stderr, "[HOLEXA ERROR] Division by zero\n"); return val_none(); }
        return is_float ? val_float(l/r) : val_int((long long)(l/r));
    }
    if (strcmp(op, "%")  == 0) return val_int((long long)l % (long long)r);
    if (strcmp(op, "==") == 0) return val_bool(l == r);
    if (strcmp(op, "!=") == 0) return val_bool(l != r);
    if (strcmp(op, "<")  == 0) return val_bool(l <  r);
    if (strcmp(op, ">")  == 0) return val_bool(l >  r);
    if (strcmp(op, "<=") == 0) return val_bool(l <= r);
    if (strcmp(op, ">=") == 0) return val_bool(l >= r);

    return val_none();
}

// ─────────────────────────────────────
// MAIN EVAL
// ─────────────────────────────────────
static Value* eval(Interpreter* interp, ASTNode* node, Env* env) {
    if (!node) return val_none();

    if (node->type == NODE_INT)    return val_int(node->int_val);
    if (node->type == NODE_FLOAT)  return val_float(node->float_val);
    if (node->type == NODE_STRING) return val_string(node->str_val ? node->str_val : "");
    if (node->type == NODE_BOOL)   return val_bool(node->bool_val);
    if (node->type == NODE_NONE)   return val_none();

    if (node->type == NODE_IDENT) {
        if (!node->str_val) return val_none();
        Value* v = env_get(env, node->str_val);
        if (!v) {
            fprintf(stderr, "[HOLEXA ERROR] Undefined: '%s'\n", node->str_val);
            return val_none();
        }
        // Return a copy
        if (v->type == VAL_STRING) return val_string(v->str_val);
        if (v->type == VAL_INT)    return val_int(v->int_val);
        if (v->type == VAL_FLOAT)  return val_float(v->float_val);
        if (v->type == VAL_BOOL)   return val_bool(v->bool_val);
        return val_none();
    }

    if (node->type == NODE_LET || node->type == NODE_CONST) {
        Value* v = (node->child_count > 0) ? eval(interp, node->children[0], env) : val_none();
        if (node->str_val) env_set(env, node->str_val, v);
        else value_free(v);
        return val_none();
    }

    if (node->type == NODE_ASSIGN) {
        Value* v = (node->child_count > 0) ? eval(interp, node->children[0], env) : val_none();
        if (node->str_val) env_set(env, node->str_val, v);
        return val_none();
    }

    if (node->type == NODE_BINOP) {
        if (node->str_val && strcmp(node->str_val, ".") == 0)
            return val_none();
        Value* left  = (node->child_count > 0) ? eval(interp, node->children[0], env) : val_none();
        Value* right = (node->child_count > 1) ? eval(interp, node->children[1], env) : val_none();
        Value* result = eval_binop(node->str_val ? node->str_val : "+", left, right);
        value_free(left);
        value_free(right);
        return result;
    }

    if (node->type == NODE_BLOCK) {
        Env* block_env = env_new(env);
        Value* last = val_none();
        for (int i = 0; i < node->child_count; i++) {
            value_free(last);
            last = eval(interp, node->children[i], block_env);
            if (last->type == VAL_RETURN) break;
        }
        env_free(block_env);
        return last;
    }

    if (node->type == NODE_PROGRAM) {
        Value* last = val_none();
        for (int i = 0; i < node->child_count; i++) {
            value_free(last);
            last = eval(interp, node->children[i], env);
        }
        value_free(last);
        return val_none();
    }

    if (node->type == NODE_FUNCTION) {
        Value* fn = malloc(sizeof(Value));
        fn->type    = VAL_FUNCTION;
        fn->fn_node = node;
        fn->str_val = NULL;
        if (node->str_val) env_set(env, node->str_val, fn);
        return val_none();
    }

    if (node->type == NODE_CALL) {
        if (!node->str_val) return val_none();

        if (strcmp(node->str_val, "print") == 0)
            return builtin_print(node, env, interp);

        if (strcmp(node->str_val, "str") == 0) {
            if (node->child_count > 0) {
                Value* v = eval(interp, node->children[0], env);
                char*  s = value_to_string(v);
                Value* r = val_string(s);
                free(s); value_free(v);
                return r;
            }
            return val_string("");
        }

        if (strcmp(node->str_val, "int") == 0) {
            if (node->child_count > 0) {
                Value* v = eval(interp, node->children[0], env);
                long long n = (v->type == VAL_STRING) ? atoll(v->str_val) : (long long)v->int_val;
                value_free(v);
                return val_int(n);
            }
            return val_int(0);
        }

        if (strcmp(node->str_val, "float") == 0) {
            if (node->child_count > 0) {
                Value* v = eval(interp, node->children[0], env);
                double n = (v->type == VAL_STRING) ? atof(v->str_val) : v->float_val;
                value_free(v);
                return val_float(n);
            }
            return val_float(0.0);
        }

        if (strcmp(node->str_val, "len") == 0) {
            if (node->child_count > 0) {
                Value* v = eval(interp, node->children[0], env);
                long long n = v->str_val ? (long long)strlen(v->str_val) : 0;
                value_free(v);
                return val_int(n);
            }
            return val_int(0);
        }

        // User-defined function call
        Value* fn = env_get(env, node->str_val);
        if (!fn || fn->type != VAL_FUNCTION || !fn->fn_node) {
            fprintf(stderr, "[HOLEXA ERROR] Undefined function: '%s'\n", node->str_val);
            return val_none();
        }

        ASTNode* fn_node = fn->fn_node;
        Env* fn_env = env_new(interp->global);

        // Pass arguments - skip self param
        if (fn_node->child_count > 0) {
            ASTNode* body = fn_node->children[fn_node->child_count - 1];
            (void)body;
        }

        Value* result = val_none();
        if (fn_node->child_count > 0) {
            value_free(result);
            result = eval(interp, fn_node->children[fn_node->child_count - 1], fn_env);
        }

        if (result->type == VAL_RETURN) {
            Value* ret = val_none();
            ret->type      = VAL_INT;
            ret->int_val   = result->int_val;
            ret->float_val = result->float_val;
            ret->bool_val  = result->bool_val;
            if (result->str_val) ret->str_val = strdup(result->str_val);
            ret->type = (result->str_val && strlen(result->str_val) > 0) ? VAL_STRING :
                        (result->float_val != 0) ? VAL_FLOAT : VAL_INT;
            value_free(result);
            env_free(fn_env);
            return ret;
        }

        env_free(fn_env);
        return result;
    }

    if (node->type == NODE_RETURN) {
        Value* v = (node->child_count > 0) ? eval(interp, node->children[0], env) : val_none();
        Value* r = val_return(v);
        value_free(v);
        return r;
    }

    if (node->type == NODE_IF) {
        if (node->child_count < 2) return val_none();
        Value* cond = eval(interp, node->children[0], env);
        int is_true = 0;
        if (cond->type == VAL_BOOL)  is_true = cond->bool_val;
        else if (cond->type == VAL_INT)   is_true = cond->int_val != 0;
        else if (cond->type == VAL_STRING) is_true = strlen(cond->str_val) > 0;
        value_free(cond);
        if (is_true) return eval(interp, node->children[1], env);
        if (node->child_count > 2)  return eval(interp, node->children[2], env);
        return val_none();
    }

    if (node->type == NODE_WHILE) {
        if (node->child_count < 2) return val_none();
        while (1) {
            Value* cond = eval(interp, node->children[0], env);
            int is_true = (cond->type == VAL_BOOL) ? cond->bool_val :
                          (cond->type == VAL_INT)  ? (cond->int_val != 0) : 0;
            value_free(cond);
            if (!is_true) break;
            Value* r = eval(interp, node->children[1], env);
            if (r->type == VAL_RETURN) return r;
            value_free(r);
        }
        return val_none();
    }

    if (node->type == NODE_FOR) {
        if (node->child_count < 2) return val_none();
        Env* loop_env = env_new(env);
        Value* start_v = eval(interp, node->children[0], loop_env);
        Value* end_v   = (node->child_count > 2) ?
                         eval(interp, node->children[1], loop_env) : NULL;
        ASTNode* body = node->children[node->child_count - 1];

        long long start = start_v->int_val;
        long long end   = end_v ? end_v->int_val : start + 10;
        value_free(start_v);
        if (end_v) value_free(end_v);

        for (long long i = start; i < end; i++) {
            if (node->str_val) env_set(loop_env, node->str_val, val_int(i));
            Value* r = eval(interp, body, loop_env);
            if (r->type == VAL_RETURN) { env_free(loop_env); return r; }
            value_free(r);
        }
        env_free(loop_env);
        return val_none();
    }

    if (node->type == NODE_LOOP) {
        if (node->child_count < 1) return val_none();
        int limit = 100000;
        while (limit-- > 0) {
            Value* r = eval(interp, node->children[0], env);
            if (r->type == VAL_RETURN) return r;
            value_free(r);
        }
        return val_none();
    }

    if (node->type == NODE_TRY) {
        if (node->child_count > 0) {
            Value* r = eval(interp, node->children[0], env);
            value_free(r);
        }
        return val_none();
    }

    if (node->type == NODE_CLASS) {
        if (node->str_val) {
            Value* cls = malloc(sizeof(Value));
            cls->type    = VAL_FUNCTION;
            cls->fn_node = node;
            cls->str_val = NULL;
            env_set(env, node->str_val, cls);
        }
        return val_none();
    }

    return val_none();
}

// ─────────────────────────────────────
// PUBLIC API
// ─────────────────────────────────────
Interpreter* interpreter_new(void) {
    Interpreter* interp = malloc(sizeof(Interpreter));
    interp->global = env_new(NULL);
    return interp;
}

void interpreter_run(Interpreter* interp, ASTNode* node) {
    // Find and run main()
    Value* result = val_none();
    for (int i = 0; i < node->child_count; i++) {
        ASTNode* child = node->children[i];
        if (child->type == NODE_FUNCTION && child->str_val &&
            strcmp(child->str_val, "main") != 0) {
            value_free(result);
            result = eval(interp, child, interp->global);
        }
    }
    value_free(result);

    // Now run main
    Value* main_fn = env_get(interp->global, "main");
    if (!main_fn) {
        // Try eval entire program
        Value* r = eval(interp, node, interp->global);
        value_free(r);
        // Call main if now defined
        main_fn = env_get(interp->global, "main");
    }

    if (main_fn && main_fn->type == VAL_FUNCTION && main_fn->fn_node) {
        Env* main_env = env_new(interp->global);
        if (main_fn->fn_node->child_count > 0) {
            Value* r = eval(interp,
                main_fn->fn_node->children[main_fn->fn_node->child_count - 1],
                main_env);
            value_free(r);
        }
        env_free(main_env);
    }
}

void interpreter_free(Interpreter* interp) {
    if (!interp) return;
    env_free(interp->global);
    free(interp);
}
