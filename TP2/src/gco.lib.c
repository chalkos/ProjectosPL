// TODO
// ler config
// ler comandos

#include <stdlib.h>
#include <stdio.h>
#include "cfg.lib.h"
#include "cmd.lib.h"
#include "csv.lib.h"

/************************
 * Definições
 ***********************/
#define DEFAULT_CONFIG_NAME "default.cfg"
int gco_set_Config(Confs cfg);

extern int cmdparse();
extern int cfgparse();
extern void csvlex_destroy();
extern void cfglex_destroy();

extern void cfgset_in(FILE * in_str);

Confs gco_config = NULL;

/************************
 * Funções
 ***********************/
int main(int argc, char* argv[]){

    // ler o nome do ficheiro de configuração
    // usar o primeiro argumento do ficheiro
    // ou usar o DEFAULT_CONFIG_NAME caso não existam argumentos
    char* configName = NULL;
    if( argc > 1 )
        configName = argv[1];
    else
        configName = DEFAULT_CONFIG_NAME;
    
    // tentar ler a confuguração, se não conseguir, terminar
    FILE *configFile;
    if( !( configFile = fopen(configName, "r") )){
        fprintf( stderr, "[ERRO] Não foi possível abrir o ficheiro %s\n", configName);
        fprintf( stderr, "[ERRO] Não foi possível carregar a configuração. Abortar.\n");
        return 1;
    }
    
    // definir que o parser de cfg deve usar o ficheiro de cfg em vez do stdin
    cfgset_in( configFile);

    // ler a configuração
    if( cfgparse() != 0 ){
        // erro ao ler a configuração
        cfglex_destroy();
        fclose(configFile);
        return 2;
    }
    
    // ler comandos do stdin
    printf("%s", CMD_PROMPT);
    cmdparse();

    // close config file
    fclose(configFile);

    // free memory
    free_cfg_Confs( gco_config );
    csv_free_ListaCSV( ListaCSV );
    printf("\n:)\n");

    return 0;
}

// carrega uma nova configuração.
// se tudo correr bem retorna 0
int gco_set_Config(Confs cfg){
    if( !cfg_Confs_validate(cfg) ){
        free_cfg_Confs(cfg);
        if( gco_config )
            fprintf( stderr, "[ERRO] Não foi possível carregar a configuração. Utilizando a configuração anterior.\n");
        else
            fprintf( stderr, "[ERRO] Não foi possível carregar a configuração. Abortar.\n");
        return 1;
    }

    // se já existe uma config, fazer free e substituir pela que foi lida
    if(gco_config)
        free_cfg_Confs(gco_config);
    gco_config = cfg;
    
    printf("Configuração Carregada:\n");
    cfg_Confs_print(gco_config);
    return 0;
}




