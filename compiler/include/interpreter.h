#ifndef INTERPRETER_H
#define INTERPRETER_H

#define _POSIX_C_SOURCE 200809L
#include "holexa.h"

// Value types
typedef enum {
    VAL_INT,
    VAL_FLOAT,
    VAL_STRING,
    VAL_BOOL,
    VAL_NONE,
    VAL_FUNCTION,
    VAL_RETURN
} ValueType;

// A HOLEXA value
typedef struct Value {
    ValueType type;
    long long  int_val;
    double     float_val;
    char*      str_val;
    int        bool_val;
    ASTNode*   fn_node;
} Value;

// Environment (variable store)
#define MAX_ENV_VARS 512

typedef struct Env {
    char*        names[MAX_ENV_VARS];
    Value*       values[MAX_ENV_VARS];
    int          count;
    struct Env*  parent;
} Env;

// Interpreter
typedef struct {
    Env* global;
} Interpreter;

Interpreter* interpreter_new(void);
void         interpreter_run(Interpreter* interp, ASTNode* node);
void         interpreter_free(Interpreter* interp);

#endif
