
%{
#include "tokens.h"

char* tipostr = "char *";
char* tipoint = "int";
%}

%%
[ \r\t\n]+ ;

"<ga>"       return OGA;
"</ga>"      return CGA;
\-\>         return ODLIST;
\|           return SEPDLIST;
\;           return SEP;
\(           return ODER;
\)           return CDER;


"INT"                {yylval= tipoint; return SIMBT;}
"STR"                {yylval= tipostr; return SIMBT;}
"cons_"[a-zA-Z0-9_]+ {yylval= strdup(yytext); return ID;}
[A-Z][a-zA-Z_0-9]*      {yylval= strdup(yytext); return SIMBN;}

.            return ERRO;

<<EOF>>  return 0;
