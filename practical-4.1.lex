%{
#include <stdio.h>
#include <string.h>
#define MAX_LEN 1000

char text[MAX_LEN];
char oldWord[100], newWord[100];
%}

%%
[a-zA-Z0-9_]+ {
    if (strcmp(yytext, oldWord) == 0) {
        printf("%s", newWord);
    } else {
        printf("%s", yytext);
    }
}
. { printf("%s", yytext); }

%%

int main() {
    printf("Enter text: ");
    fgets(text, MAX_LEN, stdin);
    text[strcspn(text, "\n")] = 0;
    
    printf("Enter the word to be replaced: ");
    scanf("%s", oldWord);
    
    printf("Enter the new word: ");
    scanf("%s", newWord);
    
    yy_scan_string(text);
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}
