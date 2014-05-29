#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//fix
char* strdup(const char * s);

#include "atl.lib.h"

Atletas ListaAtletas = NULL;

Atleta atl_novo_atleta(char* id, char* nome){
    Atleta atleta = (Atleta) malloc( sizeof( struct sAtleta ) );

    atleta->tempo_ultima_prova = 0;
    atleta->nome = strdup( nome );
    atleta->ID = strdup( id );
    atleta->score = 0;

    return atleta;
}

Atletas atl_insere_por_ID(Atletas atletas, Atleta atleta){
    Atletas original = atletas;

    // ainda nao existem atletas ou
    // o id do atleta é menor que o id do primeiro da lista
    if( !atletas || (atletas && strcmp(atletas->atleta->ID, atleta->ID) > 0) ){
        Atletas newAtletas = (Atletas) malloc( sizeof( struct sAtletas ) );
        newAtletas->atleta = atleta;
        newAtletas->proximo = atletas;
        return newAtletas;
    }

    while( atletas ){
        // actual == por inserir (ignorar)
        if( strcmp( atletas->atleta->ID, atleta->ID) == 0 ){
            atl_free_Atleta( atleta );
            return original;
        }

        // actual < por inserir < proximo
        if( atletas->proximo && strcmp( atletas->proximo->atleta->ID, atleta->ID ) > 0 ){
            Atletas newAtletas = (Atletas) malloc( sizeof( struct sAtletas ) );
            newAtletas->atleta = atleta;
            newAtletas->proximo = atletas->proximo;
            atletas->proximo = newAtletas;
            return original;
        }
        
        // se tiver chegado ao ultimo elemento da lista
        if( !atletas->proximo ){
            Atletas newAtletas = (Atletas) malloc( sizeof( struct sAtletas ) );
            newAtletas->atleta = atleta;
            newAtletas->proximo = NULL;
            atletas->proximo = newAtletas;
            return original;
        }

        atletas = atletas->proximo;
    }

    // não é suposto chegar aqui
    return original;
}

Atletas atl_insere_por_Score(Atletas atletas, Atleta atleta){
    Atletas original = atletas;

    // ainda nao existem atletas ou
    // o score do atleta é menor que o score do primeiro da lista
    if( !atletas || (atletas && atletas->atleta->score > atleta->score) ){
        Atletas newAtletas = (Atletas) malloc( sizeof( struct sAtletas ) );
        newAtletas->atleta = atleta;
        newAtletas->proximo = atletas;
        return newAtletas;
    }

    while( atletas ){
        // actual == por inserir (ignorar)
        if( atletas->atleta->score == atleta->score ){
            atl_free_Atleta( atleta );
            return original;
        }
        
        // actual <= por inserir < proximo
        if( atletas->proximo && (atletas->proximo->atleta->score > atleta->score) ){
            Atletas newAtletas = (Atletas) malloc( sizeof( struct sAtletas ) );
            newAtletas->atleta = atleta;
            newAtletas->proximo = atletas->proximo;
            atletas->proximo = newAtletas;
            return original;
        }
        
        // se tiver chegado ao ultimo elemento da lista
        if( !atletas->proximo ){
            Atletas newAtletas = (Atletas) malloc( sizeof( struct sAtletas ) );
            newAtletas->atleta = atleta;
            newAtletas->proximo = NULL;
            atletas->proximo = newAtletas;
            return newAtletas;
        }

        atletas = atletas->proximo;
    }

    // não é suposto chegar aqui
    return original;
}

void atl_print(Atletas atletas){
    Atleta a;
    printf("Atletas:\n");
    
    while( atletas ){
        a = atletas->atleta;
        if( !a )
            printf("[null] atleta sem dados\n");
        else
            printf("[%s] %s (%d pts, %d segs)\n", a->ID, a->nome, a->score, a->tempo_ultima_prova);
        atletas = atletas->proximo;
    }
}

void atl_free_Atletas(Atletas atletas){
    if( !atletas )
        return;

    atl_free_Atleta( atletas->atleta );
    atl_free_Atletas( atletas->proximo );
    free( atletas );
}

void atl_free_Atleta(Atleta atleta){
    if( !atleta )
        return;

    free( atleta->nome );
    free( atleta );
}


Atletas atl_ler_csv( Confs cfg, Linhas csv, Atletas atletas ){
    int campoChave = cfg_get_Chave( cfg );
    int campoNome = cfg_get_Nome( cfg );

    Linha linha;
    Atleta atleta;

    if( csv->flag == PScons_csv_Linhas )
        csv = csv->u.d1.s2;
    else
        return atletas;

    while( csv->flag == PScons_csv_Linhas ){
        linha = csv->u.d1.s1;

        atleta = atl_novo_atleta(
                csv_get_campo( linha, campoChave ),
                csv_get_campo( linha, campoNome ));
        
        atletas = atl_insere_por_ID( atletas, atleta );

        csv = csv->u.d1.s2;
    }

    return atletas;
}



