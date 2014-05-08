%{
#include <string.h>
#include "cmd.tab.h"
%}
%x ficheiro
%%
"config " {BEGIN ficheiro; return CONFIG;}
"c "      {BEGIN ficheiro; return CONFIG;}

"load " {BEGIN ficheiro; return LOAD;}
"l "    {BEGIN ficheiro; return LOAD;}

"import " {BEGIN ficheiro; return IMPORT;}
"i "      {BEGIN ficheiro; return IMPORT;}

"print"  return PRINT;
"p"      return PRINT;

"save! " {BEGIN ficheiro; return FSAVE;}
"s! "    {BEGIN ficheiro; return FSAVE;}
"save "  {BEGIN ficheiro; return SAVE; }
"s "     {BEGIN ficheiro; return SAVE; }

"quit"   return QUIT;
"q"      return QUIT;
"quit! " return FQUIT;
"q! "    return FQUIT;

[\n]     return '\n';

<ficheiro>[^\n]+ { /* se houver erros, tentar um duplicate aqui */
                   //cmdlval.cmd_ficheiro = strdup(cmdtext);
                   cmdlval.cmd_ficheiro = cmdtext;
                   BEGIN 0;
                   return FICHEIRO;
                 }

[ \t] ;
.       { /*printf("flex lixo: %c (%d)\n", *yytext, *yytext)*/; }

%%

int cmdwrap(){
    return 0;
}
