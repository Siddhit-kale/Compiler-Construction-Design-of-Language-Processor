%{
    #include <stdio.h>
    #include <stdlib.h>
    void yyerror(const char *s);
    int yylex();
%}

%token I T E A B

%%
S  : I E T S S_ | A ;
S_ : E S | /* epsilon */ ;
E  : B ;

%%

void yyerror(const char *s) {
    printf("Invalid string\n");
    exit(1);
}

int main() {
    if (yyparse() == 0)
        printf("Valid string\n");
    return 0;
}
