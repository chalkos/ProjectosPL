#ifndef __ILINK_H
#define __ILINK_H

// define um link para a própria wikipedia (interno)

// [[Especial: texto (parenteses)|apresentar]]resto
// [[Especial: texto, virgula|apresentar]]resto
typedef struct sILink{
    char* especial;
    char* texto;
    char* parenteses;
    char* virgula;
    char* apresentar;
    char* resto;
} ILink;

// criar um novo link
ILink* ilink_create();

// definir partes do link
void ilink_set_especial(ILink* ilink, char* str);
void ilink_set_texto(ILink* ilink, char* str);
void ilink_set_parenteses(ILink* ilink, char* str);
void ilink_set_virgula(ILink* ilink, char* str);
void ilink_set_apresentar(ILink* ilink, char* str);
void ilink_set_resto(ILink* ilink, char* str);

// mostra o que tem na variavel ilink
void ilink_print(ILink* ilink);

// liberta memória associada ao ilink
void ilink_destroy(ILink** ilink);


#endif
