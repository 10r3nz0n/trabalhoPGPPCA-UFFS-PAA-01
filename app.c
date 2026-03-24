#include "app.h"
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

void appExibirQualEstruturaLista(void) {
    printf("\nNo momento esta solucao esta configurada para a lista:\n");
    (USAR_LISTA_DUPLA == 0) ? printf(" - Encadeamento simples\n")
                            : printf(" - Encadeamento duplo\n");
    printf("Alterar em 'listaabstrata.h: USAR_LISTA_DUPLA : 0-não e 1-sim\n");
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

void appExibirDealhes(void) {
    appLimparTela();
    appExibirCabecalho();
    appExibirSobre();
    appPausar();
    appLimparTela();

    printf("\nEsta implementacao pode ser descrita conforme segue:\n");

    printf("\n- Ambiente de desenvolvimento:\n");
    printf("  onlinegdb.com : onlinegdb.com/Yiokxhr1g\n");
    printf("  flags de compilacao: -std=c89 -Wall -Wextra\n");
    printf("  Pode haver versao mais atualizada que a registrada aqui no momento\n");

    printf("\n- Repositorio do projeto:\n");
    printf("  GitHub\n");
    printf("  https://github.com/10r3nz0n/trabalhoPGPPCA-UFFS-PAA-01.git\n");

    printf("\n- Ambiente de compilacao local:\n");
    printf("  Windows 11 / w64devkit\n");
    printf("  Padrao adotado: ANSI C89\n");

    printf("\n- Comandos de compilacao:\n");
    printf("  Compilando tudo:\n");
    printf("    gcc -std=c89 -Wall -Wextra -pedantic -g main.c app.c\n");
    printf("    controller.c service.c repository.c lista.c listadupla.c\n");
    printf("    comumlistas.c -o programa.exe\n");
    printf("\n");
    printf("  Assim, as duas implementacoes entram no executavel\n");
    printf("  e a escolha entre lista simples e dupla ocorre por define\n");
    printf("  em listaabstrata.h\n");
    printf("\n");
    printf("  Se quiser evitar codigo sobrando no executavel:\n");
    printf("    USAR_LISTA_DUPLA 0  - compilar com lista.c\n");
    printf("    USAR_LISTA_DUPLA 1  - compilar com listadupla.c\n");

    printf("\n- Padrao da linguagem:\n");
    printf("  ANSI C89\n");

    printf("\n- Estrategia arquitetural:\n");
    printf("  Desenvolvimento em camadas: repository, service,\n");
    printf("  controller e aplicacao\n");

    printf("\n- Estrutura de dados:\n");
    printf("  Solucao com lista abstrata\n");
    printf("  A estrutura concreta pode ser uma lista simplesmente\n");
    printf("  encadeada ou uma lista duplamente encadeada\n");

    printf("\n- Abstracao da lista:\n");
    printf("  O sistema utiliza listaabstrata.h como ponto central\n");
    printf("  para escolha da implementacao da lista\n");
    printf("  Assim, o restante do sistema trabalha com a mesma ideia\n");
    printf("  de lista_t, nodo_t e operacoes da lista, enquanto a\n");
    printf("  implementacao concreta pode ser trocada por define\n");

    printf("\n- Definicoes estruturais:\n");
    printf("  Lista simples:\n");
    printf("    nodo_t  : struct { char tipo; unsigned int tamanho;\n");
    printf("               void *valor; struct nodo *prox; }\n");
    printf("    lista_t : struct { nodo_t *inicio; nodo_t *fim; }\n");
    printf("\n");
    printf("  Lista dupla:\n");
    printf("    nodoDupla_t  : struct { char tipo; unsigned int tamanho;\n");
    printf("                    void *valor; struct nodoDupla *anterior;\n");
    printf("                    struct nodoDupla *proximo; }\n");
    printf("    listaDupla_t : struct { nodoDupla_t *inicio;\n");
    printf("                    nodoDupla_t *fim; }\n");
    
    appPausar();

    printf("\n- Organizacao modular:\n");
    printf("  lista simples : lista.h / lista.c\n");
    printf("  lista dupla   : listadupla.h / listadupla.c\n");
    printf("  abstracao     : listaabstrata.h\n");
    printf("  itens comuns  : comumlistas.h / comumlistas.c\n");
    printf("  repository    : repository.h / repository.c\n");
    printf("  service       : service.h / service.c\n");
    printf("  controller    : controller.h / controller.c\n");
    printf("  aplicacao     : app.h / app.c\n");

    printf("\n- Fluxo de execucao:\n");
    printf("  O entrypoint (main) invoca um menu de opcoes, que aciona\n");
    printf("  o controller. Este delega ao service, que coordena as\n");
    printf("  operacoes sobre repository e lista, com apoio da camada\n");
    printf("  de aplicacao\n");
    printf("  Opcoes extras de menu foram adicionadas para apoio mesmo\n");
    printf("  que nao pertencam diretamente a solicitacao principal\n");

    printf("\n- Gerenciamento de memoria:\n");
    printf("  Tratamento de liberacao de memoria na recarga e na\n");
    printf("  finalizacao do programa\n");

    printf("\n- Manipulacao de dados:\n");
    printf("  Observado o caso de nao haver terminador de string no\n");
    printf("  arquivo, sendo feita adequacao no buffer em memoria\n");
    printf("  Copia de buffers realizada via memcpy para armazenamento\n");
    printf("  nos nodos da lista\n");

    printf("\n- Uso de macros e enumeracoes:\n");
    printf("  Macros (#define) utilizadas para mascaras simbolicas,\n");
    printf("  inclusive na selecao da implementacao da lista abstrata\n");
    printf("  Uso adicional de enum no repository para controle do\n");
    printf("  fluxo de leitura do arquivo\n");

    printf("\n- Observacoes de codigo pertinentes:\n");
    printf("  .O ponteiro fim garante insercao O(1) ao final da lista\n");
    printf("  .Na lista dupla, alem do encadeamento para frente,\n");
    printf("   tambem ha o encadeamento para tras\n");
    printf("  .A abstracao da lista foi feita para manter o restante\n");
    printf("   do sistema com a mesma ideia de uso\n");
    printf("  .A lista e limpada ao sair do sistema, nao em main\n");
    printf("  .Insercao de caractere de fim na string do buffer\n");
    printf("  .Uso de memcpy para o buffer ser copiado para o nodo\n");
    printf("  .Uso de comentarios de bloco em compatibilidade com C89\n");
    printf("  .Mantive a ideia de repository mesmo sem abstrair a\n");
    printf("   estrutura de lista dentro dele\n");
    printf("  .Foram feitos incrementos na solucao para melhor\n");
    printf("   organizacao, reaproveitamento e apresentacao\n");
    
    printf("\n- Uso de agentes de IA:\n");
    printf("  .IA foi utilizda como nesta função para harmonizar escrita\n");
    printf("  .Utilizada para gerar codigo operacional que não depende de\n");
    printf("   logica, ex: esqueletos de switch-case\n");
    printf("  .Analise de solucao de codigo para certificacao de coerencia\n");
    printf("   logica do que se propunha a funcao\n");
    printf("  .Pesquisas diversas sobre caracteristicas de funcoes, sintaxe e\n");
    printf("   requisitos do trabalho: padrao C ANSI, confronto de minha\n");
    printf("   implementao pessoal de listas x apresentacao pelo material da\n");
    printf("   disciplina, analise de alguma necessidade de refatoracao\n");
    
    
    printf("\n- Observacoes finais:\n");
    printf("  .Buscado evitar redundancia de codigo\n");
    printf("  .Trazer responsabilidade dentro de um contexto unico aceitavel para a funcao\n");
    printf("  .A construcao em camadas foi para explorar um estudo atual pessoal do aluno\n");
    printf("  .A implementacao abstrata foi o mais perto de caso polimorfico de lista no paradigma\n");
    printf("   buscou-se uma pre implementacao de listas para trabalho futuro\n");
    printf("  .Tempo desempenhado: sex(2)+sab(7)+dom(3)+seg(2)+ter(4) = 18 .. 20 horas\n");
    
}

void appExibirMenu(void) {
    printf("\nMenu de opcoes\n");
    printf("1 - Carregar arquivo padrao - myfile.dat\n");
    printf("2 - Consultar por tipo\n");
    printf("3 - Mostrar todos os registros\n");
    printf("-\n");
    printf("6 - Gerar arquivo parcial pra teste de registros iniciais\n");
    printf("7 - Definir arquivo de carga\n");
    printf("8 - Enunciado do problema\n");
    printf("9 - Enunciado e detalhes de implementacao\n");
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