#include <stdio.h>

#include "cmd.tab.h"

extern int cmdlex();

int main(){
    int token;

    while( (token=cmdlex()) != 0 ){
        switch(token){
            case CONFIG : printf("CONFIG\n");
                           break;
            case LOAD: printf("LOAD\n");
                           break;
            case IMPORT: printf("IMPORT\n");
                           break;
            case PRINT: printf("PRINT\n");
                           break;
            case FSAVE: printf("FSAVE\n");
                           break;
            case SAVE: printf("SAVE\n");
                           break;
            case QUIT: printf("QUIT\n");
                           break;
            case FQUIT: printf("FQUIT\n");
                           break;

            case FICHEIRO: printf("FICHEIRO\n");
                           break;
                           
            default: printf("token: %d\n", token);
        }
    }
}
