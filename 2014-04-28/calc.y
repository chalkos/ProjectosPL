%{
#include <stdio.h>

int registos[26] = {0};
%}

%token id num SEP

%union{
    char tipoid;
    int tiponum;
    }

%type <tipoid> id
%type <tiponum> num Exp Termo Fator

%start Calc

%%

Calc : ListaInst '$' { printf("\nThat's all folks!\n"); };

ListaInst : ListaInst SEP Inst
          | Inst
          ;

Inst : Leitura
     | Escrita
     | Atrib
     | Dump
     ;

Dump : '*' '*' { int i;
                 for(i=0; i<26; i++)
                    printf("%c :: %d\n", i+'a', registos[i]);
                 printf("\nCalc >> "); } ;

Leitura : '?' id { printf("\nIntroduza o valor : ");
                   scanf("%d", registos+$2-'a');
                   while( getchar() != '\n' );
                   printf("\nCalc >> "); } ;

Escrita : '!' Exp { printf("\n%d", $2);
                    printf("\nCalc >> "); } ;

Atrib : id '=' Exp { registos[$1-'a'] = $3;
                     printf("\nCalc >> "); } ;

Exp : Exp '+' Termo { $$ = $1 + $3; }
    | Exp '-' Termo { $$ = $1 - $3; }
    | Termo { $$ = $1; }
    ;

Termo : Termo '*' Fator { $$ = $1 * $3; }
      | Termo '/' Fator { if(!$3)
                            { printf("\nDivisao por 0!");
                              $$ = $1;
                            }
                          else
                            $$ = $1 / $3; }
      | Fator { $$ = $1; }
      ;

Fator : id { $$ = registos[$1 - 'a']; }
      | num { $$ = $1; }
      | '(' Exp ')' { $$ = $2; }
      ;

