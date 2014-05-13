// TODO
// ler config
// ler comandos

#include <stdlib.h>
#include <stdio.h>

#include "cfg.lib.h"
#include "gco.lib.h"
#include "cmd.lib.h"
#include "error.lib.h"

/************************
 * Definições
 ***********************/
#define DEFAULT_CONFIG_NAME "default.cfg"
void gco_set_Config(Confs cfg);

extern int cmdparse();
extern int cfgparse();

extern void cfgset_in(FILE * in_str);

Confs gco_config = NULL;

/************************
 * Funções
 ***********************/
int main(int argc, char* argv[]){
    char* configName = NULL;
    if( argc > 1 )
        configName = argv[1];
    else
        configName = DEFAULT_CONFIG_NAME;
    
    FILE *configFile;
    if( !( configFile = fopen(configName, "r") )){
        fprintf( stderr, "[ERRO] Não foi possível abrir o ficheiro %s\n", configName);
        fprintf( stderr, "[ERRO] Não foi possível carregar a configuração. Abortar.\n");
        exit(1);
    }
    
    cfgset_in( configFile);
    if( cfgparse() != 0 ){
        // erro ao ler a configuração
        fprintf( stderr, "[ERRO] Não foi possível carregar a configuração. Abortar.\n");
        return 1;
    }
    
    printf("-----------------------\n");
    printf("Configuração Carregada:\n");
    printf("-----------------------\n");
    cfg_Confs_print(gco_config);

    printf("-----------------------\n%s", CMD_PROMPT);

    cfgset_in(NULL);

    cmdparse();
    printf("\n:)\n");

    return 0;
}

void gco_set_Config(Confs cfg){
    if( !cfg_Confs_validate(cfg) ){
        // erro de semântica
        fprintf( stderr, "[ERRO] Não foi possível carregar a configuração. Abortar.\n");
        exit(2);
    }
    gco_config = cfg;
}




