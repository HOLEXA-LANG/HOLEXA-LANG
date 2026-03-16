#define _POSIX_C_SOURCE 200809L
#include "../include/holexa.h"
#include "../include/parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void hlx_error(const char* msg, int line, int col) {
    fprintf(stderr, "\n[HOLEXA ERROR] Line %d, Col %d: %s\n", line, col, msg);
    exit(1);
}

static char* read_file(const char* path) {
    FILE* f = fopen(path, "r");
    if (!f) { fprintf(stderr, "Error: Cannot open '%s'\n", path); exit(1); }
    fseek(f, 0, SEEK_END);
    long size = ftell(f); rewind(f);
    char* buf = malloc(size + 1);
    if (!buf) { fprintf(stderr, "Error: Out of memory\n"); exit(1); }
    fread(buf, 1, size, f);
    buf[size] = '\0';
    fclose(f);
    return buf;
}

int main(int argc, char* argv[]) {
    printf("\n");
    printf("  ██╗  ██╗ ██████╗ ██╗     ███████╗██╗  ██╗ █████╗ \n");
    printf("  ██║  ██║██╔═══██╗██║     ██╔════╝╚██╗██╔╝██╔══██╗\n");
    printf("  ███████║██║   ██║██║     █████╗   ╚███╔╝ ███████║\n");
    printf("  ██╔══██║██║   ██║██║     ██╔══╝   ██╔██╗ ██╔══██║\n");
    printf("  ██║  ██║╚██████╔╝███████╗███████╗██╔╝ ██╗██║  ██║\n");
    printf("  ╚═╝  ╚═╝ ╚═════╝ ╚══════╝╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝\n");
    printf("\n  Code like a Dragon. Think like a Human.\n");
    printf("  Version 1.0.0\n\n");

    if (argc < 2) {
        printf("Usage:\n");
        printf("  hlxc <file.hlx>       Compile\n");
        printf("  hlxc run <file.hlx>   Run\n");
        printf("  hlxc --version        Version\n");
        return 0;
    }

    if (strcmp(argv[1], "--version") == 0) {
        printf("hlxc version 1.0.0\n");
        return 0;
    }

    const char* filepath = argv[1];
    if (strcmp(argv[1], "run") == 0) {
        if (argc < 3) { fprintf(stderr, "Error: No file\n"); return 1; }
        filepath = argv[2];
    }

    char*    source = read_file(filepath);
    Lexer*   lexer  = lexer_new(source);
    Parser*  parser = parser_new(lexer);
    ASTNode* ast    = parser_parse(parser);

    if (parser->had_error) {
        printf("\n✗ Compilation failed.\n");
        ast_node_free(ast);
        parser_free(parser);
        lexer_free(lexer);
        free(source);
        return 1;
    }

    printf("Compiling: %s\n\n", filepath);
    printf("════════════════════════════════\n");
    printf("   HOLEXA Parser — AST Output\n");
    printf("════════════════════════════════\n");
    ast_print(ast, 0);
    printf("\n✓ Parser phase complete!\n\n");

    ast_node_free(ast);
    parser_free(parser);
    lexer_free(lexer);
    free(source);
    return 0;
}
