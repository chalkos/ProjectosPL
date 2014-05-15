#include "csv.lib.h"

extern int csvparse();
extern int csvlex_destroy();

int main(){

    csvparse();
    csv_print( ListaCSV->csv );
    
    csv_Linhas_validate( ListaCSV->csv );
    csv_free_ListaCSV( ListaCSV );
    return 0;
}
