%{
    #include <stdio.h>
    int char_count = 0, word_count = 0, line_count = 0;
    extern FILE *yyin;
%}

%%

[A-Za-z0-9]+ { word_count++; char_count += yyleng; }
[\t]+ { char_count += yyleng; }
\n { line_count++; char_count++; }
. { char_count++; }

%%

int main() {
    char filename[100];
    printf("Enter the filename: ");
    scanf("%s", filename);

    FILE *file = fopen(filename, "r");
    if (!file) {  // Check if the file was opened successfully
        printf("Error opening file: %s\n", filename);
        return 1;
    }

    yyin = file;
    yylex();
    fclose(file);

    printf("Characters: %d\n", char_count);
    printf("Words: %d\n", word_count);
    printf("Lines: %d\n", line_count);

    return 0;
}

int yywrap() {
    return 1;
}

