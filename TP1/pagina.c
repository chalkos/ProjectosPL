

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

void exemplo(){
    Pagina* p = (Pagina*) malloc(sizeof(Pagina));

    p->autor = "bruno";
    p->titulo = "pagina de exemplo";
    p->ultimaRev = "hoje";

    Elemento* textosimples = (Elemento*) malloc( sizeof(Elemento));

    textosimples->tipo = TIPO_STRING;
    textosimples->filho=NULL;
    textosimples->proximo=NULL;
    textosimples->pai=NULL;
    textosimples->dados = "este é o texto da página";
    
    pagina_print(p);
}

void pagina_print(Pagina* p){
    Elemento* elem = p->elementos;
    

    print_elems(elem);
}

void print_string(Elemento* elem){
    printf("%s", (char*)elem->dados);
}

void print_elems(Elemento *elem){
    switch(elem->tipo){
        case TIPO_ILINK:
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

