//
// Created by Christopher on 8/6/25.
//

#include "parser.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "../token/token.h"

static char* remove_spaces(const char* in);
static bool flush_and_append(char *buffer, int *buffer_pos, Token *tokens, int *tokens_pos);
bool is_empty(const char* in);
bool is_operator_char(const char in);

bool parse(const char *in, double *out) {
    char *calc = remove_spaces(in);

    const int len = strlen(calc);

    Token tokens[len];
    int tokens_pos = 0;

    char buffer[len];
    int buffer_pos = 0;
    for (int i = 0; i < len; i++) {
        char current = calc[i];

        if (is_operator_char(current)) {
            if (!flush_and_append(buffer, &buffer_pos, tokens, &tokens_pos)) {
                free(calc);
                return false;
            }

            Token operator;
            token_from_char(current, &operator);
            tokens[tokens_pos++] = operator;
        } else if (isdigit(current) || current == '.') {
            buffer[buffer_pos++] = current;
        } else {
            free(calc);
            return false;
        }
    }

    free(calc);
    if (!flush_and_append(buffer, &buffer_pos, tokens, &tokens_pos)) {
        return false;
    }

    double result;
    if (!token_result(tokens, tokens_pos, &result)) {
        return false;
    }

    *out = result;

    return true;
}

// flushes the buffer into a token, then adds it to the tokens array.
// returns false if an error occurred.
static bool flush_and_append(char *buffer, int *buffer_pos, Token *tokens, int *tokens_pos) {
    buffer[*buffer_pos] = '\0';


    char *end;
    double val = strtod(buffer, &end);

    if (end == buffer) {
        return false;
    }

    tokens[*tokens_pos] = token_literal(val);
    (*tokens_pos)++;

    *buffer_pos = 0;
    return true;
}

// https://stackoverflow.com/questions/1726302/remove-spaces-from-a-string-in-c
static char* remove_spaces(const char* in) {
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

bool is_empty(const char *in) {
    return in == NULL || in[0] == '\0';
}

bool is_operator_char(const char in) {
    return in == '+' || in == '-' || in == '*' || in == '/' || in == '^';
}
