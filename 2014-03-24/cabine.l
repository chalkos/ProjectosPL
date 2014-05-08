%{
    // variáveis
    int saldo=0;

    // funcoes

%}

%x POUSADO LEVANTADO MOEDA NUMEROS

%%
    BEGIN POUSADO;

<*>[ \t\n]   ;
<POUSADO>LEVANTAR { printf("maq: Pode realizar chamadas ou meter moedas.\n");
                    BEGIN LEVANTADO;}

<LEVANTADO>POUSAR { printf("maq: terminado. troco = %d\n", saldo);
                    BEGIN POUSADO;}
<LEVANTADO>MOEDA   BEGIN MOEDA;
<LEVANTADO>T=      BEGIN NUMEROS;

<MOEDA>, ;
<MOEDA>\. { printf("maq: novo saldo = %d\n", saldo);
            BEGIN LEVANTADO;}
<MOEDA>5c         saldo+=5;
<MOEDA>10c        saldo+=10;
<MOEDA>20c        saldo+=20;
<MOEDA>50c        saldo+=50;
<MOEDA>1e         saldo+=100;
<MOEDA>2e         saldo+=200;
<MOEDA>[0-9]+[ce] printf("maq: Moeda invalida: %s\n", yytext);

<NUMEROS>00[0-9]+ {
                    if( saldo>=150 ){
                        printf("maq: Chamada internacional = 1,5 euros.\n");
                        saldo-=150;
                        printf("maq: Novo saldo = %d\n", saldo);
                    }else
                        printf("maq: Saldo insuficiente = %d\n", saldo);
                    BEGIN LEVANTADO;
                  }
<NUMEROS>(601|641)[0-9]{6} { printf("maq: numeros vermelhos nao permitidos.\n");
                             BEGIN LEVANTADO; }
<NUMEROS>2[0-9]{8} {
                    if( saldo>=25 ){
                        printf("maq: Chamada nacional = 25 centimos.\n");
                        saldo-=25;
                        printf("maq: Novo saldo = %d\n", saldo);
                    }else
                        printf("maq: Saldo insuficiente = %d\n", saldo);
                    BEGIN LEVANTADO;
                   }
<NUMEROS>800[0-9]{6}  { printf("maq: Chamada verde - %s\n",yytext); BEGIN LEVANTADO; }
<NUMEROS>808[0-9]{6}  {
                        if( saldo>=10 ){
                            printf("maq: Chamada azul = 10 centimos.\n");
                            saldo-=10;
                            printf("maq: Novo saldo = %d\n", saldo);
                        }else
                            printf("maq: Saldo insuficiente = %d\n", saldo);
                        BEGIN LEVANTADO;
                      }
<*>. ;
%%
int yywrap(){
    printf("acabou. mostrar troco.\n");
}
