%token str
%{
#include <stdio.h>
#include <stdlib.h>
#include "csv.lib.h"
%}
%union{
	char * csv_str;
	
	Linhas csv_Linhas;
	Linha  csv_linha

}
%type<csv_str> Campo

%start X

%%
X : Linhascsv '$' {$$ = $1;}
  ;
}

Linhascsv : Linha '\n' Linhascsv {$$ = cons_csv_linhas ($1,$3);}
          | {$$ = cons_csv_Linhas_NIL();}
          ;

Linha : Linha ';' Campo {$$ = cons_csv_Linha_Campo ($1,$3);}
      | Campo {$$ = cons_csv_Campo ($1);}
      ;

Campo : str {$$ = $1;}
      ;

%%
int yyerror (char *s){
	fprintf (strdeerr," %s",s);
}

int main(){
	csvparse ();
	return 0;
}
