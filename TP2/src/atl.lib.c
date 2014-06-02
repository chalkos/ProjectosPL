#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

//fix
char* strdup(const char * s);

#include "atl.lib.h"

Atletas ListaAtletas = NULL;
extern Confs gco_config;

Atletas atl_ordenar_por_Score(Atletas atletas){
    Atletas res = NULL;
    while( atletas ){
        res = atl_insere_por_Score( res, atletas->atleta );
        atletas = atletas->proximo;
    }
    return res;
}

Atleta atl_novo_atleta(char* id, char* nome){
    Atleta atleta = (Atleta) malloc( sizeof( struct sAtleta ) );

    atleta->tempo_ultima_prova = 0;
    if( nome )
        atleta->nome = strdup( nome );
    else
        atleta->nome = NULL;
    atleta->ID = strdup( id );
    atleta->scores = NULL;

    return atleta;
}

void atl_add_score(Atleta atleta, int score){
    // percorrer os scores para inserir ordenado descrescente
    
    // não existem scores ou o novo score é maior que o primeiro da lista
    if( !atleta->scores || ( atleta->scores && atleta->scores->num < score)){
        LInt novo = (LInt)malloc(sizeof(struct sLInt));
        novo->num = score;
        novo->proximo = atleta->scores;
        atleta->scores = novo;
        return;
    }

    // percorrer a lista até encontrar um lugar para o novo score
    LInt scores = atleta->scores;
    while( scores ){
        // actual >= por inserir > proximo
        // se tiver chegado ao ultimo elemento da lista
        if( !scores->proximo || scores->num == score ||
            (scores->proximo && (scores->proximo->num < score))){
            LInt novo = (LInt)malloc(sizeof(struct sLInt));
            novo->num = score;
            novo->proximo = scores->proximo;
            scores->proximo = novo;
            return;
        }
        scores = scores->proximo;
    }
}

int atl_get_score(Atleta atleta, int nTop){
    // somatorio dos primeiros n
    int res = 0;
    LInt scores = atleta->scores;
    while( scores ){
        if( nTop <= 0 )
            break;
        res += scores->num;
        scores = scores->proximo;
        nTop--;
    }
    return res;
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

    int nTop = cfg_get_Ntop( gco_config );
    

    // ainda nao existem atletas ou
    // o score do atleta é maior que o score do primeiro da lista
    if( !atletas || (atletas && atl_get_score(atletas->atleta, nTop) < atl_get_score(atleta, nTop)) ){
        Atletas newAtletas = (Atletas) malloc( sizeof( struct sAtletas ) );
        newAtletas->atleta = atleta;
        newAtletas->proximo = atletas;
        return newAtletas;
    }

    while( atletas ){
        // actual >= por inserir > proximo
        // se tiver chegado ao ultimo elemento da lista
        if( !atletas->proximo ||
              atl_get_score(atletas->atleta, nTop) == atl_get_score(atleta, nTop) || 
               (atletas->proximo && 
                (atl_get_score(atletas->proximo->atleta, nTop) < atl_get_score(atleta, nTop))) ){
            Atletas newAtletas = (Atletas) malloc( sizeof( struct sAtletas ) );
            newAtletas->atleta = atleta;
            newAtletas->proximo = atletas->proximo;
            atletas->proximo = newAtletas;
            return original;
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
            printf("[%s] %s (%d pts, %d segs)\n", a->ID, a->nome,
                atl_get_score(a, cfg_get_Ntop( gco_config )), a->tempo_ultima_prova);
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

void atl_free_AtletasList(Atletas atletas){
    if( atletas ){
        atl_free_AtletasList(atletas->proximo);
        free(atletas);
    }
}


void atl_free_Atleta(Atleta atleta){
    if( !atleta )
        return;

    free( atleta->nome );
    atl_free_Scores( atleta->scores );
    free( atleta );
}

void atl_free_Scores(LInt scores){
    if( !scores )
        return;

    atl_free_Scores(scores->proximo);
    free(scores);
}

Atletas atl_ler_tempos( Confs cfg, Linhas csv, Atletas atletas ){
    Atletas atlOriginal = atletas;
    int campoChave = cfg_get_Chave( cfg );
    int campoTempo = cfg_get_Tempo( cfg );

    Linha linha;
    Atleta atleta;

    char* idAtleta;
    int tempoAtleta;

    int melhorTempo = INT_MAX;

    if( csv->flag == PScons_csv_Linhas )
        csv = csv->u.d1.s2;

    //obter os tempos (e o melhor tempo)
    while( csv->flag == PScons_csv_Linhas ){
        linha = csv->u.d1.s1;

        idAtleta = csv_get_campo( linha, campoChave );
        tempoAtleta = csv_tempo_to_int(
                        csv_get_campo( linha, campoTempo ) );
        if( tempoAtleta > 0 && tempoAtleta < melhorTempo )
            melhorTempo = tempoAtleta;

        if( tempoAtleta < 0 )
            tempoAtleta = 0;

        while( atletas ){
            atleta = atletas->atleta;
            
            if( strcmp( atleta->ID, idAtleta ) == 0 ){
                atleta->tempo_ultima_prova = tempoAtleta;
                break;
            }

            atletas = atletas->proximo;
        }
        atletas = atlOriginal;
        csv = csv->u.d1.s2;
    }

    if( melhorTempo == INT_MAX )
        return atlOriginal;

    // calcular os scores
    atletas = atlOriginal;
    while( atletas ){
        atleta = atletas->atleta;
        if( atleta->tempo_ultima_prova > 0 )
            atl_add_score(atleta, (int)(( melhorTempo / (float)atleta->tempo_ultima_prova ) * 100));
        atleta->tempo_ultima_prova = 0;
        atletas = atletas->proximo;
    }
    
    return atlOriginal;
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



