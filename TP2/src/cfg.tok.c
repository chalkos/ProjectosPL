#include <stdio.h>

#include "cfg.lib.h"
#include "cfg.tab.h"

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
                           
            case SCORE :
                printf("SCORE\n");
                break;
                           
            case str :
                printf("str\n");
                break;
                           
            case num :
                printf("num\n");
                break;
                           
            default: printf("token: %d (char: '%c')\n", token, token);
        }
    }
}

