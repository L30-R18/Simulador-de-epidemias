#ifndef _epidemia_h_
#define _epidemia_h_

/**
 * Dita a duração em dias da simulação
*/
#define DuracaoEmDias 1000
/**
 * Dita o tamanho inicial da população
*/
#define TamPopulacao 1000000

/**
 * Probabilidade de um individuo transmitir para outro
*/
#define TaxaTransmissao 11.0
/**
 * Taxa de mortalidade
*/
#define TaxaLetalidade 0.2
/**
 * Percentual de chance de recuperação diária do individuo
*/
#define TaxaRecuperacaoDiaria 9.0
/**
 * Pode ser 0 || 1, diz respeito a capacidade de pegar novamente o virus
*/
#define Reinfeccao 1

/**
 * É o percentual de chance de um individuo tomar a vacina.
*/
#define PercentualAdesaoVacina 0.0
/**
 * Diz respeito do percentual de eficácia da vacina
*/
#define EficaciaVacina 80.0

/**
 * O máximo de pessoas que um individuo pode ter contato em um dia
*/
#define MaxPessoaCirculoSocial 7

/**
 * Quanto maior o número, maior a gravidade do virus para homens
*/
#define AgravanteMasculino 0
/**
 * Quanto maior o número, maior a gravidade do virus para mulheres
*/
#define AgravanteFeminino 0
/**
 * Quanto maior o número, maior a mortalidade entre pessoas mais velhas
*/
#define AgravanteIdade 0.0

/**
 * Estrutura que representa um individuo.
*/
struct Individuo{
    unsigned char vivo:1;
    unsigned char idade:7;
    unsigned char sexo:1;
    unsigned char doente:1;
    unsigned char nivel_imunizado:3;
    unsigned char ja_esteve_doente:1;
    unsigned char classe_social:2;
};

/**
 * Estrutura para representar uma população de individuos
*/
typedef struct {
    struct Individuo I[TamPopulacao];
    unsigned qtdIndividuos;
    unsigned qtdDiasPassados;
    unsigned qtdMortos;
    unsigned qtdDoentes;
    unsigned qtdRecuperados;
}Populacao;

/**
 * Inicializa a população com uma quantidade inicial de infectados;
 * Retorna uma população
*/
Populacao *criaPopulacao(int qtdContaminados);
/**
 * Libera a memória alocada para a população
*/
void liberaPopulacao(Populacao *P);
/**
 * Exibe estatísticas sobre a população no terminal
*/
void exibeEstatisticas(Populacao *P);
/**
 * Transmite o virus para determinada quantidade de individuos baseando-se na chance de infecção
*/
void transmite(Populacao *P, unsigned qtdIndividuos, double chanceInfectar);
/**
 * Aplica vacina em determinado percentual da população.
*/
void aplicaVacina(Populacao *P, double Percentual);
/**
 * Reseta imunidade de certo percentual da população
*/
void resetaImunidade(Populacao *P, double Percentual);
/**
 * Atualiza o avanço da epidemia com base em todas as constantes fornecidas.
 * A função retorna ao número de mortes no dia decorrido
*/
int atualizaEpidemia(Populacao *P);
/**
 * Printa os individuos no terminal em forma de matriz onde:
   '!' significa que o individuo está infectado
   '-' significa que o individuo não está infectado
   ' ' significa que o individuo faleceu
*/
void printaPopulacao(Populacao *P);
/**
 * Cria um gráfico baseando-se nos valores obtidos pela população durante a epidemia
*/
void criarGraficoDeBarras(unsigned int valores[], unsigned tamanho, const char *nomeGrafico, const char *nomeEixoX, const char *nomeEixoY);

#endif
