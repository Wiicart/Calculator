//
// Created by Christopher on 8/6/25.
//

#ifndef TOKEN_H
#define TOKEN_H
#include <stdbool.h>

// https://blog.darrien.dev/posts/writing-calc-parser/
typedef enum {
    LITERAL,
    ADDITION,
    SUBTRACTION,
    MULTIPLICATION,
    DIVISION,
    POWER
} TokenType;

/**
 * A Token for expression tokenization.\n
 * Only Tokens with type LITERAL should contain a value.
 */
typedef struct {
    TokenType type;
    union {
        double value; // Only to be used if TokenType is LITERAL
    };
} Token;

extern const Token TOKEN_ADDITION;
extern const Token TOKEN_SUBTRACTION;
extern const Token TOKEN_MULTIPLICATION;
extern const Token TOKEN_DIVISION;
extern const Token TOKEN_POWER;

// Creates a Token of the type LITERAL, with the specified value.
Token token_literal(const double value);

// Applies the operator token to the right and left values, and assigns it to the out pointer.
// Returns false if the operation is invalid.
bool token_apply(const Token operator, const Token left, const Token right, double *out);

// Provides a token based on a char input, such as '+' -> TOKEN_ADDITION
// Will be an extern const, so do not attempt to free it.
bool token_from_char(const char c, Token *out);

bool token_result(const Token *tokens, int token_count, double *out);

bool is_literal(const Token token);

bool is_operator(const Token token);


#endif //TOKEN_H
