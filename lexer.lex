%{
    #include "y.tab.h"
%}

%%
"i"      { return I; }
"t"      { return T; }
"e"      { return E; }
"a"      { return A; }
"b"      { return B; }
[ \t\n]  { /* Ignore whitespace */ }
.        { return 0; }  /* Invalid character */
%%

int yywrap() { return 1; }
