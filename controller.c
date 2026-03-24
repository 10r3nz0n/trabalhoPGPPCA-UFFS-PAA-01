#include "controller.h"
#include "service.h"
#include "app.h"
#include <stdio.h>

void controllerExecutarOpcao(int opcao, lista_t *lista) {
    char tipo;

    switch (opcao) {
        case 1: {
            statusRetornoArquivo_t retornoCarga;
            char resposta;

            if (serviceListaPossuiDados(lista)) {
                printf("\nLista contem valores. Deseja sobrepor? (S/N): ");

                if (scanf(" %c", &resposta) != 1) {
                    appLimparBuffer();
                    printf("\nEntrada invalida.\n");
                    break;
                }

                appLimparBuffer();

                if (resposta != 'S' && resposta != 's') {
                    printf("\nCarga cancelada pelo usuario.\n");
                    break;
                }
            }

            retornoCarga = serviceCarregarDados(lista, NOME_ARQUIVO);

            if (retornoCarga == RETORNA_SUCESSO) {
                printf("\nCarga de dados realizada com sucesso.\n");
            } else {
                printf("\nNao foi possivel concluir a carga de dados.\n");
            }

            break;
        }

        case 2: {
            int consultou;

            if (serviceListaEstaVazia(lista)) {
                printf("\nLista vazia.\n");
                break;
            }

            tipo = appLerTipo();

            if (!comumListasListaTipoEhValido(tipo)) {
                printf("\nTipo invalido.\n");
                break;
            }

            consultou = serviceConsultarPorTipo(lista, tipo);

            if (!consultou) {
                printf("\nNenhum registro encontrado para este tipo.\n");
            }

            break;
        }

        case 3: {
            int mostrou = serviceMostrarTodos(lista);

            if (!mostrou) {
                printf("\nNenhum registro encontrado.\n");
            }

            break;
        }

        case 6: {
            char nomeArquivoSaida[256];
            unsigned int quantidadeRegistros;
            statusRetornoArquivo_t retornoGeracao;

            printf("\nInforme o nome do novo arquivo: ");
            if (scanf("%255s", nomeArquivoSaida) != 1) {
                appLimparBuffer();
                printf("\nEntrada invalida.\n");
                break;
            }
            
            appLimparBuffer();

            printf("\nInforme a quantidade de registros para o corte: ");
            if (scanf("%u", &quantidadeRegistros) != 1) {
                appLimparBuffer();
                printf("\nEntrada invalida.\n");
                break;
            }
            
            appLimparBuffer();

            retornoGeracao = serviceGerarArquivoParcial(NOME_ARQUIVO,
                                                        nomeArquivoSaida,
                                                        quantidadeRegistros);

            if (retornoGeracao != RETORNA_SUCESSO) { 
                printf("\nNao foi possivel gerar o arquivo parcial.\n");
                break;
            }
            
            printf("\nArquivo parcial gerado com sucesso: %s.\n", nomeArquivoSaida);
            
            break;
        }
        
        case 7: {
            /*TODO: renomear o arquivo parcial pro original,
                    renomear antes o original pra um old,
                    talvez pedir o arquivo a ser usado no sistema
                     ao inicio e nao ter como hoje por macro...*/
            printf("Opcao em desenvolvimento.");
            break;
        }

        case 8: {
            appExibirSobre();
            break;
        }

        case 9: {
            appExibirDealhes();
            break;
        }

        case 0: {
            printf("\nEncerrando.... Liberando memoria!\n");
            serviceEncerrar(lista);
            printf("Encerrada execucao!");
            break;
        }

        default:
            printf("\nOpcao invalida.\n");
            break;
    }
}