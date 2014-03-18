#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "hlink.h"

void hlink_set_view(char* viewPart){
    if(viewPart)
        free(hlink.view);
    hlink.view = strdup(viewPart);
}

void hlink_set_special(char* special){
    if(special)
        free(hlink.special);
    hlink.special = strdup(special);
}

void hlink_set_moreLink(char* moreLink){
    if(moreLink)
        free(hlink.moreLink);
    hlink.moreLink = strdup(moreLink);
}

void hlink_set_moreView(char* moreView){
    if(moreView)
        free(hlink.moreView);

    hlink.moreView = strdup(moreView);
}

void hlink_print(){
    printf("{[%s] %s%s (%s%s)}\n", hlink.special, hlink.view, hlink.moreView, hlink.view, hlink.moreLink);
}

void hlink_got_ending(char* str){
    int i;
    
    // verificar se existe moreView no valor encontrado
    if( str[ strlen(str)-1 ] != ']' ){
        for(i=strlen(str)-2; str[i] != ']'; i--);
        str[i] = str[i-1] = '\0'; //retirar parenteses
        hlink_set_moreView(str+i+1);
    }else{
        //retirar na mesma os parenteses rectos
        i = strlen(str)-1;
        str[i] = str[i-1] = '\0';
    }

    if( hlink.view && !hlink.moreLink )
        hlink_set_moreLink(str);
    else if( !hlink.view )
        hlink_set_view(str);

    //extra
    hlink_print();
    hlink_free_all();
}

void hlink_got_rename(char* str){
    // nao preciso de fazer nada
    printf("BEBUG!!\n");
    hlink_print();
    hlink_free_all();
}

unsigned int hlink_status(){
    unsigned int status = 0x0;
    if( hlink.view ) status |= HL_VIEW;
    if( hlink.special) status |= HL_SPECIAL;
    if( hlink.moreLink) status |= HL_MORELINK;
    if( hlink.moreView) status |= HL_MOREVIEW;

    return status;
}
void hlink_free_all(){
    free(hlink.view);
    free(hlink.special);
    free(hlink.moreLink);
    free(hlink.moreView);

    hlink.view = NULL;
    hlink.special= NULL;
    hlink.moreLink= NULL;
    hlink.moreView= NULL;
}
