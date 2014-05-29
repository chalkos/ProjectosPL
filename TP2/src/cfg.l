%{
#define YY_NO_INPUT
#include <string.h>
#include "cfg.lib.h"
#include "cfg.tab.h"
%}
%option nounput
%option yylineno
%x ler_string
%x ler_numero
%x ler_tempo
%x campos
%%
"=titulo="  {BEGIN ler_string; return TITULO;}
"=nprovas=" {BEGIN ler_numero; return NPROVAS;}
"=ntop="    {BEGIN ler_numero; return NTOP;}
"=campos="  {BEGIN campos;     return CAMPOS;}
"=tempo="   {BEGIN ler_numero; return TEMPO;}
"=chave="   {BEGIN ler_numero; return CHAVE;}
"=nome="    {BEGIN ler_numero; return NOME;}


<ler_string>[^\n]+ {cfglval.cfg_str = strdup(cfgtext);
                    BEGIN 0;
                    return str;}
<ler_numero>\$     return '$';
<ler_numero>[0-9]+ {cfglval.cfg_num = atoi(cfgtext);
                    BEGIN 0;
                    return num;}

<campos>[0-9]+ { cfglval.cfg_num = atoi(cfgtext);
                 return num;}
<campos>\$     { return '$'; }
<campos>\;     { return ';'; }
<campos>\n     { BEGIN 0; return '\n'; }

<*><<EOF>>  return '$';

[\n]+       return '\n';

<*>[ \t] ;
<*>.     { /*printf("flex: %c (%d)\n", *cfgtext, *cfgtext);*/ }

%%

int cfgwrap(){
    return 1;
}
