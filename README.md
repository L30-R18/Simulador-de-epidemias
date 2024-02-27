# Simulação de Epidemia

Este programa em C simula a propagação de uma epidemia em uma população, levando em consideração diversos parâmetros configuráveis. Abaixo estão algumas informações importantes para entender e utilizar o código.

## Parâmetros de Simulação

O programa utiliza diversas constantes para controlar o comportamento da simulação. Estes parâmetros podem ser ajustados no início do arquivo `epidemia.h`. Alguns dos principais parâmetros incluem:

- `DuracaoEmDias`: Duração em dias da simulação.
- `TamPopulacao`: Tamanho inicial da população.
- `TaxaTransmissao`: Probabilidade de um indivíduo transmitir o vírus para outro.
- `TaxaLetalidade`: Taxa de letalidade da doença.
- `TaxaRecuperacaoDiaria`: Percentual de chance de recuperação diária do indivíduo.
- `Reinfeccao`: Capacidade de pegar novamente o vírus (0 ou 1).
- `PercentualAdesaoVacina`: Percentual de chance de um indivíduo tomar a vacina.
- `EficaciaVacina`: Percentual de eficácia da vacina.
- `MaxPessoaCirculoSocial`: Máximo de pessoas que um indivíduo pode ter contato em um dia.
- `AgravanteMasculino`, `AgravanteFeminino`, `AgravanteIdade`: Parâmetros relacionados à gravidade do vírus para diferentes grupos.

## Estruturas e Funções

### Estrutura `Individuo`

Representa um indivíduo na população, com informações sobre sua condição, idade, sexo, etc.

### Estrutura `Populacao`

Representa a população de indivíduos e armazena informações estatísticas sobre a epidemia.

### Funções Principais

- `criaPopulacao`: Inicializa a população com uma quantidade inicial de infectados.
- `liberaPopulacao`: Libera a memória alocada para a população.
- `exibeEstatisticas`: Exibe estatísticas sobre a população no terminal.
- `transmite`: Transmite o vírus para uma determinada quantidade de indivíduos com base na chance de infecção.
- `aplicaVacina`: Aplica vacina em um determinado percentual da população.
- `resetaImunidade`: Reseta imunidade de certo percentual da população.
- `atualizaEpidemia`: Atualiza o avanço da epidemia com base em todas as constantes fornecidas.
- `printaPopulacao`: Printa os indivíduos no terminal em forma de matriz.
- `criarGraficoDeBarras`: Cria um gráfico baseando-se nos valores obtidos pela população durante a epidemia.

## Como Usar

1. Clone ou baixe o repositório.
2. Ajuste os parâmetros no arquivo `epidemia.h` conforme necessário.
3. Compile o programa utilizando um compilador C.
4. Execute o programa gerado.

## Observações

Certifique-se de ler e entender o código-fonte para uma configuração adequada dos parâmetros de simulação.

---
