#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser/parser.h"

bool active = true;

bool should_quit(const char* input);
bool helping(const char* input);

int main(void) {
    printf("Simple C Calculator\n");
    printf("Type \"quit\" or \"q\" to quit.\n");

    while (active) {
        char response[100];
        printf("Enter a calculation:\n");

        if (!fgets(response, sizeof(response), stdin)) break;

        response[strcspn(response, "\n")] = '\0';

        if (should_quit(response)) {
            active = false;
            continue;
        }

        if (helping(response)) {
            continue;
        }

        double result;
        if (parse(response, &result)) {
            printf("Result: %f\n", result);
        } else {
            printf("Invalid input.\n");
        }

        printf("\n");
    }

    return 0;
}

// https://www.tutorialspoint.com/convert-a-string-to-uppercase-in-c
void string_to_upper(char* in) {
    for (int i = 0; in[i] != '\0'; i++) {
        in[i] = (char)toupper(in[i]);
    }
}

bool should_quit(const char* input) {
    if (input == NULL) {
        return false;
    }

    char *in = malloc(strlen(input) + 1 * sizeof(char));
    if (!in) {
        printf("malloc failed, quitting...\n");
        return true;
    }

    strcpy(in, input);
    string_to_upper(in);

    if (strcmp(in, "QUIT") == 0 || strcmp(in, "Q") == 0) {
        printf("Quitting...\n");
        free(in);
        return true;
    }

    free(in);
    return false;
}

bool helping(const char* input) {
    if (input == NULL) {
        return false;
    }

    char in[strlen(input) + 1];
    strcpy(in, input);
    string_to_upper(in);

    if (strcmp(in, "HELP") == 0 || strcmp(in, "H") == 0) {
        printf("Type a valid equation using numbers, and any of the operators:\n");
        printf("*, /, +, -,\n");
        printf("Type QUIT to quit.\n");
        return true;
    }

    return false;
}
