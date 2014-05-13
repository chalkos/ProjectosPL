// TODO
// ler config
// ler comandos

#include <stdlib.h>
#include <stdio.h>

#define DEFAULT_CONFIG_NAME "default.cfg"

extern int cmdparse();
extern int cfgparse();

int main(int argc, char* argv[]){
    char* configName = NULL;
    if( argc > 1 )
        configName = argv[1];
    else
        configName = DEFAULT_CONFIG_NAME;
    
    printf("cfg: %s\n", configName);
    return 0;
}
