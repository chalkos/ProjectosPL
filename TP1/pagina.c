

#include <stdlib.h>
#include <stdio.h>


#include "pagina.h"

// funções privadas
void print_elems(Elemento *elem);
void print_string(Elemento *elem);
void print_hlink(Elemento *elem);
void print_italico(Elemento *elem);
void print_negrito(Elemento *elem);
void print_ilink(Elemento *elem);

void print_string(Elemento* elem){
    printf("%s", (char*)elem->dados);
}

void print_elems(Elemento *elem){
    switch(elem->tipo){
        case TIPO_ILINK:
            ilink_print((ILink*)elem->dados);
            break;
        case TIPO_HLINK:
            break;
        case TIPO_NEGRITO:
            break;
        case TIPO_ITALICO:
            break;
        case TIPO_STRING:
            break;
    }
}
//-------------------------------------
//funções acessíveis

// cria uma nova página
Pagina* pagina_create(){
    Pagina* p = (Pagina*) malloc(sizeof(Pagina));

    p->titulo = NULL;
    p->ultimaRev = NULL;
    p->autor = NULL;

    p->iLinks = NULL;
    p->nILinks = 0;

    p->hLinks = NULL;
    p->nHLinks = 0;

    p->seccoes = NULL;
    p->nSeccoes = 0;

    p->elementos = NULL;
    p->actual = NULL;

    return p;
}

void pagina_set_titulo(Pagina* p, char* str){
    //recebe:
    //texto da pagina

    p->titulo = (char*) malloc( strlen(str)+1 );
    strcpy( p->titulo, str);
}

// destroi a página
void pagina_destroy(Pagina** pag){
    Pagina* p = *pag;

    free(p->titulo);
    free(p->ultimaRev);
    free(p->autor);

    // mais complicado porque é preciso destruir cada elemento
    // falta aqui a parte destruir os elementos
    

    free(*pag);
}

void pagina_print(Pagina* p){
    print_elems(p->elementos);
}



void pagina_adicionar_proximo(Pagina* p, Tipo tipo, void* dados){
}

void pagina_adicionar_filho(Pagina* p, Tipo tipo, void* dados){
    
}

int pagina_seleccionar_pai(Pagina* p){
    if( p && p->actual && p->actual && p->actual->pai ){
        p->actual = p->actual->pai;
        return 1;
    }
    return 0;
}

