%{
#include "y.tab.h"
%}

%%
\+ return '+';
\- return '-';
\* return '*';
\/ return '/';
\( return '(';
\) return ')';
\= return '=';
\! return '!';
\? return '?';

[a-z] { yylval.tipoid = *yytext; return id; }

[0-9]+ {yylval.tiponum = atoi(yytext); return num; }

\n return SEP;

[ \t] ;
<<EOF>> return '$';
. ;

