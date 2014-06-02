%token CONFIG LOAD IMPORT PRINT SAVE FSAVE QUIT FQUIT FICHEIRO
%{
#include <stdio.h>
#include "cmd.lib.h"

#define YYERROR_VERBOSE

extern int cmdlex (void);
extern void cmdlex_destroy();
extern void sav_load_done();
extern int sav_loading;
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

Config : CONFIG FICHEIRO { cmd_config($2); printf(CMD_PROMPT); }
       | CONFIG
       ;

Load : LOAD FICHEIRO { cmd_load($2); if(!sav_loading) printf(CMD_PROMPT); }
     | LOAD
     ;

Import : IMPORT FICHEIRO { cmd_import($2); if(!sav_loading) printf(CMD_PROMPT); }
       | IMPORT
       ;

Save : SAVE FICHEIRO { cmd_save($2, 0); printf(CMD_PROMPT); }
     | FSAVE FICHEIRO { cmd_save($2, 1); printf(CMD_PROMPT); }
     | SAVE
     | FSAVE
     ;

Print : PRINT { cmd_print(); printf(CMD_PROMPT); };

Quit : QUIT  { if(cmd_quit()){
                    YYACCEPT;
               }else{
                    printf(CMD_PROMPT);
               }}
     | FQUIT { YYACCEPT;}
     ;

%%
int yyerror( char* s ){
    //fprintf(stderr, "%s", s);
    return 0;
}

