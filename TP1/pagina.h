#ifndef __PAGINA_H
#define __PAGINA_H

#include "ilink.h"
#include "hlink.h"
#include "seccao.h"

typedef struct sElemento {
    void *dados;
    struct sElemento* proximo; // o proximo elemento
} Elemento;

typedef struct sPagina {
   char* titulo;
   char* autor;
   char* ultimaRev;

   int indice;

   // links internos
   Elemento* iLinks;
   int nILinks;

   // links externos
   Elemento* hLinks;
   int nHLinks;
   
   // headers
   Elemento* seccoes;
   int nSeccoes;
} Pagina;


// cria uma nova página
Pagina* pagina_create();

// destroi a página
void pagina_destroy(Pagina** p);

// destroi os iLinks
void pagina_destroy_ilinks(Elemento** ilinks);

// destroi os hLinks
void pagina_destroy_hlinks(Elemento** hlinks);

// destroi as seccoes
void pagina_destroy_seccoes(Elemento** seccoes);

// insere o titulo
void pagina_set_titulo(Pagina* p, char* str);

// insere o autor
void pagina_set_autor(Pagina* p, char* str);

// insere o ultimaRevisao
void pagina_set_ultimaRevisao(Pagina* p, char* str);

// imprimir o HTML da página
void pagina_print(Pagina* p);

// inserir uma seccao
void pagina_add_seccao(Pagina* pagina, Seccao* seccao);

// inserir um ILink
void pagina_add_ilink(Pagina* pagina, ILink* linkinfo);

// inserir um ILink
void pagina_add_hlink(Pagina* pagina, HLink* linkinfo);


#endif
