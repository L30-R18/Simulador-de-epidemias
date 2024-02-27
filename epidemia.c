#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "epidemia.h"

Populacao *criaPopulacao(int qtdContaminados){
    Populacao *P = (Populacao*) malloc(sizeof(Populacao));
    P->qtdIndividuos = TamPopulacao;
    P->qtdDiasPassados = 0;
    P->qtdDoentes = 0;
    P->qtdMortos = 0;
    P->qtdRecuperados = 0;

    for(int i = 0; i < TamPopulacao; i ++){
        P->I[i].vivo = 1;
        P->I[i].sexo = rand () % 2;
        P->I[i].doente = 0;
        P->I[i].nivel_imunizado = 0;
        P->I[i].ja_esteve_doente = 0;
        P->I[i].classe_social = 0;
        
        if(i < TamPopulacao/25){
            P->I[i].idade = rand () % 20 + 60;
            continue;
        }
        else if(i < TamPopulacao/7){
            P->I[i].idade = rand () % 10 + 60;
            continue;
        }
        else if(i < TamPopulacao/6){
            P->I[i].idade = rand () % 10 + 30;
            continue;
        }
        else if(i < TamPopulacao/2.9){
            P->I[i].idade = rand () % 18;
            continue;
        }
        else{
            P->I[i].idade = rand () % 10 + 20;
        }
    }

    for(int i = 0; i < qtdContaminados; i ++){
        P->I[i].doente = 1;
        P->qtdDoentes ++;
    }
    return P;
}

void liberaPopulacao(Populacao *P){
    free(P);
}

void exibeEstatisticas(Populacao *P){
    unsigned qtdMenores = 0, qtdAdultos = 0, qtdIdosos = 0;
    unsigned qtdHomens = 0, qtdMulheres = 0;
    for(int i = 0; i < TamPopulacao; i ++){
        if(!P->I[i].vivo)
            continue;
        if(P->I[i].sexo == 0){
            qtdMulheres ++;
        }else{
            qtdHomens ++;
        }
        if(P->I[i].idade <= 18){
            qtdMenores ++;
        }else if(P->I[i].idade <= 60){
            qtdAdultos ++;
        }else{
            qtdIdosos ++;
        }
    }
    printf("____________________________________________________________\n");
    printf("DIAS PASSADOS : %u\n", P->qtdDiasPassados);
    printf("-----\n");
    printf("QTD VIVOS : %u\n", P->qtdIndividuos);
    printf("QTD MORTOS : %u\n", P->qtdMortos);
    printf("QTD INFECTADOS : %u\n", P->qtdDoentes);
    printf("QTD RECUPERADOS : %u\n", P->qtdRecuperados);
    printf("-----\n");
    printf("QTD MENORES : %u\tPERCENTUAL : %.3lf\n",qtdMenores ,(100.0/P->qtdIndividuos) * qtdMenores);
    printf("QTD ADULTOS : %u\tPERCENTUAL : %.3lf\n",qtdAdultos ,(100.0/P->qtdIndividuos) * qtdAdultos);
    printf("QTD IDOSOS :  %u\tPERCENTUAL : %.3lf\n",qtdIdosos ,(100.0/P->qtdIndividuos) * qtdIdosos);
    printf("-----\n");
    printf("QTD HOMENS :  %u\tPERCENTUAL : %.3lf\n",qtdHomens ,(100.0/P->qtdIndividuos) * qtdHomens);
    printf("QTD MULHERES :%u\tPERCENTUAL : %.3lf\n",qtdMulheres ,(100.0/P->qtdIndividuos) * qtdMulheres);
    printf("____________________________________________________________\n");
}

void transmite(Populacao *P, unsigned qtdIndividuos, double chanceInfectar){
    for(unsigned i = 0; i < qtdIndividuos; i ++){
        if(rand() % 10000 / 100.0 > chanceInfectar){
            continue;
        }
        unsigned tentativas = 0, indice;
        while(tentativas < TamPopulacao/10){
            indice = rand () % TamPopulacao;
            if(P->I[indice].vivo){
                break;
            }
        }
        
        if(Reinfeccao){
            //printf("1 ");
            if(!P->I[indice].doente)
                P->qtdDoentes ++;
            P->I[indice].doente = 1;
            continue;
        }else if(!Reinfeccao && !P->I[indice].ja_esteve_doente){
            //printf("0");
            if(!P->I[indice].doente)
                P->qtdDoentes ++;
            P->I[indice].doente = 1;
        }
    }
}

void aplicaVacina(Populacao *P, double Percentual){
    for(unsigned i = 0; i < TamPopulacao; i ++){
        if(P->I[i].vivo){
            if(rand () % 10000 / 100.0 > Percentual){
                continue;
            }
            P->I[i].nivel_imunizado = 7;
        }
    }
}

void resetaImunidade(Populacao *P, double Percentual){
    for(int i = 0; i < TamPopulacao; i ++){
        if(P->I[i].vivo)
            if(P->I[i].nivel_imunizado == 3)
                if(rand() % 10000 / 100.0 < Percentual)
                    P->I[i].nivel_imunizado = 0;
    }
}

int atualizaEpidemia(Populacao *P){
    int qtdMortes = 0;

    if(P->qtdDiasPassados % 250 == 0){
        resetaImunidade(P, ((rand() % 2000 - P->qtdDiasPassados*4) + 4000) / 100.0);
    }

    for(int i = 0; i < TamPopulacao; i ++){
        if(P->I[i].vivo){
            if(P->I[i].doente){
                transmite(P, rand() % MaxPessoaCirculoSocial, TaxaTransmissao - ((EficaciaVacina/100.0/7.0 * P->I[i].nivel_imunizado) * (TaxaTransmissao)));
                double agravante; 
                if(!P->I[i].sexo)
                    agravante = AgravanteFeminino;
                else
                    agravante = AgravanteMasculino;
                double letalidade = ((TaxaLetalidade)
                    + ((agravante * (TaxaLetalidade))/100.0)
                    + (((P->I[i].idade * AgravanteIdade * (TaxaLetalidade)))/100.0)
                    - ((EficaciaVacina/100.0/7.0 * P->I[i].nivel_imunizado) * (TaxaLetalidade)))
                    / (100.0/TaxaRecuperacaoDiaria)/2;
                if(rand () % 10000 / 100.0 < letalidade){
                    qtdMortes ++;
                    P->I[i].vivo = 0;
                    P->qtdMortos ++;
                    P->qtdIndividuos --;
                    P->qtdDoentes --;
                    if(P->I[i].ja_esteve_doente)
                        P->qtdRecuperados --;
                }else if(rand () % 10000 / 100.0 < (TaxaRecuperacaoDiaria * ((P->I[i].nivel_imunizado + 1)/2.0))){
                    if(P->I[i].nivel_imunizado != 7)
                        P->I[i].nivel_imunizado = 3;
                    P->I[i].doente = 0;
                    if(!P->I[i].ja_esteve_doente)
                        P->qtdRecuperados ++;
                    P->I[i].ja_esteve_doente = 1;
                    P->qtdDoentes --;
                }
            }
        }
    }
    P->qtdDiasPassados ++;
    return qtdMortes;
}

void printaPopulacao(Populacao *P){
    printf("__________________________________________________________________________________\n");
    for(int i = 0; i < TamPopulacao; i ++){
        if(i % 125 == 0)
            printf("\n");
        if(!P->I[i].vivo){
            printf(" ");
            continue;
        }else if(P->I[i].vivo && !P->I[i].doente){
            printf("-");
            continue;
        }else{
            printf("!");
        }
    }
    printf("\n__________________________________________________________________________________\n");
}

int vetor_eh_nulo(unsigned int vetor[], unsigned tamanho){
    for (unsigned i = 0; i < tamanho; i ++){
        if(vetor[i] == 1)
            return 0;
    }
    return 1;
}

void criarGraficoDeBarras(unsigned int valores[], unsigned tamanho, const char *nomeGrafico, const char *nomeEixoX, const char *nomeEixoY) {
    if(vetor_eh_nulo(valores, tamanho)){
        printf("\n--- Dados nulos obtidos ---\n");
    }
    
    FILE *arquivo = fopen("dados.dat", "w");
    if (arquivo == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo.\n");
        return;
    }

    // Escrever os dados no arquivo
    for (unsigned i = 0; i < tamanho; i++) {
        fprintf(arquivo, "%d %d\n", i + 1, valores[i]);
    }

    // Fechar o arquivo
    fclose(arquivo);

    sleep(1);

    // Criar o gráfico de barras usando gnuplot
    FILE *gnuplotPipe = fopen("gnuplot_commands", "w");
    if (gnuplotPipe == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo de comandos do gnuplot.\n");
        return;
    }

    unsigned int somaValores = 0;
    for(unsigned i = 0; i < tamanho; i ++){
        somaValores += valores[i];
    }

    fprintf(gnuplotPipe, "set title '%s'\n", nomeGrafico);
    fprintf(gnuplotPipe, "set xlabel '%s'\n", nomeEixoX);
    fprintf(gnuplotPipe, "set ylabel '%s'\n", nomeEixoY);

    fprintf(gnuplotPipe, "set size 1.1, 1.0\n"); 
    fprintf(gnuplotPipe, "plot 'dados.dat' with boxes title 'Número de mortes : %u'\n", somaValores);

    fclose(gnuplotPipe);

    system("gnuplot -persistent gnuplot_commands");

    system("rm dados.dat");
    system("rm gnuplot_commands");
}