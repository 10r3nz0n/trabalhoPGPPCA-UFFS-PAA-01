#include "app.h"
#include "lista.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

void appLimparBuffer(void) {
    int c;

    while ((c = getchar()) != '\n' && c != EOF) {}
}

void appLimparTela(void) {
    int resultado;
    
    #ifdef _WIN32
        resultado = system("cls");
    #else
        resultado = system("clear");
    #endif

    if (resultado != 0) {
    }
}

void appPausar(void) {
    printf("\nPressione ENTER para continuar...");
    getchar();
}

void appExibirCabecalho(void) {
    printf("2026.1 PGPPCA-UFFS");
    printf("\nMestrado Profissional em Computacao Aplicada");
    printf("\nMCET042 - Projeto e Analise de Algoritmos");
    printf("\nProfessores: Dr. Denio Duarte e Dr. Samuel da Silva Feitosa");
    printf("\nDiscente: Valdemar Lorenzon Junior\n");
}

void appExibirSobre(void) {
    appLimparTela();
    appExibirCabecalho();
    printf("\nEnunciado:\n");
    printf("\nNesta atividade, o estudante devera submeter a solucao ");
    printf("implementada em C Ansi\n");
    printf("para o seguinte problema:\n");
    
    printf("\n- Abrir o arquivo myfile.dat (Data File) para leitura binaria\n");
    
    printf("- Ler os registros e carrega-los para a memoria usando alguma\n");
    printf("  estrutura de dados\n");
    
    printf("- Permitir fazer uma projecao dos registros consultando apenas\n");
    printf("  registros de um determinado tipo\n");
    
    printf("\nEstrutura do arquivo de dados e a seguinte:\n");
    
    printf("\n+-----+-------+-------+----+------+--------\n");
    printf("|Type |Length |Content|Type|Length|Content ..........\n");
    printf("+-----+-------+-------+----+------+--------\n");
    
    printf("\nOnde Type e o tipo do conteudo (C - Character, I - Integer,\n");
    printf("F - Float e S - String),\n");
    printf("Length e o tamnho em bytes do conteudo do registro e\n");
    printf("Content e o dado.\n");
    
    printf("\nA solucao deve ter um \"menu\" para o usuario escolher a carga\n");
    printf("e a consulta.\n");
    
    printf("\nNo caso da consulta, o usuario escolhe o tipo de dado.\n");
    printf("Por exemplo, caso escolher I,\n");
    printf("serao apresentados apenas os registros que contenham esse tipo.\n");
}

void appExibirDealhes   (void){
    appLimparTela();
    appExibirCabecalho();
    appExibirSobre();
    appPausar();
    appLimparTela();
    printf("\nEsta implementacao pode ser descrita conforme segue:\n");

    printf("\n- Ambiente de desenvolvimento:\n");
    printf("  onlinegdb.com (share: )\n");
    printf("\n- git hub");
    printf("  https://github.com/10r3nz0n/trabalhoPGPPCA-UFFS-PAA-01.git");
    
    printf("\n- Ambiente de compilacao local:\n");
    printf("  Windows 11 / w64devkit - ANSI C89\n");
    printf("  Comando de compilacao:\n");
    printf("    gcc -std=c89 -Wall -Wextra -pedantic -g main.c app.c\n");
    printf("    controller.c service.c repository.c lista.c listaapp.c\n");
    printf("    -o programa.exe\n");
    
    printf("\n- Padrao da linguagem:\n");
    printf("  ANSI C 89\n");
    
    printf("\n- Estrategia arquitetural:\n");
    printf("  Desenvolvimento em camadas: repository, service,\n");
    printf("  controller e aplicacao\n");
    
    printf("\n- Estrutura de dados:\n");
    printf("  Lista simplesmente encadeada\n");
    
    printf("\n- Definicoes estruturais:\n");
    printf("  nodo_t  : struct { char tipo; unsigned int tamanho;\n");
    printf("             void *valor; struct nodo *prox; }\n");
    printf("  lista_t : struct { nodo_t *inicio; nodo_t *fim; }\n");
    
    printf("\n- Observacao de desempenho:\n");
    printf("  O ponteiro 'fim' garante insercao O(1) ao final da lista\n");
    
    printf("\n- Organizacao modular:\n");
    printf("  lista       : lista.h / lista.c\n");
    printf("  repository  : repository.h / repository.c\n");
    printf("  service     : service.h / service.c\n");
    printf("  controller  : controller.h / controller.c\n");
    printf("  aplicacao   : app.h / app.c / listaapp.h / listaapp.c\n");
    printf("Adotado um espalhamento de service pelo controller e listaapp\n");
    printf("podendo entender que poderia ter juntado no service tudo");
    
    printf("\n- Fluxo de execucao:\n");
    printf("  O entrypoint (main) invoca um menu de opcoes, que aciona\n");
    printf("  o controller. Este delega ao service, que coordena as\n");
    printf("  operacoes sobre repository e lista, com apoio da camada\n");
    printf("  de aplicacao\n");
    printf("  Opcoes extras de menu foram adicionadas para apoio mesmo\n");
    printf("  que nao pertencam a solicitacao de solucao");
    
    printf("\n- Gerenciamento de memoria:\n");
    printf("  Tratamento de liberacao de memoria na recarga e na\n");
    printf("  finalizacao do programa\n");
    
    printf("\n- Manipulacao de dados:\n");
    printf("  Observado caso de não ter teminador de string no arquivo\n");
    printf("  e inserido focadamente no buffer\n");
    printf("  Copia de buffers realizada via memcpy para armazenamento\n");
    printf("  nos nodos da lista\n");
    
    
    printf("\n- Uso de macros e enumeracoes:\n");
    printf("  Macros (#define) utilizadas para mascaras simbolicas\n");
    printf("  Preferencia por macros neste contexto\n");
    printf("  Uso adicional de enum no repository com finalidade similar\n");
    
    printf("\n- Separacao de responsabilidades:\n");
    printf("  lista.h define a estrutura base da lista\n");
    printf("  listaapp.h encapsula comportamentos especificos da aplicacao\n");
}

void appExibirMenu(void) {
    printf("\nMenu de opcoes\n");
    printf("1 - Carregar arquivo\n");
    printf("2 - Consultar por tipo\n");
    printf("3 - Mostrar todos os registros\n");
    printf("-\n");
    printf("8 - Enunciado do problema\n");
    printf("9 - Detalhes de implementacao\n");
    printf("0 - Sair\n");
    printf("Escolha uma opcao: ");
}

int appLerOpcao(void) {
    int opcao;

    if (scanf("%d", &opcao) != 1) {
        appLimparBuffer(); /*o erro fica no buffer*/
        return -1;
    }
    appLimparBuffer();
    return opcao;
}

char appNormalizarTipo(char tipo) {
    return (char) toupper((unsigned char) tipo);
}

char appLerTipo(void) {
    char tipo;

    printf("\nInforme o tipo desejado [%c %c %c %c]: ",
           TIPO_CHAR, TIPO_INT, TIPO_FLOAT, TIPO_STRING);

    if (scanf(" %c", &tipo) != 1) {
        appLimparBuffer();
        return '\0';
    }

    appLimparBuffer();

    tipo = appNormalizarTipo (tipo);

    return tipo;
}

void appCorVerdeMatrix(void) {
    printf("\033[0;32m");
}

void appCorPadrao(void) {
    printf("\033[0m");
}