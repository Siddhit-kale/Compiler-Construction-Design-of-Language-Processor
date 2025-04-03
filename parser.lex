%{
#include <stdio.h>
#include <string.h>

extern void checkGrammar(char *str);  // Function in C file
%}

%%

[a-z]+  { checkGrammar(yytext); }   // Match lowercase strings and check grammar
[ \t\n] ;  // Ignore spaces and newlines
.       { printf("Invalid string\n"); }  // Invalid character case

%%

int main() {
    yylex();
    return 0;
}

