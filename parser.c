#include <stdio.h>
#include <string.h>

void checkGrammar(char *str) {
    int len = strlen(str);

    // Base case: If input is "a", it's valid
    if (strcmp(str, "a") == 0) {
        printf("Valid string\n");
        return;
    }

    // Check if input follows the pattern "i E t S S'"
    if (str[0] == 'i' && len >= 4 && str[1] == 'b' && str[2] == 't') {
        int e_count = 0;
        for (int i = 3; i < len; i++) {
            if (str[i] == 'e') e_count++;
        }

        // If it contains 'e' before another valid substring, it's valid
        if (e_count > 0 || strcmp(&str[3], "a") == 0) {
            printf("Valid string\n");
            return;
        }
    }

    printf("Invalid string\n");
}
