#include <stdio.h>
#include "utils.h"

int main(void) {
    if (!str_eq("a", "a")) return 1;
    if (str_eq("a", "b")) return 2;
    printf("unit_tests OK\n");
    return 0;
}