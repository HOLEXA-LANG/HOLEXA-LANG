#ifndef CODEGEN_H
#define CODEGEN_H

#define _POSIX_C_SOURCE 200809L
#include "holexa.h"
#include <stdio.h>

typedef struct {
    FILE* out;
    int   tmp_count;
    int   str_count;
} Codegen;

Codegen* codegen_new(FILE* out);
void     codegen_generate(Codegen* cg, ASTNode* node);
void     codegen_free(Codegen* cg);

#endif
