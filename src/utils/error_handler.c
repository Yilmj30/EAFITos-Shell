#include <stdio.h>
#include <stdarg.h>
#include "utils.h"

void print_error(const char *msg) {
    fprintf(stderr, "Error: %s\n", msg);
}

void print_errorf(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
}