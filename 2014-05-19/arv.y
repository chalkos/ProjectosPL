%token num
%{
#include "arv.lib.h"
#include <stdio.h>
#define YYERROR_VERBOSE
%}

%union{
    int valor;
    Arv arvore;
}
%type<valor> num
%type<arvore> Arvore
%start Z
%%
Z : Arvore '$' { arv_verifica( $1 );
                 arv_inorder( $1 );
                 arv_soma( $1 );
                 arv_conta( $1 );
                 yylex_destroy();
                 YYACCEPT; };
Arvore : '(' num Arvore Arvore ')' { $$ = cons_arv($2, $3, $4); }
       | '(' ')'                   { $$ = cons_arv_NIL(); }
       ;

%%
int yyerror( char* s ){
    fprintf(stderr, "%s", s);
    return 0;
}

int main(){
    yyparse();
    return 0;
}
