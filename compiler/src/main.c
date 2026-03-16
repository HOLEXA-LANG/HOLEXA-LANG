#include "../include/holexa.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void hlx_error(const char* msg, int line, int col) {
    fprintf(stderr, "\n[HOLEXA ERROR] Line %d, Col %d: %s\n", line, col, msg);
    exit(1);
}

static char* read_file(const char* path) {
    FILE* f = fopen(path, "r");
    if (!f) {
        fprintf(stderr, "Error: Cannot open file '%s'\n", path);
        exit(1);
    }
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    rewind(f);
    char* buf = malloc(size + 1);
    fread(buf, 1, size, f);
    buf[size] = '\0';
    fclose(f);
    return buf;
}

static void run_tokens(const char* source) {
    printf("\n═══════════════════════════════\n");
    printf("  HOLEXA Lexer — Token Stream\n");
    printf("═══════════════════════════════\n");
    Lexer* lexer = lexer_new(source);
    Token* tok;
    do {
        tok = lexer_next_token(lexer);
        printf("  [Line %2d] %-12s → %s\n",
            tok->line, token_type_name(tok->type), tok->value);
        TokenType t = tok->type;
        token_free(tok);
        if (t == TOK_EOF) break;
    } while (1);
    lexer_free(lexer);
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
    printf("  Version 1.0.0 — hlxc compiler\n\n");

    if (argc < 2) {
        printf("Usage:\n");
        printf("  hlxc <file.hlx>        Compile a file\n");
        printf("  hlxc run <file.hlx>    Run a file\n");
        printf("  hlxc --version         Show version\n");
        return 0;
    }

    if (strcmp(argv[1], "--version") == 0) {
        printf("hlxc version 1.0.0\n");
        return 0;
    }

    const char* filepath = argv[1];
    if (strcmp(argv[1], "run") == 0) {
        if (argc < 3) { fprintf(stderr, "Error: No file specified\n"); return 1; }
        filepath = argv[2];
    }

    char* source = read_file(filepath);
    printf("Compiling: %s\n", filepath);
    run_tokens(source);
    printf("\n✓ Lexer phase complete!\n");
    free(source);
    return 0;
}
