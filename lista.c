#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void listaInicializar(lista_t *lista) {
    if (lista == NULL) {
        return;
    }

    lista->inicio = NULL;
    lista->fim = NULL;
}

int listaEstaVazia(const lista_t *lista) {
    if (lista == NULL) {
        return TRUE;
    }

    return lista->inicio == NULL;
}

int listaTipoEhValido(char tipo) {
    return tipo == TIPO_CHAR ||
           tipo == TIPO_INT ||
           tipo == TIPO_FLOAT ||
           tipo == TIPO_STRING;
}

nodo_t *listaAlocarNodo(void) {
    nodo_t *nodo = (nodo_t *) malloc(sizeof(nodo_t));

    if (nodo == NULL) {
        return NULL;
    }

    nodo->tipo = '\0';
    nodo->tamanho = 0;
    nodo->valor = NULL;
    nodo->prox = NULL;

    return nodo;
}

int listaDefinirValorNodo(nodo_t *nodo, char tipo, unsigned int tamanho, const void *valor) {
    if (nodo == NULL || valor == NULL) {
        return FALSE;
    }

    nodo->tipo = tipo;
    nodo->tamanho = tamanho;

    if (tipo == TIPO_STRING) {
        nodo->valor = malloc(tamanho + 1);
        if (nodo->valor == NULL) {
            return FALSE;
        }

        memcpy(nodo->valor, valor, tamanho);
        ((char *) nodo->valor)[tamanho] = '\0';
        return TRUE;
    }

    nodo->valor = malloc(tamanho);
    if (nodo->valor == NULL) {
        return FALSE;
    }

    memcpy(nodo->valor, valor, tamanho);
    return TRUE;
}

int listaInserirNoFim(lista_t *lista, char tipo, unsigned int tamanho, const void *valor) {
    nodo_t *novo;

    if (lista == NULL || valor == NULL) {
        return FALSE;
    }

    if (!listaTipoEhValido(tipo)) {
        return FALSE;
    }

    novo = listaAlocarNodo();
    if (novo == NULL) {
        return FALSE;
    }

    if (!listaDefinirValorNodo(novo, tipo, tamanho, valor)) {
        free(novo);
        return FALSE;
    }

    if (listaEstaVazia(lista)) {
        lista->inicio = novo;
        lista->fim = novo;
        return TRUE;
    }

    lista->fim->prox = novo;
    lista->fim = novo;

    return TRUE;
}

void listaLimpar(lista_t *lista) {
    nodo_t *aux;
    nodo_t *temp;

    if (lista == NULL) {
        return;
    }

    aux = lista->inicio;
    while (aux != NULL) {
        temp = aux->prox;
        free(aux->valor);
        free(aux);
        aux = temp;
    }

    lista->inicio = NULL;
    lista->fim = NULL;
}

void listaMostrarNodo(const nodo_t *nodo) {
    if (nodo == NULL) {
        return;
    }

    printf("Tipo:\t%c\tTamanho:\t%u\tValor:\t", nodo->tipo, nodo->tamanho);

    switch (nodo->tipo) {
        case TIPO_CHAR:
            printf("%c", *(char *) nodo->valor);
            break;

        case TIPO_INT:
            printf("%d", *(int *) nodo->valor);
            break;

        case TIPO_FLOAT:
            printf("%.2f", *(float *) nodo->valor);
            break;

        case TIPO_STRING:
            printf("%s", (char *) nodo->valor);
            break;

        default:
            printf("Tipo desconhecido");
            break;
    }

    printf("\n");
}