#define _POSIX_C_SOURCE 200809L
#include "../include/semantic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void scope_push(Semantic* s) {
    if (s->scope_depth >= MAX_SCOPES - 1) return;
    s->scope_depth++;
    s->scopes[s->scope_depth].count = 0;
}

static void scope_pop(Semantic* s) {
    if (s->scope_depth <= 0) return;
    Scope* scope = &s->scopes[s->scope_depth];
    for (int i = 0; i < scope->count; i++)
        if (scope->symbols[i].name) free(scope->symbols[i].name);
    scope->count = 0;
    s->scope_depth--;
}

static void scope_define(Semantic* s, const char* name,
                          SymbolKind kind, int line, int is_const) {
    Scope* scope = &s->scopes[s->scope_depth];
    for (int i = 0; i < scope->count; i++) {
        if (strcmp(scope->symbols[i].name, name) == 0) {
            fprintf(stderr,
                "\n[HOLEXA ERROR HLX201] Line %d: "
                "'%s' already declared in this scope\n\n",
                line, name);
            s->error_count++;
            return;
        }
    }
    if (scope->count >= MAX_SYMBOLS) return;
    scope->symbols[scope->count].name     = strdup(name);
    scope->symbols[scope->count].kind     = kind;
    scope->symbols[scope->count].line     = line;
    scope->symbols[scope->count].is_const = is_const;
    scope->count++;
}

static Symbol* scope_lookup(Semantic* s, const char* name) {
    for (int d = s->scope_depth; d >= 0; d--) {
        Scope* scope = &s->scopes[d];
        for (int i = 0; i < scope->count; i++)
            if (strcmp(scope->symbols[i].name, name) == 0)
                return &scope->symbols[i];
    }
    return NULL;
}

static void analyze_node(Semantic* s, ASTNode* node);

static void analyze_children(Semantic* s, ASTNode* node) {
    for (int i = 0; i < node->child_count; i++)
        analyze_node(s, node->children[i]);
}

static void analyze_node(Semantic* s, ASTNode* node) {
    if (!node) return;

    if (node->type == NODE_PROGRAM) {
        analyze_children(s, node);

    } else if (node->type == NODE_BLOCK) {
        scope_push(s);
        analyze_children(s, node);
        scope_pop(s);

    } else if (node->type == NODE_LET) {
        if (node->child_count > 0) analyze_node(s, node->children[0]);
        if (node->str_val) scope_define(s, node->str_val, SYM_VARIABLE, node->line, 0);

    } else if (node->type == NODE_CONST) {
        if (node->child_count > 0) analyze_node(s, node->children[0]);
        if (node->str_val) scope_define(s, node->str_val, SYM_VARIABLE, node->line, 1);

    } else if (node->type == NODE_FUNCTION) {
        if (node->str_val) scope_define(s, node->str_val, SYM_FUNCTION, node->line, 0);
        scope_push(s);
        scope_define(s, "self", SYM_PARAMETER, node->line, 0);
        analyze_children(s, node);
        scope_pop(s);

    } else if (node->type == NODE_CLASS) {
        if (node->str_val) scope_define(s, node->str_val, SYM_CLASS, node->line, 0);
        scope_push(s);
        analyze_children(s, node);
        scope_pop(s);

    } else if (node->type == NODE_IDENT) {
        if (!node->str_val) return;
        if (strcmp(node->str_val, "self")  == 0) return;
        if (strcmp(node->str_val, "none")  == 0) return;
        if (strcmp(node->str_val, "true")  == 0) return;
        if (strcmp(node->str_val, "false") == 0) return;
        if (!scope_lookup(s, node->str_val)) {
            fprintf(stderr,
                "\n[HOLEXA ERROR HLX202] Line %d: "
                "Undefined variable '%s'\n\n",
                node->line, node->str_val);
            s->error_count++;
        }

    } else if (node->type == NODE_CALL) {
        if (node->str_val) {
            if (strcmp(node->str_val, "print")  != 0 &&
                strcmp(node->str_val, "input")  != 0 &&
                strcmp(node->str_val, "len")    != 0 &&
                strcmp(node->str_val, "str")    != 0 &&
                strcmp(node->str_val, "int")    != 0 &&
                strcmp(node->str_val, "float")  != 0 &&
                strcmp(node->str_val, "type")   != 0 &&
                strcmp(node->str_val, "range")  != 0 &&
                strcmp(node->str_val, "append") != 0 &&
                strcmp(node->str_val, "Error")  != 0) {
                if (!scope_lookup(s, node->str_val)) {
                    fprintf(stderr,
                        "\n[HOLEXA WARNING HLX301] Line %d: "
                        "Function '%s' may not be defined yet\n\n",
                        node->line, node->str_val);
                    s->warning_count++;
                }
            }
        }
        analyze_children(s, node);

    } else if (node->type == NODE_FOR) {
        scope_push(s);
        if (node->str_val) scope_define(s, node->str_val, SYM_VARIABLE, node->line, 0);
        analyze_children(s, node);
        scope_pop(s);

    } else if (node->type == NODE_TRY) {
        scope_push(s);
        scope_define(s, "err", SYM_VARIABLE, node->line, 0);
        analyze_children(s, node);
        scope_pop(s);

    } else {
        analyze_children(s, node);
    }
}

Semantic* semantic_new(void) {
    Semantic* s      = malloc(sizeof(Semantic));
    s->scope_depth   = 0;
    s->error_count   = 0;
    s->warning_count = 0;
    s->scopes[0].count = 0;
    scope_define(s, "print",  SYM_FUNCTION, 0, 0);
    scope_define(s, "input",  SYM_FUNCTION, 0, 0);
    scope_define(s, "len",    SYM_FUNCTION, 0, 0);
    scope_define(s, "str",    SYM_FUNCTION, 0, 0);
    scope_define(s, "int",    SYM_FUNCTION, 0, 0);
    scope_define(s, "float",  SYM_FUNCTION, 0, 0);
    scope_define(s, "type",   SYM_FUNCTION, 0, 0);
    scope_define(s, "range",  SYM_FUNCTION, 0, 0);
    scope_define(s, "append", SYM_FUNCTION, 0, 0);
    scope_define(s, "Error",  SYM_FUNCTION, 0, 0);
    scope_define(s, "true",   SYM_VARIABLE, 0, 1);
    scope_define(s, "false",  SYM_VARIABLE, 0, 1);
    scope_define(s, "none",   SYM_VARIABLE, 0, 1);
    return s;
}

void semantic_analyze(Semantic* s, ASTNode* node) {
    analyze_node(s, node);
}

void semantic_free(Semantic* s) {
    if (!s) return;
    for (int d = 0; d <= s->scope_depth; d++) {
        Scope* scope = &s->scopes[d];
        for (int i = 0; i < scope->count; i++)
            if (scope->symbols[i].name) free(scope->symbols[i].name);
    }
    free(s);
}
