%{
#define YY_NO_INPUT
#include <string.h>
#include "cmd.tab.h"
#include "cmd.lib.h"
%}
%option nounput
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
"quit!" return FQUIT;
"q!"    return FQUIT;

<<EOF>>  return FQUIT;

[\n]+    { return '\n'; }

<ficheiro>[^\n]+ { /* se houver erros, tentar um duplicate aqui */
                   //cmdlval.cmd_ficheiro = strdup(cmdtext);
                   cmdlval.cmd_ficheiro = cmdtext;
                   BEGIN 0;
                   return FICHEIRO;
                 }
<ficheiro>[\n]    { BEGIN 0;
                    printf("Comando inválido6.\n%s", CMD_PROMPT);
                    return '\n'; }

 /** capturar comandos inválidos especiais **/
[clis]\n          { printf("Comando inválido1.\n%s", CMD_PROMPT); }
[^clipsq\n][^\n]* { printf("Comando inválido2.\n%s", CMD_PROMPT); }
"q"[^\n]+         { printf("Comando inválido3.\n%s", CMD_PROMPT); }
"p"[^\n]+         { printf("Comando inválido4.\n%s", CMD_PROMPT); }
"config"[^ ]      { printf("Comando inválido5.\n%s", CMD_PROMPT); }

. ;

%%

int cmdwrap(){
    return 1;
}
