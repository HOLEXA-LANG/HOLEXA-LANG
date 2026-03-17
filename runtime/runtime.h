#ifndef HLX_RUNTIME_H
#define HLX_RUNTIME_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Print
void hlx_print(const char* msg);
void hlx_print_int(long long n);
void hlx_print_float(double f);
void hlx_print_bool(int b);

// Math
long long hlx_abs_int(long long n);
double    hlx_abs_float(double f);
double    hlx_sqrt(double n);
double    hlx_pow(double base, double exp);
long long hlx_max(long long a, long long b);
long long hlx_min(long long a, long long b);

// String
int   hlx_strlen(const char* s);
char* hlx_strcat_new(const char* a, const char* b);
int   hlx_strcmp(const char* a, const char* b);

// Type conversion
long long hlx_str_to_int(const char* s);
double    hlx_str_to_float(const char* s);
char*     hlx_int_to_str(long long n);
char*     hlx_float_to_str(double f);
char*     hlx_bool_to_str(int b);

// Error
void hlx_panic(const char* msg, int line);
void hlx_assert(int cond, const char* msg, int line);

// Memory
void* hlx_alloc(int size);
void  hlx_free(void* ptr);

#endif
