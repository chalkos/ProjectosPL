%{
#include "arv.lib.h"
#include "y.tab.h"
%}

%%
[0-9]+  { yylval.valor = atoi(yytext); return num; }
\(      return '(';
\)      return ')';
<<EOF>> return '$';
[ \n\t] ;
.       ;

%%

int yywrap(){
    return 1;
}
