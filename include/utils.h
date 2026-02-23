#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>

/* Comparación segura */
bool str_eq(const char *a, const char *b);

/* Errores */
void print_error(const char *msg);
void print_errorf(const char *fmt, ...);

#endif