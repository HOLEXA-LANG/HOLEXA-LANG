#define _POSIX_C_SOURCE 200809L
#include "../include/codegen.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

static void emit(Codegen* cg, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vfprintf(cg->out, fmt, args);
    va_end(args);
}

static int new_tmp(Codegen* cg) { return cg->tmp_count++; }

static void gen_node(Codegen* cg, ASTNode* node);

static void gen_expr(Codegen* cg, ASTNode* node) {
    if (!node) return;
    if (node->type == NODE_INT) {
        int t = new_tmp(cg);
        emit(cg, "  %%t%d = add i64 0, %lld\n", t, node->int_val);
        return;
    }
    if (node->type == NODE_STRING) {
        int s = cg->str_count++;
        emit(cg, "@.s%d = private constant [%zu x i8] c\"%s\\00\"\n",
             s, strlen(node->str_val ? node->str_val : "") + 1,
             node->str_val ? node->str_val : "");
        return;
    }
    if (node->type == NODE_BINOP && node->str_val) {
        int L = new_tmp(cg);
        int R = new_tmp(cg);
        if (node->child_count > 0) gen_expr(cg, node->children[0]);
        if (node->child_count > 1) gen_expr(cg, node->children[1]);
        int t = new_tmp(cg);
        if (strcmp(node->str_val, "+") == 0)
            emit(cg, "  %%t%d = add i64 %%t%d, %%t%d\n", t, L, R);
        else if (strcmp(node->str_val, "-") == 0)
            emit(cg, "  %%t%d = sub i64 %%t%d, %%t%d\n", t, L, R);
        else if (strcmp(node->str_val, "*") == 0)
            emit(cg, "  %%t%d = mul i64 %%t%d, %%t%d\n", t, L, R);
        else if (strcmp(node->str_val, "/") == 0)
            emit(cg, "  %%t%d = sdiv i64 %%t%d, %%t%d\n", t, L, R);
        return;
    }
}

static void gen_node(Codegen* cg, ASTNode* node) {
    if (!node) return;
    if (node->type == NODE_FUNCTION && node->str_val) {
        int is_main = strcmp(node->str_val, "main") == 0;
        if (is_main)
            emit(cg, "\ndefine i32 @main() {\nentry:\n");
        else
            emit(cg, "\ndefine i64 @%s() {\nentry:\n", node->str_val);
        if (node->child_count > 0)
            gen_node(cg, node->children[node->child_count - 1]);
        if (is_main) emit(cg, "  ret i32 0\n}\n");
        else         emit(cg, "  ret i64 0\n}\n");
        return;
    }
    if (node->type == NODE_BLOCK) {
        for (int i = 0; i < node->child_count; i++)
            gen_node(cg, node->children[i]);
        return;
    }
    if (node->type == NODE_RETURN) {
        if (node->child_count > 0) gen_expr(cg, node->children[0]);
        int t = cg->tmp_count - 1;
        emit(cg, "  ret i64 %%t%d\n", t);
        return;
    }
    gen_expr(cg, node);
}

void codegen_generate(Codegen* cg, ASTNode* node) {
    emit(cg, "; HOLEXA LLVM IR v1.0.0\n");
    emit(cg, "; Code like a Dragon. Think like a Human.\n\n");
    emit(cg, "declare i32 @printf(i8* nocapture, ...)\n\n");
    if (!node) return;
    for (int i = 0; i < node->child_count; i++) {
        if (node->children[i] &&
            node->children[i]->type == NODE_FUNCTION)
            gen_node(cg, node->children[i]);
    }
}

Codegen* codegen_new(FILE* out) {
    Codegen* cg   = malloc(sizeof(Codegen));
    cg->out       = out;
    cg->tmp_count = 0;
    cg->str_count = 0;
    return cg;
}

void codegen_free(Codegen* cg) { if (cg) free(cg); }
