#include "cmd.lib.h"
#include <stdio.h>
#include <stdlib.h>

extern int cfgparse();
extern void cfgset_in(FILE * in_str);
extern int csvparse();
extern void csvset_in(FILE * in_str);

extern void cfglex_destroy();

extern void htm_print();
extern void sav_save(FILE* file);
extern void sav_load(FILE* file);

void cmd_config(char* ficheiro){
    printf("[DEBUG] comando config (%s)\n", ficheiro);

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
    printf("[DEBUG] comando load (%s)\n", ficheiro);

    FILE *file;
    if( !( file = fopen(ficheiro, "rb") )){
        fprintf( stderr, "[ERRO] Não foi possível abrir o ficheiro %s. Abortar.\n", ficheiro);
        return;
    }
    
    sav_load( file );

    fclose(file);
}

void cmd_import(char* ficheiro){

    printf("[DEBUG] comando import (%s)\n", ficheiro);

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
    printf("[DEBUG] comando print\n");
    htm_print();
}

void cmd_save(char* ficheiro, int force){
    printf("[DEBUG] comando save(force:%d) (%s)\n", force, ficheiro);

    //always forced
    FILE *file;
    if( !force && ( file = fopen(ficheiro, "r") )){
        fprintf( stderr, "[ERRO] O ficheiro %s já existe.\n", ficheiro);
        fprintf( stderr, "[ERRO] Para forçar a gravação, utilize \"save!\". Abortar.\n");
        fclose(file);
        return;
    }

    if( !( file = fopen(ficheiro, "wb") )){
        fprintf( stderr, "[ERRO] Não foi possível abrir o ficheiro %s para escrita. Abortar.\n", ficheiro);
        return;
    }

    sav_save(file);
}

int cmd_quit(){
    printf("[DEBUG] comando quit\n");
    // se o ficheiro não tiver sido guardado recentemente,
    // avisar e dizer para guardar o ficheiro antes de sair
    // ou entao sair com quit!
    
    // verificar se o ficheiro foi guardado recentemente
    return 0; //nao pode sair


    return 1; //pode sair
}

