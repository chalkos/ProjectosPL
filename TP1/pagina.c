

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "pagina.h"

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

    p->indice = -1;

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
    str[10] = str[19] = ' ';
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
    printf("<div class=\"panel panel-default\"><a name=\"pagina%d\"></a><div class=\"panel-heading\"><h1>%s</h1><div style=\"width:100%%\"><button type=\"button\" class=\"btn btn-danger disabled\" align = \"left\">Ultima alteração em %s por %s</button><a href=\"#top\"><button type=\"button\" class=\"btn btn-default\" style =\"float:right\">&uarr;</button></a></div></div><div class=\"panel-body\"><div class=\"subsection\" id=\"cont\"><h2>Conteúdos</h2>\n", p->indice, p->titulo, p->ultimaRev, p->autor);

    // imprimir as seccões
    
    printf("</div><hr width=100%%><table class=\"table table-striped \"><thead><tr class=\"info\"><th>%d Links Externos</th><th>%d Links Internos</th></tr></thead><tbody>", p->nHLinks, p->nILinks);

    // imprimir os links
    
    printf("</tbody></table></div></div>");
}

void pagina_add_ilink(Pagina* pagina, ILink* linkinfo){
    Elemento* e = (Elemento*) malloc( sizeof(Elemento));

    e->dados = linkinfo;
    e->proximo= NULL;
    e->tipo = TIPO_ILINK;

    Elemento* itr = pagina->iLinks;
    
    // se ainda nao houver elementos na lista
    if( itr == NULL ){
        pagina->iLinks = e;
        return;
    }
    
    // se ja houver elementos, percorrer até ao ultimo e inserir
    while( itr->proximo != NULL )
        itr = itr->proximo;

    itr->proximo = e;
}

void pagina_add_seccao(Pagina* pagina, Seccao* seccao){
    Elemento* e = (Elemento*) malloc( sizeof(Elemento));

    e->dados = seccao;
    e->proximo= NULL;
    e->tipo = TIPO_HEADER;

    Elemento* itr = pagina->seccoes;
    
    // se ainda nao houver elementos na lista
    if( itr == NULL ){
        pagina->seccoes = e;
        return;
    }
    
    // se ja houver elementos, percorrer até ao ultimo e inserir
    while( itr->proximo != NULL )
        itr = itr->proximo;

    itr->proximo = e;
}


