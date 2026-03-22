#include "controller.h"
#include "service.h"
#include "app.h"
#include <stdio.h>

void controllerExecutarOpcao(int opcao, lista_t *lista) {
    char tipo;

    switch (opcao) {
        case 1: {
            retornoLeitura_t retornoCarga;
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
                break;
            }
        
            if (retornoCarga == RETORNA_FALHA) {
                printf("\nNao foi possivel concluir a carga de dados.\n");
                break;
            }
        
            printf("\nRetorno inesperado na carga de dados.\n");
            break;
        }

        case 2: {
            if (serviceListaEstaVazia(lista)) {
                printf("\nLista vazia.\n");
                break;
            }
        
            tipo = appLerTipo();
            serviceConsultarPorTipo(lista, tipo);
            break;
        }

        case 3: {
            serviceMostrarTodos(lista);
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