#include "cmd.lib.h"
#include <stdio.h>
#include <stdlib.h>

extern int cfgparse();
extern void cfgset_in(FILE * in_str);
extern int csvparse();
extern void csvset_in(FILE * in_str);

extern void cfglex_destroy();

void cmd_config(char* ficheiro){
    printf("comando config (%s)\n", ficheiro);

    FILE *cfgFile;
    if( !( cfgFile = fopen(ficheiro, "r") )){
        fprintf( stderr, "[ERRO] Não foi possível abrir o ficheiro %s\n", ficheiro);
        fprintf( stderr, "[ERRO] Não foi possível carregar a configuração. Abortar.\n");
        return;
    }
    
    cfgset_in(cfgFile);
    if( cfgparse() == 1 ){
        // houve problemas ao ler o cfg
        fprintf( stderr, "[ERRO] Não foi possível carregar a configuração. Abortar.\n");
        cfglex_destroy();
        fclose(cfgFile);
        return;
    }
    fclose(cfgFile);
    
}

void cmd_load(char* ficheiro){
    printf("comando load (%s)\n", ficheiro);
}

void cmd_import(char* ficheiro){

    printf("comando import (%s)\n", ficheiro);

    FILE *csvFile;
    if( !( csvFile = fopen(ficheiro, "r") )){
        fprintf( stderr, "[ERRO] Não foi possível abrir o ficheiro %s\n", ficheiro);
        fprintf( stderr, "[ERRO] Não foi possível carregar o ficheiro CSV. Abortar.\n");
        return;
    }
    
    csvset_in(csvFile);
    if( csvparse() == 1 ){
        // houve problemas ao ler o csv
        fprintf( stderr, "[ERRO] Não foi possível carregar o ficheiro CSV. Abortar.\n");
        fclose(csvFile);
        return;
    }
    fclose(csvFile);
}

void cmd_print(){
    printf("comando print\n");
}

void cmd_save(char* ficheiro, int force){
    printf("comando save(force:%d) (%s)\n", force, ficheiro);
}

int cmd_quit(){
    printf("comando quit\n");
    // se o ficheiro não tiver sido guardado recentemente,
    // avisar e dizer para guardar o ficheiro antes de sair
    // ou entao sair com quit!
    
    // verificar se o ficheiro foi alterado recentemente
    return 0; //nao pode sair


    return 1; //pode sair
}

