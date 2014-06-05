#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

#include "sav.lib.h"
#include "cfg.lib.h"
#include "csv.lib.h"
#include "cmd.lib.h"

extern void cmd_lex_push(FILE* file );
extern void cmd_lex_pop();

extern int cmdparse();
extern void cmdset_in(FILE * in_str);

int sav_has_changes = 0;
int sav_loading = 0;

/************************
 * Private Declarations
 ***********************/
#define BASE_DIR "./savestate/"

void sav_cria_pasta();

FILE* sav_file_import;

/************************
 * Implementations
 ***********************/

void sav_cria_pasta(){
    // verificar se o nome ja existe
    struct stat estado;
    int err = stat(BASE_DIR, &estado);

    if( err == -1 ){
        if(ENOENT == errno){
            mkdir(BASE_DIR, 0777);
        }else{
            perror("stat");
        }
    }
}

void sav_save(char* nome, int force){
    // obter o numero total de CSVs
    int nCSVs = 0;
    Lcsv csvs = ListaCSV;
    while( csvs ){
        nCSVs++;
        csvs = csvs->next;
    }

    if( nCSVs == 0 ){
        fprintf(stderr, "[INFO] Não existem dados em memória. Nada feito.\n");
        return;
    }

    sav_cria_pasta();

    char* realname = (char*)malloc( sizeof(char) * (strlen(nome) + strlen(BASE_DIR) + 1) );
    strcpy( realname, BASE_DIR );
    strcat( realname, nome );
    
    FILE* file;
    if( !force ){
        if( (file = fopen(realname, "r"))){
            fprintf(stderr, "[ERRO] Ficheiro já existe. Abortar.\n");
            free(realname);
            fclose(file);
            return;
        }
    }

    // deve-se criar ou escrever por cima do ficheiro existente
    file = fopen(realname, "w");
    if( !file ){
        fprintf(stderr, "[ERRO] Não foi possível criar o ficheiro. Abortar.\n");
        free(realname);
        return;
    }

    FILE* fcsv[nCSVs];
    int i;
    char buffer[1024];
    for(i=0; i<nCSVs; i++){
        snprintf(buffer, 1024, "%s%d", realname, i);
        fcsv[i] = fopen(buffer, "w");
    }
    //verificar
    for(i=0; i<nCSVs; i++){
        if( !fcsv[i] ){
            fprintf(stderr, "[ERRO] Não foi possível criar o ficheiro (%d). Abortar.\n", i);
            for(i=0; i<nCSVs; i++)
                fclose( fcsv[i] );
            fclose(file);
            free(realname);
            return;
        }
    }

    // todos os ficheiros estão abertos para escrita
    csvs = ListaCSV;
    Linhas linhas;
    Linha linha;
    Campo campo;
    i = 0;
    while( csvs ){
        // escrever o CSV
        linhas = csvs->csv;
        while( linhas->flag == PScons_csv_Linhas ){
            linha = linhas->u.d1.s1;

            while( linha->flag == PScons_csv_Linha ){
                campo = linha->u.d1.s2;
                if( campo->flag == PScons_csv_Campo )
                    fprintf(fcsv[i], "%s;", campo->u.d1.s1);
                else
                    fprintf(fcsv[i], ";");

                linha = linha->u.d1.s1;
            }
            // PScons_csv_Linha_Fim
            campo = linha->u.d2.s1;
            if( campo->flag == PScons_csv_Campo )
                fprintf(fcsv[i], "%s\n", campo->u.d1.s1);
            else
                fprintf(fcsv[i], "\n");
            

            linhas = linhas->u.d1.s2;
        }
        i++;
        csvs = csvs->next;
    }

    // escrever o comando no ficheiro de comandos
    for(i=nCSVs-1; i>=0; i--)
        fprintf( file, "i %s%d\n", realname, i );


    for(i=0; i<nCSVs; i++)
        fclose( fcsv[i] );
    fclose(file);
    free(realname);
    sav_has_changes = 0;
}

void sav_load(char* nome){
    // abrir o ficheiro para o batch import
    char* realname = (char*)malloc( sizeof(char) * (strlen(nome) + strlen(BASE_DIR) + 1) );
    strcpy( realname, BASE_DIR );
    strcat( realname, nome );
    sav_file_import = fopen(realname, "r");
    if( !sav_file_import ){
        free(realname);
        fprintf(stderr, "[ERRO] Não foi possível ler o ficheiro de estado. Abortar.\n");
        return;
    }
    
    sav_has_changes = 1;

    // trocar o buffer para o ficheiro de batch import
    cmd_lex_push( sav_file_import );
    // ler cmds
    sav_loading = 1;
    cmdparse();
    sav_loading = 0;
    // trocar o buffer para o stdin
    cmd_lex_pop();
    // libertar coisas
    fclose(sav_file_import);
    free(realname);
}



