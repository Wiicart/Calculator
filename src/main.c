#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "parser/parser.h"

bool active = true;

bool should_quit(const char* input);

int main(void) {
    printf("Simple C Calculator\n");
    printf("Type \"quit\" or \"q\" to quit.\n");

    while (active) {
        char response[100];
        printf("Enter a calculation:\n");
        scanf("%99s", response);

        if (should_quit(response)) active = false;
        printf("Result: %f\n", parse(response));
    }

    return 0;
}

// https://www.tutorialspoint.com/convert-a-string-to-uppercase-in-c
void string_to_upper(char* in) {
    for (int i = 0; in[i] != '\0'; i++) {
        if (in[i] >= 'a' && in[i] <= 'z') {
            in[i] = in[i] - 32;
        }
    }
}

bool should_quit(const char* input) {
    if (input == NULL) {
        return false;
    }

    char in[strlen(input) + 1];
    strcpy(in, input);
    string_to_upper(in);

    if (strcmp(in, "QUIT") == 0 || strcmp(in, "!") == 0) {
        printf("Quitting...\n");
        return true;
    }

    return false;
}
