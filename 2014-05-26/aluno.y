%{
#include <stdio.h>
%}
%token PAR AVALIACAO DISCIPLINAS DISC IDENT str num real data

%start Aluno
%%

Aluno : IdAluno AvalAluno DiscAluno '$' {printf("processo de aluno OK\n"); YYACCEPT;};

IdAluno : IDENT '(' str ',' data ',' str ',' str ')' ;

AvalAluno : AVALIACAO '(' ListaPar ')' ;

ListaPar : ListaPar Par
         | Par
         ;

Par : PAR '(' str ',' num ')' ;

DiscAluno : DISCIPLINAS '(' ListaDisc ')' ;

ListaDisc : ListaDisc Disc
          | Disc
          ;

Disc : DISC '(' str ',' str ',' real ')' ;

%%

void yyerror( char *s ){
    fprintf(stderr, "ERRO: %s\n", s);
}

int main(){
    yyparse();
    return 0;
}
