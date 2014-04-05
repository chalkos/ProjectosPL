

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
    Elemento* itr = NULL;
    int i;
    
    printf("<div class=\"panel panel-default\"><a name=\"pagina%d\"></a><div class=\"panel-heading\"><h1>%s</h1><div style=\"width:100%%\"><button type=\"button\" class=\"btn btn-danger disabled\" align = \"left\">Ultima alteração em %s por %s</button><a href=\"#top\"><button type=\"button\" class=\"btn btn-default\" style =\"float:right\">&uarr;</button></a></div></div><div class=\"panel-body\"><div class=\"subsection\" id=\"cont\"><h3>Secções (%d)</h3>\n", p->indice, p->titulo, p->ultimaRev, p->autor, p->nSeccoes);

    // imprimir as seccões
    Seccao *seccao = NULL;
    for( itr=p->seccoes; itr; itr = itr->proximo ){
        seccao = itr->dados;
        seccao_print(seccao);
    }
    
    printf("</div><hr width=100%%><table class=\"table table-striped \"><thead><tr class=\"info\"><th style=\"width:50%%\" colspan=2>%d Links Externos</th></tr></thead><tbody>", p->nHLinks);
    
    itr = p->hLinks;
    for(i=0; i < p->nHLinks/2; i+=1){
        printf("<tr><td>");
        hlink_print((HLink*)itr->dados);

        itr = itr->proximo;
        printf("</td><td>");
        hlink_print((HLink*)itr->dados);
        printf("</td></tr>\n");

        itr = itr->proximo;
    }

    if( itr ){
        printf("<tr><td>");
        hlink_print((HLink*)itr->dados);
        printf("</td><td></td></tr>");
    }
    printf("</tbody></table>");


    printf("<hr width=100%%><table class=\"table table-striped \"><thead><tr class=\"info\"><th style=\"width:50%%\" colspan=2>%d Links Internos</th></tr></thead><tbody>", p->nILinks);

    itr = p->iLinks;
    for(i=0; i < p->nILinks/2; i+=1){
        printf("<tr><td>");
        ilink_print((ILink*)itr->dados);

        itr = itr->proximo;
        printf("</td><td>");
        ilink_print((ILink*)itr->dados);
        printf("</td></tr>\n");

        itr = itr->proximo;
    }

    if( itr ){
        printf("<tr><td>");
        ilink_print((ILink*)itr->dados);
        printf("</td><td></td></tr>");
    }
    
    printf("</tbody></table></div></div>");
}

void pagina_add_ilink(Pagina* pagina, ILink* linkinfo){
    Elemento* e = (Elemento*) malloc( sizeof(Elemento));

    e->dados = linkinfo;
    e->proximo= NULL;

    Elemento* itr = pagina->iLinks;
    pagina->nILinks++;
    
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

    Elemento* itr = pagina->seccoes;
    pagina->nSeccoes++;
    
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


void pagina_add_hlink(Pagina* pagina, HLink* linkinfo){
    Elemento* e = (Elemento*) malloc( sizeof(Elemento));

    e->dados = linkinfo;
    e->proximo= NULL;

    Elemento* itr = pagina->hLinks;
    pagina->nHLinks++;
    
    // se ainda nao houver elementos na lista
    if( itr == NULL ){
        pagina->hLinks = e;
        return;
    }
    
    // se ja houver elementos, percorrer até ao ultimo e inserir
    while( itr->proximo != NULL )
        itr = itr->proximo;
    
    itr->proximo = e;
}
