%{
#include <stdio.h>
#include <stdlib.h>
%}

/* Regular Expressions for Token Categories */
%%
"int"|"float"|"return"|"if"|"else"|"while"|"for"|"char"|"double"    { printf("Keyword: %s\n", yytext); }
[a-zA-Z_][a-zA-Z0-9_]*                                              { printf("Identifier: %s\n", yytext); }
[0-9]+                                                              { printf("Constant: %s\n", yytext); }
\"(\\.|[^\\"])*\"                                                   { printf("String: %s\n", yytext); }
[\+\-\*/%=<>!&|]                                                    { printf("Operator: %s\n", yytext); }
[;(),{}\[\]]                                                        { printf("Punctuation: %s\n", yytext); }
"//".*                                                              { printf("Comment: %s\n", yytext); }
"/*"([^*]|\*+[^*/])*\*+"/"                                           { printf("Comment: %s\n", yytext); }
.                                                                   { printf("Lexical Error: %s\n", yytext); }
%%

int main() {
    printf("Enter the C source code: \n");
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}
