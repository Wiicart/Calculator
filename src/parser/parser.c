//
// Created by Christopher on 8/6/25.
//

#include "parser.h"

#include <stdlib.h>
#include <string.h>

#include "../context/calculation_context.h"

char* remove_spaces(const char* in);

double parse(char* in) {
    char *calc = remove_spaces(in);
    double first = calc[0] - '0';
    char op = calc[1];
    double second = calc[2] - '0';
    CalculationContext context = calc_context_new(first, second, op);

    free(calc);
    return calc_context_compute(context);
}

// https://stackoverflow.com/questions/1726302/remove-spaces-from-a-string-in-c
char* remove_spaces(const char* in) {
    size_t length = strlen(in);

    char* result = malloc(length + 1);

    const char* src = in;
    char* out = result;

    while (*src) {
        if (*src != ' ') {
            *out++ = *src;
        }
        src++;
    }

    *out = '\0';

    return result;
}
