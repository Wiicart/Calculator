//
// Created by Christopher on 8/6/25.
//

#include "token.h"

#include <stddef.h>
#include <tgmath.h>

const Token TOKEN_ADDITION = {ADDITION};
const Token TOKEN_SUBTRACTION = {SUBTRACTION};
const Token TOKEN_MULTIPLICATION = {MULTIPLICATION};
const Token TOKEN_DIVISION = {DIVISION};
const Token TOKEN_POWER = {POWER};

Token token_literal(const double value) {
    Token token = {.value = value, .type = LITERAL};
    return token;
}

bool token_apply(const Token operator, const Token left, const Token right, double *out) {
    if (left.type != LITERAL || right.type != LITERAL || out == NULL) {
        return false;
    }

    switch (operator.type) {
        case ADDITION: *out = left.value + right.value; break;
        case SUBTRACTION: *out = left.value - right.value; break;
        case MULTIPLICATION: *out = left.value * right.value; break;
        case DIVISION: *out = left.value / right.value; break;
        case POWER: *out = pow(left.value, right.value); break;;
        default: return false;
    }

    return true;
}

bool token_from_char(const char c, Token *out) {
    const Token* temp;
    switch (c) {
        case '+': temp = &TOKEN_ADDITION; break;
        case '-': temp = &TOKEN_SUBTRACTION; break;
        case '*': temp = &TOKEN_MULTIPLICATION; break;
        case '/': temp = &TOKEN_DIVISION; break;
        case '^': temp = &TOKEN_POWER; break;
        default: return false;
    }

    *out = *temp;
    return true;
}

bool token_result(const Token *tokens, int token_count, double *out) {
    double result = 0;

    const Token *left = NULL;
    const Token *right = NULL;
    const Token *operator = NULL;

    for (int i = 0; i < token_count; i++) {
        const Token *token = &tokens[i];
        bool is_lit = is_literal(*token);

        if (left == NULL) {
            if (!is_lit) return false;
            left = token;
            result = left->value;
        } else if (operator == NULL) {
            if (is_lit) return false;
            operator = token;
        } else {
            if (!is_lit) return false;

            right = token;

            double temp;
            if (!token_apply(*operator, *left, *right, &temp)) {
                return false;
            }

            result = temp;
            left = &(Token){.value = result, .type = LITERAL};

            operator = NULL;
            right = NULL;
        }
    }

    if (operator != NULL) return false;

    *out = result;
    return true;
}

bool is_literal(const Token token) {
    return token.type == LITERAL;
}

bool is_operator(const Token token) {
    return token.type != LITERAL;
}
