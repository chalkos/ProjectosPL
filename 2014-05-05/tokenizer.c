#include <stdio.h>

#include "y.tab.h"

extern int yylex();

int main(){
    int token;

    while( (token=yylex()) != 0 ){
        switch(token){
            case IAGENDA : printf("IAGENDA\n");
                           break;
            case IENTRADA: printf("IENTRADA\n");
                           break;
            case FAGENDA : printf("FAGENDA\n");
                           break;
            case FENTRADA : printf("FENTRADA\n");
                            break;

            case chave : printf("chave\n");
                         break;
            case valor : printf("valor\n");
                         break;
            case '=' : printf("=\n");
                       break;
            default: printf("token: %d\n", token);
        }
    }
}
