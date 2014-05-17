%token str
%{
#include <stdio.h>
#include <stdlib.h>
#include "csv.lib.h"

#define YYERROR_VERBOSE

extern unsigned int csvlineno;
extern int csvlex (void);
extern void csvlex_destroy();
%}
%union{
	char * csv_str;
	
	Linhas csv_Linhas;
	Linha  csv_Linha;
	Campo  csv_Campo;

} 

%type<csv_str> str
%type<csv_Campo> Campo
%type<csv_Linhas> X Linhascsv
%type<csv_Linha> Linha
%start X

%%
X : Linhascsv '$' { $$ = $1; 
                    csv_Linhas_validate($$);
                    csv_import_csv($$);
                    csvlex_destroy();
                    YYACCEPT;};

Linhascsv : Linha '\n' Linhascsv {$1 = csv_Linha_reverse($1);
                                  $$ = cons_csv_Linhas ($1,$3);}
          | {$$ = cons_csv_Linhas_NIL();}
          ;

Linha : Linha ';' Campo {$$ = cons_csv_Linha ($1,$3);}
      | Campo {$$ = cons_csv_Linha_Fim ($1);}
      ;

Campo : str {$$ = cons_csv_Campo ($1);}
      | {$$ = cons_csv_Campo_NIL();}
      ;

%%
int yyerror( char* s ){
    fprintf(stderr, "Line %d: %s\n", csvlineno, s);
    return 0;
}
