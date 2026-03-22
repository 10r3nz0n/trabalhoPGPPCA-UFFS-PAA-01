#include "service.h"
#include <stdio.h>

int serviceListaPossuiDados(const lista_t *lista) {
    if (lista == NULL) {
        return FALSE;
    }

    return !listaEstaVazia(lista);
}

int serviceListaEstaVazia(const lista_t *lista) {
    if (lista == NULL) {
        return TRUE;
    }

    return listaEstaVazia(lista);
}

retornoLeitura_t serviceCarregarDados(lista_t *lista, const char *nomeArquivo) {
    retornoLeitura_t carregou;

    if (lista == NULL || nomeArquivo == NULL) {
        return RETORNA_FALHA;
    }

    listaLimpar(lista);
    listaInicializar(lista);

    carregou = repositoryCarregarArquivo(nomeArquivo, lista);

    if (carregou == RETORNA_FALHA) {
        printf("Falha ao carregar os dados.\n");
        return RETORNA_FALHA;
    }

    return RETORNA_SUCESSO;
}

void serviceConsultarPorTipo(const lista_t *lista, char tipo) {
    if (lista == NULL) {
        printf("\nLista inexistente.\n");
        return;
    }

    listaMostrarPorTipo(lista, tipo);
}

void serviceMostrarTodos(const lista_t *lista) {
    if (lista == NULL) {
        printf("\nLista inexistente.\n");
        return;
    }

    listaMostrarTodos(lista);
}

void serviceEncerrar(lista_t *lista) {
    if (lista == NULL) {
        return;
    }

    listaLimpar(lista);
}