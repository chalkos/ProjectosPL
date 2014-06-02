#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "csv.lib.h"
#include "atl.lib.h"

// fix
char* strdup(const char * s);

Lcsv ListaCSV = NULL;
extern Confs gco_config;

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

// retorna o tempo em segundos a partir de uma string de tempo
int csv_tempo_to_int(char* str){
    if( !str )
        return -1;

    if( strlen(str) != 8 )
        return -1;

    if( str[2] != ':' || str[5] != ':' )
        return -1;

    if( !isdigit( str[0] ) ||
        !isdigit( str[1] ) ||
        !isdigit( str[3] ) ||
        !isdigit( str[4] ) ||
        !isdigit( str[6] ) ||
        !isdigit( str[7] ))
        return -1;
    
    // o tempo é válido da forma hh:mm:ss
    return ( atoi(str) * 3600 +
             atoi(str+3) * 60 +
             atoi(str+6));

}


char* csv_get_campo(Linha campos, int indice_campo){
    Campo campo = NULL;
    while( indice_campo > 1 ){
        // se o indice_campo for >0 e ja estivermos no
        // ultimo campo da linha, nao há mais campos
        if( campos->flag == PScons_csv_Linha_Fim )
            return NULL;

        if( campos->flag == PScons_csv_Linha )
            campos = campos->u.d1.s1;
        indice_campo--;
    }

    if( indice_campo == 1 ){
        if( campos->flag == PScons_csv_Linha )
            campo = campos->u.d1.s2;
        else // PScons_csv_Linha_Fim
            campo = campos->u.d2.s1;

        if( campo->flag == PScons_csv_Campo )
            return campo->u.d1.s1;
        else
            return NULL;
    }
    return NULL;
}

// Retorna 1 se o ficheiro csv estiver bom
int csv_Linhas_validate(Linhas linhas){
    int numLinha = 0;
    int numCamposCerto = 0;
    int numCamposLido = 0;
    int ocorreuErro = 0; //se ocorrer fica a 1
    
    Linha linha;
    
    if( linhas->flag == PScons_csv_Linhas_NIL ){
        fprintf(stderr, "[ERRO] O ficheiro csv apenas tem o cabeçalho.\n");
        return 0;
    }

    // tem mais linhas além do cabeçalho. guardar o nr de campos do cabeçalho
    linha = linhas->u.d1.s1;
    while( linha->flag == PScons_csv_Linha ){
        numCamposCerto++;
        linha = linha->u.d1.s1;
    }
    numCamposCerto++; //linha->flag == PScons_csv_Linha_Fim
    numLinha++;

    while( linhas->flag == PScons_csv_Linhas ){
        linha = linhas->u.d1.s1;
        
        numCamposLido = 0;
        while( linha->flag == PScons_csv_Linha ){
            numCamposLido++;
            linha = linha->u.d1.s1;
        }
        numCamposLido++;//linha->flag == PScons_csv_Linha_Fim
        
        //validar
        if( numCamposLido != numCamposCerto ){
            ocorreuErro = 1;
            fprintf(stderr, "[ERRO] CSV (linha %d): esperados %d campo(s), lidos %d campo(s)\n", numLinha, numCamposCerto, numCamposLido);
        }

        numLinha++;
        linhas = linhas->u.d1.s2;
    }
    
    if( ocorreuErro )
        return 0;
    return 1;
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
    ListaAtletas = atl_ler_csv( gco_config, dados, ListaAtletas);

    //atl_print( ListaAtletas );

    atl_ler_tempos( gco_config, dados, ListaAtletas );

    //printf("Lista de atletas por score:\n");
    //Atletas porscore = atl_ordenar_por_Score( ListaAtletas );
    //atl_print( porscore );
    

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

    Lcsv csvs = ListaCSV;
    int ncsvs = 0;
    int nprovas = cfg_get_Nprovas(gco_config);
    while( csvs ){
        ncsvs++;
        csvs = csvs->next;
    }

    printf("Prova #%d (máximo definido: %d)\n", ncsvs, nprovas);

    if( ncsvs > nprovas )
        fprintf(stderr, "[WARNING] Excedido o número de provas definido na configuração.\n");
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

