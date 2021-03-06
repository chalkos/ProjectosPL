%token TITULO NPROVAS NTOP CAMPOS TEMPO CHAVE NOME str num
%{
#include <stdio.h>
#include <stdlib.h>
#include "cfg.lib.h"

#define YYERROR_VERBOSE

extern unsigned int cfglineno;
extern int cfglex (void);
extern int gco_set_Config(Confs cfg);
extern void cfglex_destroy();
%}
%union{
    char* cfg_str;
    int cfg_num;
    
    Confs cfg_confs;
    Conf cfg_conf;
    Lcampos cfg_campos;
}
%type <cfg_str> str Titulo
%type <cfg_num> num Nprovas Ntop Tempo Campo Chave Nome
%start Z

%type <cfg_confs> Z Configuracoes
%type <cfg_conf> Configuracao
%type <cfg_campos> Lcampos Campos
%%
Z : Configuracoes '$' { $$ = $1;
                        cfglex_destroy();
                        if( gco_set_Config($$) == 0 )
                            YYACCEPT;
                        YYABORT; };

Configuracoes : Configuracao '\n' Configuracoes {$$ = cons_cfg_Confs($1,$3);}
              | { $$ = cons_cfg_Confs_NIL(); }
              ;

Configuracao : Titulo  { $$ = cons_cfg_Conf_Titulo($1); }
             | Nprovas { $$ = cons_cfg_Conf_Nprovas($1); }
             | Ntop    { $$ = cons_cfg_Conf_Ntop($1); }
             | Tempo { $$ = cons_cfg_Conf_Tempo($1); }
             | Campos  { $$ = cons_cfg_Conf_Campos($1); }
             | Chave { $$ = cons_cfg_Conf_Chave($1); }
             | Nome { $$ = cons_cfg_Conf_Nome($1); }
             ;

Titulo  : TITULO str     { $$ = $2; };
Nprovas : NPROVAS num    { $$ = $2; };
Ntop    : NTOP num       { $$ = $2; };
Campos  : CAMPOS Lcampos { $$ = cfg_Lcampos_reverse( $2 ); }
Tempo   : TEMPO '$' num  { $$ = $3; };
Chave   : CHAVE '$' num  { $$ = $3; };
Nome    : NOME '$' num   { $$ = $3; };


Lcampos : Lcampos ';' Campo { $$ = cons_cfg_Lcampos_Lcampos($1,$3); }
        | Campo             { $$ = cons_cfg_Lcampos_Campo($1); }
        ;

Campo : '$' num { $$ = $2; };

%%
int yyerror( char* s ){
    fprintf(stderr, "Line %d: %s\n", cfglineno, s);
    return 0;
}


