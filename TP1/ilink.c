#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "ilink.h"

static void string_replace(char* str, const char find, const char replace){
    if(!str) return;
    
    while(*str != '\0'){
        if(*str == find)
            *str = replace;
        str++;
    }
}

ILink* ilink_create(){
    ILink* ilink = (ILink*) malloc(sizeof(ILink));

    ilink->parenteses = NULL;
    ilink->texto = NULL;
    ilink->virgula = NULL;
    ilink->apresentar = NULL;
    ilink->resto = NULL;
    ilink->especial = NULL;

    return ilink;
}

void ilink_set_especial(ILink* ilink, char* str){
    
    //recebe coisas como:
    //help:texto da pagina
    
    char* especial = strtok(str, ":");
    char* texto = strtok(NULL, ":");

    ilink->especial = (char*) malloc( strlen(especial)+1 );
    strcpy( ilink->especial, especial );
    
    ilink->texto = (char*) malloc( strlen(texto)+1 );
    strcpy( ilink->texto, texto );
    string_replace(ilink->texto, ' ', '_');
}

void ilink_set_texto(ILink* ilink, char* str){
    //recebe:
    //texto da pagina

    ilink->texto = (char*) malloc( strlen(str)+1 );
    strcpy( ilink->texto, str);
    //string_replace(ilink->texto, ' ', '_');
}

void ilink_set_parenteses(ILink* ilink, char* str){

    //recebe:
    //(coisas entre parenteses)
    //(coisas que nao acabam com parenteses
    
    if( str[strlen(str)-1] == ')' ){
        ilink->parenteses = (char*) malloc( strlen(str)+1 );
        strcpy( ilink->parenteses, str );
        string_replace(ilink->parenteses, ' ', '_');
    }else{
        //nao termina com parenteses e por isso é o segundo caso
        char* acumulador = (char*) malloc( strlen(str) + strlen(ilink->texto) + 1 );
        acumulador[0] = '\0';
        strcat(acumulador, ilink->texto);
        strcat(acumulador, str);
        free( ilink->texto );
        ilink->texto = acumulador;
    }
}

void ilink_set_virgula(ILink* ilink, char* str){

    //recebe:
    //, coisas depois de uma virgula

    ilink->virgula = (char*) malloc( strlen(str)+1 );
    strcpy( ilink->virgula, str );
    string_replace(ilink->virgula, ' ', '_');
}

void ilink_set_apresentar(ILink* ilink, char* str){

    //recebe:
    //coisas que aparecerem depois do pipe
    //\ \t
    
    while(*str == ' ') //retirar espaços em branco no início
        str++;

    ilink->apresentar = (char*) malloc( strlen(str)+1 );
    strcpy( ilink->apresentar, str );
}

void ilink_set_resto(ILink* ilink, char* str){

    //recebe:
    //letrasDepoisDosParentesesRectosSemEspacos

    ilink->resto = (char*) malloc( strlen(str)+1 );
    strcpy( ilink->resto, str );
}

// mostra o que tem na variavel ilink
void ilink_print(ILink* ilink){
    //printf("<a href=\"https://en.wikipedia.org/wiki/%s", "dummy");
    //printf("especial: %s\n", ilink->especial);
    //printf("virgula: %s\n", ilink->virgula);
    //printf("apresentar: %s\n", ilink->apresentar);
    //printf("resto: %s\n", ilink->resto);
    //printf("parenteses: %s\n", ilink->parenteses);
    //printf("texto: %s\n\n", ilink->texto);
    

    printf("<a href=\"https://en.wikipedia.org/wiki/");
    
    string_replace(ilink->virgula, ' ', '_');
    string_replace(ilink->parenteses, ' ', '_');
    string_replace(ilink->texto, ' ', '_');

    if( ilink->especial )
        printf("%s:",ilink->especial);
    
    if( ilink->parenteses )
        printf("%s%s", ilink->texto, ilink->parenteses);
    else if( ilink->virgula )
        printf("%s%s", ilink->texto, ilink->virgula);
    else
        printf("%s", ilink->texto);

    printf("\">");

    string_replace(ilink->virgula, '_', ' ');
    string_replace(ilink->parenteses, '_', ' ');
    string_replace(ilink->texto, '_', ' ');
    
    if(ilink->apresentar == NULL){
        // mostrar tudo tal como está
        if( ilink->parenteses )
            printf("%s%s%s", ilink->texto, ilink->parenteses, ilink->resto);
        else if( ilink->virgula )
            printf("%s%s%s", ilink->texto, ilink->virgula, ilink->resto);
        else
            printf("%s%s", ilink->texto, ilink->resto);
    }else if( ilink->apresentar != NULL && ilink->apresentar[0] == '\0' ){
        // ocultar automáticamente os parenteses ou virgula
        printf("%s%s", ilink->texto, ilink->resto);
    } else {
        // mostrar a parte de apresentacao
        printf("%s%s", ilink->apresentar, ilink->resto);
    }
    
    printf("</a>\n");
}

// liberta memória associada ao ilink
void ilink_destroy(ILink** ilink){
    //ilink_print(*ilink);

    free((*ilink)->texto);
    free((*ilink)->resto);
    free((*ilink)->virgula);
    free((*ilink)->apresentar);
    free((*ilink)->especial);
    free((*ilink)->parenteses);

    free(*ilink);
    *ilink = NULL;
}





