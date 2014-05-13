#include "cfg.lib.h"

extern int cfgparse();

void gco_set_Config(Confs cfg){
    free_cfg_Confs(cfg);
    cfg_Confs_validate(cfg);
    cfg_Confs_print(cfg);
}

int main(){
    cfgparse();
    return 0;
}

