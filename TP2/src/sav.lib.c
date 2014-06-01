#include <string.h>

#include "sav.lib.h"
#include "cfg.lib.h"
#include "csv.lib.h"

// WR_INT( int )
// escreve um inteiro no ficheiro
#define WR_INT(NUM) fwrite(&(NUM), sizeof(int), 1, file)
// WR_STR( char*, int )
// escreve a string de tamanho L no ficheiro
#define WR_STR(STR,L) fwrite((STR), sizeof(char), (L), file)

// RD_INT( int* )
// lê um inteiro do ficheiro
#define RD_INT(NUM) \
    do { \
        NUM = (int*)malloc(sizeof(int)); \
        fread(NUM, sizeof(int), 1, file); \
    } while(0)
// RD_STR( char*, int )
// lê uma string de tamanho L do ficheiro
#define RD_STR(STR,L) \
    do { \
        STR=(char*)malloc(sizeof(char)*((L)+1)); \
        fread((STR), sizeof(char), (L), file); \
        STR[L] = '\0'; \
    } while(0)


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

Lcampos sav_load_campos(FILE* file){
    // isto tem que ser alterado para conseguir ler as cenas
}

Confs sav_load_confs(FILE* file, Confs proximo){
    char* str = NULL;
    int* num = NULL;
    Confs confs = NULL;
    Conf conf = NULL;
    if( proximo->flag == PScons_cfg_Confs_NIL ){
        RD_INT(num);
        RD_STR(str,*num);
        confs = cons_cfg_Confs(
            cons_cfg_Conf_Titulo(str),
            proximo);
    }else{
        conf = proximo->u.d1.s1;
        switch( conf->flag ){
            case PScons_cfg_Conf_Titulo:
                RD_INT(num);
                confs = cons_cfg_Confs(
                    cons_cfg_Conf_Nprovas( *num ),
                    proximo);
                break;
            case PScons_cfg_Conf_Nprovas:
                RD_INT(num);
                confs = cons_cfg_Confs(
                    cons_cfg_Conf_Ntop( *num ),
                    proximo);
                break;
            case PScons_cfg_Conf_Ntop:
                RD_INT(num);
                confs = cons_cfg_Confs(
                    cons_cfg_Conf_Tempo( *num ),
                    proximo);
                break;
            case PScons_cfg_Conf_Tempo:
                RD_INT(num);
                confs = cons_cfg_Confs(
                    cons_cfg_Conf_Chave( *num ),
                    proximo);
                break;
            case PScons_cfg_Conf_Chave:
                RD_INT(num);
                confs = cons_cfg_Confs(
                    cons_cfg_Conf_Nome( *num ),
                    proximo);
                break;
            case PScons_cfg_Conf_Nome:
                return cons_cfg_Confs(
                    cons_cfg_Conf_Campos( sav_load_campos(file) ),
                    proximo);
                break;
        }
    }


    free(str);
    free(num);
    return sav_load_confs(file, confs);
}

void sav_load(FILE* file){
    // no fim fazer isto, quando souber que está tudo bem
    //free_cfg_Confs( gco_config);
    //csv_free_ListaCSV( ListaCSV );
    
    char* str;
    int* num;

    Confs confsFinal = sav_load_confs(file, cons_cfg_Confs_NIL());
}







