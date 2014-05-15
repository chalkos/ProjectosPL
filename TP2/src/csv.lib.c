#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "csv.lib.h"

Lcsv ListaCSV = NULL;

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
 
int csv_Linhas_validate(Linhas lcsv){
    int campo = 0;
    int campoLinha =0;

    Linha l;
    Campo cmp;
    
    while (lcsv -> flag != PScons_csv_Linhas_NIL){
        l = lcsv->u.d1.s1;
        switch (l->flag){
            case PScons_csv_Linha_Fim:
                cmp = l->u.d2.s1;
                switch(cmp->flag){
                    case PScons_csv_Campo_NIL:
                        campo++;
                        break;
                    case PScons_csv_Campo:
                        campo++;
                        break;
                }
                break;
            case PScons_csv_Linha:
                while (l->flag != PScons_csv_Linha_Fim){
                    cmp = l->u.d1.s2;
                    switch (cmp->flag){
                        case PScons_csv_Campo:
                            campoLinha ++;
                            break;
                        case PScons_csv_Campo_NIL:
                            campoLinha ++;
                            break;
                    } 
                    l = l->u.d1.s1;  
                }
                cmp = l->u.d2.s1;
                switch (cmp->flag){
                     case PScons_csv_Campo:
                           campoLinha++;
                           break ;
                     case PScons_csv_Campo_NIL:
                           campoLinha++;
                           break;
                }
                campo = campoLinha;    
                break;
           
            default :
                fprintf(stderr, "WARNING : flag %d na struct Linha ignorada\n",l->flag );
        }
         
         lcsv = lcsv->u.d1.s2;
    }
     if (campo!= campoLinha)    
             fprintf(stderr, "WARNING: Linhas com nº de campos diferentes campos\n");
    return 0;
}


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
        c = cons_csv_Campo (strdup(cp->u.d1.s1));
    else
        c = cons_csv_Campo_NIL ();

    l = l->u.d1.s1;
    aux = cons_csv_Linha_Fim(c);
    while(l->flag == PScons_csv_Linha){
        cp = l->u.d1.s2;
        if (cp->flag == PScons_csv_Campo)
            c = cons_csv_Campo (strdup(cp->u.d1.s1));
        else
            c = cons_csv_Campo_NIL ();

        l = l->u.d1.s1;
        aux = cons_csv_Linha(aux,c);
    }
    cp = l->u.d2.s1;
    if (cp->flag == PScons_csv_Campo)
        c = cons_csv_Campo (strdup(cp->u.d1.s1));
    else
        c = cons_csv_Campo_NIL ();
    
    aux = cons_csv_Linha (aux, c);

    free_csv_Linha(init);

    return aux;
}

void csv_import_csv( Linhas dados ){
    if( !ListaCSV ){
        ListaCSV = (Lcsv) malloc( sizeof( struct sLcsv ) );
        ListaCSV->next = NULL;
        ListaCSV->csv = dados;
        return;
    }

    Lcsv nova = (Lcsv) malloc( sizeof( struct sLcsv ) );
    nova->next = ListaCSV;
    nova->csv = dados;
    ListaCSV = nova;
}

void csv_free_ListaCSV(Lcsv elem){
    if( elem ){
        free_csv_Linhas( elem->csv );
        csv_free_ListaCSV( elem->next );
        free( elem );
    }
}

/* -----------------------------------
 * Destructor Function Implementations
 * -----------------------------------
 */

void free_csv_Campo (Campo cmp){
    if (cmp->flag == PScons_csv_Campo)
        free(cmp->u.d1.s1);
    free (cmp);
}

void free_csv_Linha (Linha l){
    switch (l->flag){
        case PScons_csv_Linha_Fim:
            free_csv_Campo (l->u.d2.s1);
            break;
        case PScons_csv_Linha:
            free_csv_Campo (l->u.d1.s2);
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

