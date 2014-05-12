%{
#include <string.h>
#include "cfg.lib.h"
#include "cfg.tab.h"
%}
%x ler_string
%x ler_numero
%x campos
%%
"=titulo="  {BEGIN ler_string; return TITULO;}
"=nprovas=" {BEGIN ler_numero; return NPROVAS;}
"=ntop="    {BEGIN ler_numero; return NTOP;}
"=campos="  {BEGIN campos;     return CAMPOS;}
"=score="   {BEGIN ler_numero; return SCORE;}

<ler_string>[^\n]+ {cfglval.cfg_str = cfgtext;
                    cfgtext[strlen(cfgtext)-1] = '\0';
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
<*>.     { printf("flex lixo: %c (%d)\n", *cfgtext, *cfgtext); }

%%

int cfgwrap(){
    return 1;
}