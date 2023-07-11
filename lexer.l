%{
// Define constant values for each token type
#include "tokens.h"
//#include "lexer.tab.h"
%}

%%
[A-Z] { return NT; }     // Match nonterminals
[a-z] { return T; }      // Match terminals
"-->" { return GOES; }   // Match goes symbol
";"   { return SEMI; }   // Match semicolon
"|"   { return OR; }     // Match OR symbol
[\n]+   { return EOL; }    // Match end of line
[  \t]+ { /* ignore whitespace */ }
.                   ;                 /* catch-all rule for unmatched characters */

%%


// Entry point for the lexer
int yywrap() {
  return 1;
}
