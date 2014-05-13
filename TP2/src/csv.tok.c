#include <stdio.h>

#include "csv.lib.h"
#include "csv.tab.h"

extern int csvlex();

int main(){
    int token;

    while( (token=csvlex()) != 0 ){
        switch(token){
            case str :
                printf("str=\"%s\"\n", csvlval.csv_str);
                break;
                           
            default: printf("token: %d (char: '%c')\n", token, token);
        }
    }
}

