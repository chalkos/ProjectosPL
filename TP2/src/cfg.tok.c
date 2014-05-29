#include <stdio.h>

#include "cfg.lib.h"
#include "cfg.tab.h"

void gco_set_Config(Confs cfg){}

extern int cfglex();

int main(){
    int token;

    while( (token=cfglex()) != 0 ){
        switch(token){
            case TITULO :
                printf("TITULO\n");
                break;
                           
            case NPROVAS :
                printf("NPROVAS\n");
                break;
                           
            case NTOP :
                printf("NTOP\n");
                break;
                           
            case CAMPOS :
                printf("CAMPOS\n");
                break;
                           
            case TEMPO :
                printf("TEMPO\n");
                break;
                           
            case CHAVE :
                printf("CHAVE\n");
                break;
                           
            case NOME :
                printf("NOME\n");
                break;
                           
            case str :
                printf("str\n");
                break;
                           
            case num :
                printf("num\n");
                break;
            
            case '\n':
                printf("SEPARADOR_LINHA\n");
                break;
                           
            default: printf("token: %d (char: '%c')\n", token, token);
        }
    }

    return 0;
}

