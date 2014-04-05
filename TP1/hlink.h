#ifndef __HLINK_H
#define __HLINK_H


typedef struct sHLink{
    char* uri;
    char* texto;
} HLink;

// criar um novo link
HLink* hlink_create();

// definir partes do link
void hlink_set_texto(HLink* hlink, char* str);
void hlink_set_uri(HLink* hlink, char* str);

// mostra o que tem na variavel hlink
void hlink_print(HLink* hlink);

// liberta memória associada ao hlink
void hlink_destroy(HLink** hlink);

#endif
