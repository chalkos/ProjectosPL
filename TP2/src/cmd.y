%token CONFIG LOAD IMPORT PRINT SAVE FSAVE QUIT FQUIT FICHEIRO
%{
#include <stdio.h>
#include "cmd.lib.h"
%}
%union{ char* cmd_ficheiro; }
%type <cmd_ficheiro> FICHEIRO
%start Comandos
%%
Comandos : Comando '\n' Comandos
         | 
         ;

Comando : Config
        | Load
        | Import
        | Print
        | Save
        | Quit
        | {/*| error  { printf("Comando inválido2.\n%s", CMD_PROMPT); yyclearin; yyerrok; }*/}
        ;

Config : CONFIG FICHEIRO { cmd_config($2); printf(CMD_PROMPT); };

Load : LOAD FICHEIRO { cmd_load($2); printf(CMD_PROMPT); };

Import : IMPORT FICHEIRO { cmd_import($2); printf(CMD_PROMPT); };

Save : SAVE FICHEIRO { cmd_save($2, 0); printf(CMD_PROMPT); }
     | FSAVE FICHEIRO { cmd_save($2, 1); printf(CMD_PROMPT); }
     ;

Print : PRINT { cmd_print(); printf(CMD_PROMPT); };

Quit : QUIT  { cmd_quit(0); printf(CMD_PROMPT); }
     | FQUIT { cmd_quit(1); printf(CMD_PROMPT); }
     ;

%%
int yyerror( char* s ){
    //fprintf(stderr, "%s", s);
}

