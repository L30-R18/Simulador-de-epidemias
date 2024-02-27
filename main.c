#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include "epidemia.h"

int main(){

    unsigned int qtdMortes[DuracaoEmDias];

    srand(time(NULL));
    Populacao *P = criaPopulacao(20);

    aplicaVacina(P, PercentualAdesaoVacina);

    while(P->qtdDiasPassados < DuracaoEmDias){ 
        qtdMortes[P->qtdDiasPassados - 1] = atualizaEpidemia(P);
        if(P->qtdDiasPassados % 100 == 0){
            sleep(1);
            exibeEstatisticas(P);
            if(TamPopulacao <= 500){
                printaPopulacao(P);
            }
        }
    }
    exibeEstatisticas(P);

    liberaPopulacao(P);


    char titulo[100];

    sprintf(titulo, "QUANTIDADE DE MORTES PARA %u HABITANTES COM %.2lf%c DA POPULAÇÃO IMUNIZADA", TamPopulacao, PercentualAdesaoVacina, '%');

    criarGraficoDeBarras(qtdMortes, DuracaoEmDias, titulo , "Dias", "Numero de mortes");

    return 0;
}