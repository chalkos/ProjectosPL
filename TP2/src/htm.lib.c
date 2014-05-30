#include <stdio.h>

#include "htm.lib.h"

FILE* output = NULL;

int htm_begin(){
    output = fopen("index.html", "w");
    if( output == NULL )
        return 0;
    return 1;
}

void htm_end(){
    fclose(output);
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

void htm_print_indice( Confs cfg ){
    char* nome_torneio = cfg_get_Titulo( cfg );
    Lcsv csvs = ListaCSV;
    int nprova = 1;
    
    fprintf(output, "<div class=\"panel panel-default\"><div class=\"panel-heading\"><h2>%s</h2></div><div class=\"panel-body\"><dl><dt><a href=\"#finais\">Resultados Finais</a></dt>", nome_torneio);

    while( csvs ){
        fprintf(output, "<dt><a href=\"#prova%d\">Prova %d</a></dt>", nprova, nprova);
        csvs = csvs->next;
    }
    fprintf(output, "</dl></div></div>");
}

void htm_print_header(){
    fprintf(output, "<html><head><meta http-equiv=\"Content-Type\" content=\"text/html;charset=UTF-8\"><link rel=\"stylesheet\" type=\"text/css\" href=\"bootstrap.css\"><title>Gestão de Campeonatos de Orientação</title></head><body style=\"width:90%%; margin-left: auto; margin-right: auto; margin-top: 25px;\"><a name=\"top\"></a><div><p align=\"right\"><img src=\"http://corpora.di.uminho.pt/linguateca/pagina_linguateca/logoUM.jpg\" alt=\"Escola de Engenharia da Universidade do Minho\" width=\"150\" height=\"75\" align=\"top;\"></div><div style=\"position:fixed;bottom:10px;right:10px;\"><a href=\"#top\"><button type=\"button\" class=\"btn btn-default\">&uarr;</button></a></div>");


}

