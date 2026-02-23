#include <string.h>
#include "utils.h"

bool str_eq(const char *a, const char *b) {
    if (!a || !b) return false;
    return strcmp(a, b) == 0;
}