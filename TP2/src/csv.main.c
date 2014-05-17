#include <stdio.h>
#include "csv.lib.h"

extern int csvparse();
extern int csvlex_destroy();

int main(){

    if( csvparse() == 0){
        printf("csv impecável\n");
        csv_print( ListaCSV->csv );
        csv_free_ListaCSV( ListaCSV );
    }else{
        printf("csv com erros\n");
    }

    
    return 0;
}
