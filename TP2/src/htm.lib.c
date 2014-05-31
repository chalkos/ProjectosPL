#include <stdio.h>

#include "htm.lib.h"
#include "atl.lib.h"
#include "cfg.lib.h"
#include "csv.lib.h"

FILE* output = NULL;
extern Confs gco_config;

/**********************
 * "private" functions
 * ********************/
void htm_print_indice();
void htm_print_provas();
void htm_print_resultados();
int htm_begin();
void htm_end();


/*****************
 * Public
 * **************/
void htm_print(){
    if( htm_begin() ){
        htm_print_indice();
        htm_print_resultados();
        htm_print_provas();
    }else
        fprintf(stderr, "[ERRO] não foi possível escrever no ficheiro index.html.\n");
    htm_end();
}



/**********************
 * "private" functions
 * ********************/

int htm_begin(){
    output = fopen("index.html", "w");
    if( output == NULL )
        return 0;
    return 1;
}

void htm_end(){
    if( output )
        fprintf(output, "</body></html>");
    fclose(output);
}

void htm_print_provas(){
    Lcsv csvs = ListaCSV;
    Linhas csv;
    Linha campos;
    char* valor = NULL;

    int totalCampos = 0;
    if( csvs ){
        csv = csvs->csv;
        while( (valor = csv_get_campo(csv->u.d1.s1, totalCampos+1)) )
            totalCampos++;
    }

    int i;
    char* selCampos = cfg_Campos_seleccionado( gco_config, totalCampos );
    int nprova = 1;

    while( csvs ){
        csv = csvs->csv;

        // inicio da tabela
        fprintf(output, "<div class=\"panel panel-default\"> <a name=\"prova%d\"></a> <div class=\"panel-heading\"><h1>Prova %d</h1></div> <div class=\"panel-body\"> <table class=\"table table-striped \"> <thead>", nprova, nprova);
        
        // cabeçalho
        campos = csv->u.d1.s1;
        csv = csv->u.d1.s2;
        fprintf(output, "<tr class=\"success\">");
        for( i=0; i<totalCampos; i++){
            if( selCampos[i] ){
                valor = csv_get_campo( campos, i+1 );
                fprintf(output, "<th>%s</th>", valor);
            }
        }
        fprintf(output, "</tr></thead><tbody>");
        
        // valores
        while( csv->flag == PScons_csv_Linhas ){
            campos = csv->u.d1.s1;
            csv = csv->u.d1.s2;
            fprintf(output, "<tr>");
            for( i=0; i<totalCampos; i++){
                if( selCampos[i] ){
                    valor = csv_get_campo( campos, i+1 );
                    fprintf(output, "<td>%s</td>", valor);
                }
            }
            fprintf(output, "</tr>");
        }

        fprintf(output, "</tbody> </table> </div> </div>");
        
        nprova++;
        csvs = csvs->next;
    }
}

void htm_print_resultados(){
    Atletas atletas = atl_ordenar_por_Score( ListaAtletas );
    Atleta atleta;

    fprintf(output, "<div class=\"panel panel-default\"> <a name=\"finais\"></a> <div class=\"panel-heading\"><h1>Resultados Finais</h1></div> <div class=\"panel-body\"> <table class=\"table table-striped \"> <thead> <tr class=\"success\"> <th>ID</th> <th>Nome</th> <th>Pontuação</th> </tr> </thead> <tbody>");

    while( atletas ){
        atleta = atletas->atleta;
        
        fprintf(output, "<tr> <td>%s</td> <td>%s</td> <td>%d</td> </tr>",
                atleta->ID, atleta->nome, atleta->score);

        atletas = atletas->proximo;
    }

    fprintf(output, "</tbody></table></div></div>");
    
    atl_free_AtletasList( atletas );
}

void htm_print_indice(){
    char* nome_torneio = cfg_get_Titulo( gco_config );
    Lcsv csvs = ListaCSV;
    int nprova = 1;
    
    fprintf(output, "<html><head><meta http-equiv=\"Content-Type\" content=\"text/html;charset=UTF-8\"><link rel=\"stylesheet\" type=\"text/css\" href=\"html/bootstrap.css\"><title>Gestão de Campeonatos de Orientação</title></head><body style=\"width:90%%; margin-left: auto; margin-right: auto; margin-top: 25px;\"><a name=\"top\"></a><div><p align=\"right\"><img src=\"http://corpora.di.uminho.pt/linguateca/pagina_linguateca/logoUM.jpg\" alt=\"Escola de Engenharia da Universidade do Minho\" width=\"150\" height=\"75\" align=\"top;\"></div><div style=\"position:fixed;bottom:10px;right:10px;\"><a href=\"#top\"><button type=\"button\" class=\"btn btn-default\">&uarr;</button></a></div>");
    
    fprintf(output, "<div class=\"panel panel-default\"><div class=\"panel-heading\"><h2>%s</h2></div><div class=\"panel-body\"><dl><dt><a href=\"#finais\">Resultados Finais</a></dt>", nome_torneio);

    while( csvs ){
        fprintf(output, "<dt><a href=\"#prova%d\">Prova %d</a></dt>", nprova, nprova);
        nprova++;
        csvs = csvs->next;
    }
    fprintf(output, "</dl></div></div>");
}

