

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "pagina.h"

// funções privadas
void print_hlink(Elemento *elem);
void print_ilink(Elemento *elem);
void print_header(Elemento *elem);


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

    return p;
}

void pagina_set_titulo(Pagina* p, char* str){
    //recebe:
    //texto da pagina

    p->titulo = (char*) malloc( strlen(str)+1 );
    strcpy( p->titulo, str);
}

// insere o autor
void pagina_set_autor(Pagina* p, char* str){
    p->autor = (char*) malloc( strlen(str)+1 );
    strcpy( p->autor, str);
}

// insere o ultimaRevisao
void pagina_set_ultimaRevisao(Pagina* p, char* str){
    p->ultimaRev = (char*) malloc( strlen(str)+1 );
    strcpy( p->ultimaRev, str);
}

void elemento_add_ilink(Pagina* pagina, ILink* linkinfo){
    Elemento* e = (Elemento*) malloc( sizeof(Elemento));

    e->dados = linkinfo;
    e->proximo= NULL;
    e->tipo = TIPO_ILINK;

    Elemento* itr = pagina->iLinks;

    if( itr == NULL ){
        pagina->iLinks = e;
        return;
    }

    
}

// destroi a página
void pagina_destroy(Pagina** pag){
    Pagina* p = *pag;

    free(p->titulo);
    free(p->ultimaRev);
    free(p->autor);

    // falta aqui a parte destruir os elementos das listas
    

    free(*pag);
}

void pagina_print(Pagina* p){
    // é preciso adicionar uma cena para escrever o html da pagina
}

