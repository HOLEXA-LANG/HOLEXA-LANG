// HOLEXA Runtime v1.0.0
// Code like a Dragon. Think like a Human.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// ── Built-in print ───────────────────────────────────────
void hlx_print(const char* msg) {
    printf("%s\n", msg);
}

void hlx_print_int(long long n) {
    printf("%lld\n", n);
}

void hlx_print_float(double f) {
    printf("%g\n", f);
}

void hlx_print_bool(int b) {
    printf("%s\n", b ? "true" : "false");
}

// ── Built-in math ────────────────────────────────────────
long long hlx_abs_int(long long n) {
    return n < 0 ? -n : n;
}

double hlx_abs_float(double f) {
    return f < 0 ? -f : f;
}

double hlx_sqrt(double n) {
    return sqrt(n);
}

double hlx_pow(double base, double exp) {
    return pow(base, exp);
}

long long hlx_max(long long a, long long b) {
    return a > b ? a : b;
}

long long hlx_min(long long a, long long b) {
    return a < b ? a : b;
}

// ── Built-in string ──────────────────────────────────────
int hlx_strlen(const char* s) {
    return s ? (int)strlen(s) : 0;
}

char* hlx_strcat_new(const char* a, const char* b) {
    if (!a) a = "";
    if (!b) b = "";
    int len = strlen(a) + strlen(b) + 1;
    char* result = malloc(len);
    strcpy(result, a);
    strcat(result, b);
    return result;
}

int hlx_strcmp(const char* a, const char* b) {
    if (!a || !b) return -1;
    return strcmp(a, b);
}

// ── Type conversion ──────────────────────────────────────
long long hlx_str_to_int(const char* s) {
    return s ? atoll(s) : 0;
}

double hlx_str_to_float(const char* s) {
    return s ? atof(s) : 0.0;
}

char* hlx_int_to_str(long long n) {
    char* buf = malloc(32);
    snprintf(buf, 32, "%lld", n);
    return buf;
}

char* hlx_float_to_str(double f) {
    char* buf = malloc(32);
    snprintf(buf, 32, "%g", f);
    return buf;
}

char* hlx_bool_to_str(int b) {
    return b ? "true" : "false";
}

// ── Error handling ───────────────────────────────────────
void hlx_panic(const char* msg, int line) {
    fprintf(stderr, "\n[HOLEXA RUNTIME ERROR] Line %d: %s\n\n", line, msg);
    exit(1);
}

void hlx_assert(int cond, const char* msg, int line) {
    if (!cond) hlx_panic(msg, line);
}

// ── Memory ───────────────────────────────────────────────
void* hlx_alloc(int size) {
    void* ptr = malloc(size);
    if (!ptr) hlx_panic("Out of memory", 0);
    return ptr;
}

void hlx_free(void* ptr) {
    if (ptr) free(ptr);
}
