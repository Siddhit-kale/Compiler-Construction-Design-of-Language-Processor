%{
    #include <stdio.h>
    #include <string.h>
%}

%%

charusat { printf("university"); }
CHARUSAT { printf("university"); }
[Cc]harusat { printf("university"); }
. { printf("%c", yytext[0]); }
\n { printf("\n"); }

%%

int main() {
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}