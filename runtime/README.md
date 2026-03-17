# HOLEXA Runtime v1.0.0

The HOLEXA runtime provides core built-in functions for compiled HOLEXA programs.

## Functions

### Print
- `hlx_print(msg)` — print string
- `hlx_print_int(n)` — print integer
- `hlx_print_float(f)` — print float
- `hlx_print_bool(b)` — print boolean

### Math
- `hlx_abs_int(n)` — absolute value
- `hlx_sqrt(n)` — square root
- `hlx_pow(base, exp)` — power
- `hlx_max(a, b)` — maximum
- `hlx_min(a, b)` — minimum

### String
- `hlx_strlen(s)` — string length
- `hlx_strcat_new(a, b)` — concatenate
- `hlx_strcmp(a, b)` — compare

### Type Conversion
- `hlx_str_to_int(s)` — string to int
- `hlx_int_to_str(n)` — int to string
- `hlx_float_to_str(f)` — float to string

### Error
- `hlx_panic(msg, line)` — fatal error
- `hlx_assert(cond, msg, line)` — assertion

## Build
```sh
gcc -c runtime.c -o runtime.o
```
