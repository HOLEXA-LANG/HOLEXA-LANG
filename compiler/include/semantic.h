#ifndef SEMANTIC_H
#define SEMANTIC_H

#define _POSIX_C_SOURCE 200809L
#include "holexa.h"

#define MAX_SYMBOLS 1024
#define MAX_SCOPES  64

// Symbol types
typedef enum {
    SYM_VARIABLE,
    SYM_FUNCTION,
    SYM_CLASS,
    SYM_PARAMETER
} SymbolKind;

// One symbol entry
typedef struct {
    char*      name;
    SymbolKind kind;
    int        line;
    int        is_const;
} Symbol;

// One scope
typedef struct {
    Symbol symbols[MAX_SYMBOLS];
    int    count;
} Scope;

// Semantic analyzer
typedef struct {
    Scope  scopes[MAX_SCOPES];
    int    scope_depth;
    int    error_count;
    int    warning_count;
} Semantic;

Semantic* semantic_new(void);
void      semantic_analyze(Semantic* s, ASTNode* node);
void      semantic_free(Semantic* s);

#endif
