%token CONFIG LOAD IMPORT PRINT SAVE FSAVE QUIT FQUIT FICHEIRO
%{
#include <stdio.h>
#include "cmd.lib.h"
%}
%union{ char* cmd_ficheiro; }
%type <cmd_ficheiro> FICHEIRO
%start Comandos
%%
Comandos : Comandos '\n' Comando
         | 
         ;

Comando : Config
        | Load
        | Import
        | Print
        | Save
        | Quit
        | error { printf("Comando inválido.\n"); yyclearin; yyerrok; }
        ;

Config : CONFIG FICHEIRO { cmd_config($2); };

Load : LOAD FICHEIRO { cmd_load($2); };

Import : IMPORT FICHEIRO { cmd_import($2); };

Save : SAVE FICHEIRO { cmd_save($2, 0); }
     | FSAVE FICHEIRO { cmd_save($2, 1); }
     ;

Print : PRINT { cmd_print(); };

Quit : QUIT  { cmd_quit(0); }
     | FQUIT { cmd_quit(1); }
     ;

%%
int yyerror( char* s ){
    //fprintf(stderr, "%s", s);
}

int main(){
    cmdparse();
    return 0;
}

