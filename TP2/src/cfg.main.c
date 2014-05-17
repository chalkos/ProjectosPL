#include "cfg.lib.h"

#include <stdio.h>

extern int cfgparse();

int gco_set_Config(Confs cfg){
    if( !cfg_Confs_validate(cfg) ){
        free_cfg_Confs(cfg);
        fprintf( stderr, "[ERRO] Não foi possível carregar a configuração. Abortar.\n");
        return 1;
    }

    
    printf("Configuração Carregada:\n");
    cfg_Confs_print(cfg);
    free_cfg_Confs(cfg);
    return 0;
}

int main(){
    cfgparse();
    return 0;
}

