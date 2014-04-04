
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "hlink.h"

// criar um novo link
HLink* hlink_create(){
    HLink* novo = (HLink*) malloc( sizeof(HLink));

    novo->uri = NULL;
    novo->texto = NULL;

    return novo;
}

// definir partes do link
void hlink_set_texto(HLink* hlink, char* str){
    hlink->texto = (char*) malloc( strlen(str)+1 );
    strcpy( hlink->texto, str);
}

void hlink_set_uri(HLink* hlink, char* str){
    hlink->uri= (char*) malloc( strlen(str)+1 );
    strcpy( hlink->uri, str);
}

// mostra o que tem na variavel hlink
void hlink_print(HLink* hlink){
    if( hlink->texto ){
        printf("<a href=\"%s\">%s</a>", hlink->uri, hlink->texto);
    }else{
        printf("<a href=\"%s\">%s</a>", hlink->uri, hlink->uri);
    }
}

// liberta memória associada ao hlink
void hlink_destroy(HLink** hlink){
    HLink* tmp = *hlink;

    free(tmp->uri);
    free(tmp->texto);

    free(*hlink);
}
