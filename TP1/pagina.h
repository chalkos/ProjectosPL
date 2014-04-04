#ifndef __PAGINA_H
#define __PAGINA_H

#include "ilink.h"
#include "hlink.h"
#include "seccao.h"

typedef enum { TIPO_HLINK // hyperlink
             , TIPO_ILINK // internal link
             , TIPO_HEADER // header

             , TIPO_PAGINA // uma pagina
} Tipo;

typedef struct sElemento {
    Tipo tipo;
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
