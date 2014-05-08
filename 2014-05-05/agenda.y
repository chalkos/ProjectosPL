%{
#include <stdio.h>
%}
%token IAGENDA FAGENDA
%token IENTRADA FENTRADA
%token INOME FNOME
%token ITELEFONE FTELEFONE
%token IGRUPO FGRUPO
%token IREF FREF
%token IEMAIL FEMAIL

%token chave valor numero texto

%start Agenda

%%

Agenda : IAGENDA Lista FAGENDA {printf("reconheci uma agenda\n");} ;

Lista : Lista Entrada
      | Lista Grupo
      | Entrada
      | Grupo
      ;

Entrada : IENTRADA ListaAtrib '>' Nome Email Telefone FENTRADA ;

ListaAtrib : ListaAtrib Atrib
           |
           ;

Atrib : chave '=' valor ;

Nome : INOME texto FNOME ;

Email : IEMAIL texto FEMAIL ;
      |
      ;

Telefone : ITELEFONE numero FTELEFONE ;

Grupo : IGRUPO ListaAtrib '>' ListaG FGRUPO ;

ListaG : ListaG Entrada
       | ListaG Grupo
       | ListaG Ref
       | Entrada
       | Grupo
       | Ref
       ;

Ref : IREF ListaAtrib FREF ;

%%
int yyerror( char *s ){
    fprintf(stderr, "%s", s);
}

int main(){
    yyparse();
    return 0;
}
