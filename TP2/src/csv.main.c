#include "csv.lib.h"

extern int csvparse();
extern int csvlex_destroy();

int main(){

    csvparse();
    csv_free_ListaCSV( ListaCSV );
    return 0;
}
