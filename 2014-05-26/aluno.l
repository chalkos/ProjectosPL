%{
#include "y.tab.h"
%}

%%

[\(\)\,] return *yytext;

"Par"         return PAR;
"Avaliacao"   return AVALIACAO;
"Disc"        return DISC;
"Disciplinas" return DISCIPLINAS;
"Ident"       return IDENT;

\"[^\"]*\"                   return str;
[0-9]{4}\-[0-9]{2}\-[0-9]{2} return data;
[0-9]{1,2}                   return num;
[0-9]\.[0-9]{1,2}            return real;

[ \t\n] ;

<<EOF>> return '$';
