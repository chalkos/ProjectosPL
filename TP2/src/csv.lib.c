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


Linha  cons_csv_Linha( Linha a1, Campo a2)
{
    Linha aux0;

  aux0 = (Linha) malloc(sizeof(struct sLinha));
  aux0->flag = PScons_csv_Linha;
  aux0->u.d1.s1 = a1;
  aux0->u.d1.s2 = a2;
  return(aux0);
}

Linha  cons_csv_Linha_Fim( Campo a1)
{
    Linha aux0;

  aux0 = (Linha) malloc(sizeof(struct sLinha));
  aux0->flag = PScons_csv_Linha_Fim;
  aux0->u.d2.s1 = a1;
  return(aux0);
}


Campo  cons_csv_Campo( char * a1)
{
    Campo aux0;

  aux0 = (Campo) malloc(sizeof(struct sCampo));
  aux0->flag = PScons_csv_Campo;
  aux0->u.d1.s1 = a1;
  return(aux0);
}

Campo  cons_csv_Campo_NIL()
{
    Campo aux0;

  aux0 = (Campo) malloc(sizeof(struct sCampo));
  aux0->flag = PScons_csv_Campo_NIL;
  return(aux0);
}


/* -----------------------------------
 * Custom Function Implementations
 * -----------------------------------
 */
 
void csv_print( Linhas lcsv ){

    Linha ls;
    Campo cp;
    while (lcsv->flag!=PScons_csv_Linhas_NIL ){
        ls = lcsv->u.d1.s1;
        switch (ls->flag){
            case PScons_csv_Linha_Fim:
                cp = ls->u.d2.s1;
                switch (cp->flag){
                    case PScons_csv_Campo:
                        printf("Passo 1 ->%s\n",cp->u.d1.s1 );
                        break ;
                    case PScons_csv_Campo_NIL:
                        printf("Passo 2 -> {}\n");
                        break;
                }
              break;

            case PScons_csv_Linha:
                while (ls->flag != PScons_csv_Linha_Fim){
                    cp = ls->u.d1.s2;
                    switch (cp->flag){
                        case PScons_csv_Campo:
                             printf("Passo 3 ->%s\n",cp->u.d1.s1 );
                             break ;
                        case PScons_csv_Campo_NIL:
                              printf("Passo 4 ->{}\n");
                            break;
                     }
                    ls = ls->u.d1.s1;
                }
                cp = ls->u.d2.s1;
                switch (cp->flag){
                     case PScons_csv_Campo:
                           printf("Passo 5 ->%s\n",cp->u.d1.s1 );
                           break ;
                     case PScons_csv_Campo_NIL:
                           printf("Passo 6 ->{}\n");
                           break;
                 }
                break;
        }

        lcsv  = lcsv ->u.d1.s2;
    }

}

Linha csv_Linha_reverse( Linha l ){
    Campo cp;
    Campo c;
    Linha init = l;
    Linha aux;

    if (l->flag == PScons_csv_Linha_Fim)
        return l;

    cp = l->u.d1.s2;

    if (cp->flag == PScons_csv_Campo)
        c = cons_csv_Campo (cp->u.d1.s1);
    else
        c = cons_csv_Campo_NIL ();

    l = l->u.d1.s1;
    aux = cons_csv_Linha_Fim(c);
    while(l->flag == PScons_csv_Linha){
        cp = l->u.d1.s2;
        if (cp->flag == PScons_csv_Campo)
            c = cons_csv_Campo (cp->u.d1.s1);
        else
            c = cons_csv_Campo_NIL ();

        l = l->u.d1.s1;
        aux = cons_csv_Linha(aux,c);
    }
    cp = l->u.d2.s1;
    if (cp->flag == PScons_csv_Campo)
        c = cons_csv_Campo (cp->u.d1.s1);
    else
        c = cons_csv_Campo_NIL ();
    
    aux = cons_csv_Linha (aux, c);
    return aux;
}

/* -----------------------------------
 * Destructor Function Implementations
 * -----------------------------------
 */

void free_csv_Campos (Campo cmp){
    if (cmp->flag == PScons_csv_Campo)
        free (cmp);
}

void free_csv_Linha (Linha l){
    switch (l->flag){
        case PScons_csv_Linha_Fim:
            free_csv_Campos (l->u.d2.s1);
            break;
        case PScons_csv_Linha:
            free_csv_Linha (l->u.d1.s1);
            break;
    }

    free(l);
}

void free_csv_Linhas (Linhas lcsv){
    if (lcsv->flag == PScons_csv_Linhas){
       free_csv_Linha (lcsv -> u.d1.s1);
       free_csv_Linhas(lcsv -> u.d1.s2); 
    }
    free (lcsv);
}

