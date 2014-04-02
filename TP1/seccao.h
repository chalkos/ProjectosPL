#ifndef __SECCOES_H
#define __SECCOES_H


typedef struct sSeccao{
    char* texto;
    int indent;
} Seccao;

// criar uma nova seccao
Seccao* seccao_create(char* str, int indentacao);

// mostra o que tem na variavel seccao
void seccao_print(Seccao* seccao);

// liberta memória associada a seccao
void seccao_destroy(Seccao** seccao);


#endif
