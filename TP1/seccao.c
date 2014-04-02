
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "seccao.h"

// criar uma nova seccao
Seccao* seccao_create(char* str, int indentacao){
    Seccao* s = (Seccao*) malloc(sizeof(Seccao));

    s->texto = (char*) malloc( strlen(str)+1 );
    strcpy( s->texto, str);

    s->indent = indentacao;
    
    return s;
}

// mostra o que tem na variavel seccao
void seccao_print(Seccao* seccao){
    int i;
    printf("<h4>");
    for(i=1; i<seccao->indent; i++)
        printf("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;");

    printf("%s</h4>\n", seccao->texto);
}

// liberta memória associada a seccao
void seccao_destroy(Seccao** seccao){
    Seccao* s = *seccao;

    free(s->texto);

    free(*seccao);
}

