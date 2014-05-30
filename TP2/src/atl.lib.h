#ifndef __ATL_LIB_H
#define __ATL_LIB_H

#include "cfg.lib.h"
#include "csv.lib.h"

/*************
 * Específico do atleta
 * ***********/
typedef struct sAtletas *Atletas;
typedef struct sAtleta *Atleta;

extern Atletas ListaAtletas;

struct sAtletas{
    Atletas proximo;
    Atleta atleta;
};

struct sAtleta{
    char* ID;
    char* nome;
    int score;
    int tempo_ultima_prova;
};

Atleta atl_novo_atleta(char* id, char* nome);

Atletas atl_ordenar_por_Score(Atletas atletas);
Atletas atl_insere_por_ID(Atletas atletas, Atleta atleta);
Atletas atl_insere_por_Score(Atletas atletas, Atleta atleta);

void atl_print(Atletas atletas);

void atl_free_Atletas(Atletas atletas);

// versão que não liberta memória dos atletas em sí (apenas da lista)
// usado para libertar a lista ordenada por score
void atl_free_AtletasList(Atletas atletas);
void atl_free_Atleta(Atleta atleta);


/******************
 * Ler dados dos atletas a partir do csv
 * ***************/

Atletas atl_ler_csv( Confs cfg, Linhas csv, Atletas atletas );
Atletas atl_ler_tempos( Confs cfg, Linhas csv, Atletas atletas );

#endif
