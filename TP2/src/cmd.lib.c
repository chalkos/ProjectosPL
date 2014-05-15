#include "cmd.lib.h"
#include <stdio.h>
#include <stdlib.h>

extern int csvparse();
extern void csvset_in(FILE * in_str);

void cmd_config(char* ficheiro){
    printf("comando config (%s)\n", ficheiro);
}

void cmd_load(char* ficheiro){
    printf("comando load (%s)\n", ficheiro);
}

void cmd_import(char* ficheiro){

    printf("comando import (%s)\n", ficheiro);

    FILE *csvFile;
    if( !( csvFile = fopen(ficheiro, "r") )){
        fprintf( stderr, "[ERRO] Não foi possível abrir o ficheiro %s\n", ficheiro);
        fprintf( stderr, "[ERRO] Não foi possível carregar a configuração. Abortar.\n");
        return;
    }
    
    csvset_in(csvFile);
    if( csvparse() == 0 ){
        
    }
}

void cmd_print(){
    printf("comando print\n");
}

void cmd_save(char* ficheiro, int force){
    printf("comando save(force:%d) (%s)\n", force, ficheiro);
}

void cmd_quit(int force){
    if( force ){ 
        printf("comando quit (forced)\n");
        exit(0);
    }else{
        printf("comando quit\n");
    }
}

