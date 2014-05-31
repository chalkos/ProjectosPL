#include <string.h>

#include "sav.lib.h"
#include "cfg.lib.h"
#include "csv.lib.h"

#define WR_INT(NUM) fwrite(&(NUM), sizeof(int), 1, file)
#define WR_STR(STR,L) fwrite((STR), sizeof(char), (L), file)


extern Confs gco_config;

void sav_save(FILE* file){
    char* str = NULL;
    int num, i;
    int *lcampos;

    // *********************************
    // ---- guardar a configuraçao -----
    // *********************************
    
    // titulo
    str = cfg_get_Titulo(gco_config);
    num = strlen(str);
    WR_INT(num);
    WR_STR(str,num);

    // Nprovas
    num = cfg_get_Nprovas(gco_config);
    WR_INT(num);

    // Ntop
    num = cfg_get_Ntop(gco_config);
    WR_INT(num);

    // Tempo
    num = cfg_get_Tempo(gco_config);
    WR_INT(num);

    // Chave
    num = cfg_get_Chave(gco_config);
    WR_INT(num);

    // Nome
    num = cfg_get_Nome(gco_config);
    WR_INT(num);

    // Numero de Campos
    num = cfg_get_NCampos(gco_config);
    WR_INT(num);
    
    // Lista de Campos
    lcampos = cfg_get_Campos(gco_config);
    i=0;
    while( lcampos[i] != -1 )
        WR_INT(lcampos[i++]);

    
    // *********************************
    // ---- Guardar os CSVs -----
    // *********************************
    Lcsv csvs = ListaCSV;
    Linhas csv;
    Linha campos;
    Campo campo;
    
    int ncsvs, nlinhas, ncampos;
    ncsvs = nlinhas = ncampos = 0;
    
    // contar o nr de CSVs
    while( csvs ){
        ncsvs++;
        csvs = csvs->next;
    }
    WR_INT(ncsvs);

    // inserir os CSVs
    csvs = ListaCSV;
    while( csvs ){
        // contar o nr de linhas do csv
        nlinhas = 0;
        csv = csvs->csv;
        while( csv->flag == PScons_csv_Linhas ){
            nlinhas++;
            csv = csv->u.d1.s2;
        }
        WR_INT(nlinhas);

        // contar o nr de campos na primeira linha
        ncampos = 0;
        campos = csvs->csv->u.d1.s1;
        while( campos->flag == PScons_csv_Linha ){
            ncampos++;
            campos = campos->u.d1.s1;
        }
        ncampos++;
        WR_INT(ncampos);

        // inserir as linhas do csv
        csv = csvs->csv;
        while( csv->flag == PScons_csv_Linhas ){
            campos = csv->u.d1.s1;

            // interar os campos e inseri-los
            while( campos->flag == PScons_csv_Linha ){
                campo = campos->u.d1.s2;
                if( campo->flag == PScons_csv_Campo ){
                    str = campo->u.d1.s1;
                    num = strlen(str);
                    WR_INT(num);
                    WR_STR(str,num);
                }else{
                    num = 0;
                    WR_INT(num);
                }
                campos = campos->u.d1.s1;
            }
            // ultimo campo
            campo = campos->u.d2.s1;
            if( campo->flag == PScons_csv_Campo ){
                str = campo->u.d1.s1;
                num = strlen(str);
                WR_INT(num);
                WR_STR(str,num);
            }else{
                num = 0;
                WR_INT(num);
            }
            
            // proxima linha
            csv = csv->u.d1.s2;
        }
        
        // proximo CSV
        csvs = csvs->next;
    }


    fclose(file);
}

void sav_load(FILE* file){

}
