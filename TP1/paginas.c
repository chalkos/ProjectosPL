#include "pagina.h"

#include <stdio.h>
#include <stdlib.h>

Elemento* paginas_create(){
    Elemento* paginas = (Elemento*) malloc(sizeof(Elemento));

    paginas->proximo = NULL;
    paginas->dados = NULL;
    paginas->tipo = TIPO_PAGINA;

    return paginas;
}

void paginas_add(Elemento* ps, Pagina* p){
    if( ps->dados == NULL ){
        // primeira pagina
        p->indice = 0;
        ps->dados = p;
        return;
    }
    
    
    Elemento* e = (Elemento*) malloc( sizeof(Elemento));

    e->dados = p;
    e->proximo= NULL;
    e->tipo = TIPO_PAGINA;

    Elemento* itr = ps;
    int count = 1;
    
    // ir até ao fim da lista de paginas
    while( itr->proximo != NULL ){
        itr = itr->proximo;
        count++;
    }
    
    p->indice = count;
    itr->proximo = e;
}

void paginas_destroy(Elemento** paginas){
    if( *paginas == NULL )
        return;
    
    pagina_destroy( (Pagina**) &((*paginas)->dados) );

    paginas_destroy( &((*paginas)->proximo) );
    
    free(*paginas);
}

void paginas_print(Elemento* paginas){
    Elemento* itr;
    Pagina* pActual;
    
    // head
    printf("<html><head><meta http-equiv=\"Content-Type\" content=\"text/html;charset=UTF-8\"><link rel=\"stylesheet\" type=\"text/css\" href=\"http://bootswatch.com/cosmo/bootstrap.css\"><title>Processamento de Linguagens</title></head>");
    
    // inicio do body
    printf("<body style=\"width:90%%; margin-left: auto; margin-right: auto; margin-top: 25px;\"><a name=\"top\"></a><div><p align=\"right\"><img src=\"http://corpora.di.uminho.pt/linguateca/pagina_linguateca/logoUM.jpg\" alt=\"Escola de Engenharia da Universidade do Minho\" width=\"150\" height=\"75\" align=\"top;\"></div>");

    printf("<div class=\"panel panel-default\"><div class=\"panel-heading\"><h2>Índice de Páginas</h2></div><div class=\"panel-body\"><dl>");

    itr = paginas;
    while( itr ){
        pActual = (Pagina*) itr->dados;
        printf("<dt><a href=\"#pagina%d\">%s</a></dt>\n", pActual->indice, pActual->titulo);
        //pagina_print( (Pagina*)itr->dados);
        itr = itr->proximo;
    }

    printf("</dl></div></div>");
}




