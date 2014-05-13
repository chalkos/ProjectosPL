#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "csv.lib.h"

/* -----------------------------------
 * Constructor Function Implementations
 * -----------------------------------
 */

Linhas  cons_csv_Linhas( Linha a1, Linhas a2)
{
    Linhas aux0;

  aux0 = (Linhas) malloc(sizeof(struct sLinhas));
  aux0->flag = PScons_csv_Linhas;
  aux0->u.d1.s1 = a1;
  aux0->u.d1.s2 = a2;
  return(aux0);
}

Linhas  cons_csv_Linhas_NIL()
{
    Linhas aux0;

  aux0 = (Linhas) malloc(sizeof(struct sLinhas));
  aux0->flag = PScons_csv_Linhas_NIL;
  return(aux0);
}


Linha  cons_csv_Linha_Campo( Linha a1, char * a2)
{
    Linha aux0;

  aux0 = (Linha) malloc(sizeof(struct sLinha));
  aux0->flag = PScons_csv_Linha_Campo;
  aux0->u.d1.s1 = a1;
  aux0->u.d1.s2 = a2;
  return(aux0);
}

Linha  cons_csv_Campo( char * a1)
{
    Linha aux0;

  aux0 = (Linha) malloc(sizeof(struct sLinha));
  aux0->flag = PScons_csv_Campo;
  aux0->u.d2.s1 = a1;
  return(aux0);
}


/* -----------------------------------
 * Custom Function Implementations
 * -----------------------------------
 */
 
void csv_print( Linhas lcsv ){

    Linha ls;

    while (lcsv->flag != PScons_csv_Linhas_NIL){
        ls = lcsv->u.d1.s1;
        switch (ls->flag){
            case PScons_csv_Campo:
                printf("%s\n",ls->u.d1.s2 );
                break;
            case PScons_csv_Linha_Campo:
                while(ls-> flag == PScons_csv_Linha_Campo){
                    printf("%s\n",ls->u.d1.s2 );
                    ls = ls ->u.d1.s1;
                }
                break;
        }
        lcsv =  lcsv->u.d1.s2;
    }
}

Linha csv_Linha_reverse( Linha l ){
    char * campo;
    Linha aux;

    if (l->flag == PScons_csv_Campo)
        return l;
    campo = (char*) malloc (sizeof (strlen(l->u.d1.s2)));
    campo = l->u.d1.s2;
    l = l->u.d1.s1;
    aux = cons_csv_Campo(campo);


    while(l->flag == PScons_csv_Linha_Campo){
        campo = (char*)malloc (sizeof (strlen(l->u.d1.s2)));
        campo = l->u.d1.s2;
        l = l->u.d1.s1;
        aux = cons_csv_Linha_Campo(aux,campo);

    }
    return aux;
}



