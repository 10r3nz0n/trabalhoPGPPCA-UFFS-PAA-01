#include "comumlistas.h"

#include "listadupla.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void listaDuplaInicializar(listaDupla_t *lista) {
    if (lista == NULL) {
        return;
    }

    lista->inicio = NULL;
    lista->fim = NULL;
}

int listaDuplaEstaVazia(const listaDupla_t *lista) {
    if (lista == NULL) {
        return TRUE;
    }

    return lista->inicio == NULL;
}

nodoDupla_t *listaDuplaAlocarNodo(void) {
    nodoDupla_t *nodo = (nodoDupla_t *) malloc(sizeof(nodoDupla_t));

    if (nodo == NULL) {
        return NULL;
    }

    nodo->tipo = '\0';
    nodo->tamanho = 0;
    nodo->valor = NULL;
    nodo->anterior = NULL;
    nodo->proximo = NULL;

    return nodo;
}

int listaDuplaDefinirValorNodo(nodoDupla_t *nodo, char tipo, unsigned int tamanho, const void *valor) {

    if (nodo == NULL) {
        return FALSE;
    }

    if (tipo != TIPO_STRING && (valor == NULL || tamanho == 0)) {
        return FALSE;
    }

    if (tipo == TIPO_STRING && valor == NULL && tamanho > 0) {
        return FALSE;
    }

    nodo->tipo = tipo;
    nodo->tamanho = tamanho;

    if (tipo == TIPO_STRING) {
        nodo->valor = malloc(tamanho + 1);
        if (nodo->valor == NULL) {
            return FALSE;
        }

        /*copiando os dqados, evitando tratar aqui caso a caso*/
        memcpy(nodo->valor, valor, tamanho);
        
        if (((char *) nodo->valor)[tamanho - 1] != TERMINADOR_STRING) {
            ((char *) nodo->valor)[tamanho] = TERMINADOR_STRING;
        }
        return TRUE;
    }

    nodo->valor = malloc(tamanho);
    if (nodo->valor == NULL) {
        return FALSE;
    }

    memcpy(nodo->valor, valor, tamanho);
    return TRUE;
}

int listaDuplaInserirNoFim(listaDupla_t *lista, char tipo, unsigned int tamanho, const void *valor) {
    nodoDupla_t *novo;

    if (lista == NULL || valor == NULL) {
        return FALSE;
    }

    if (!comumListasListaTipoEhValido(tipo)) {
        return FALSE;
    }

    novo = listaDuplaAlocarNodo();
    if (novo == NULL) {
        return FALSE;
    }

    if (!listaDuplaDefinirValorNodo(novo, tipo, tamanho, valor)) {
        free(novo);
        return FALSE;
    }

    if (listaDuplaEstaVazia(lista)) {
        lista->inicio = novo;
        lista->fim = novo;
        return TRUE;
    }

    novo->anterior = lista->fim;
    lista->fim->proximo = novo;
    lista->fim = novo;

    return TRUE;
}

void listaDuplaLimpar(listaDupla_t *lista) {
    nodoDupla_t *aux;
    nodoDupla_t *temp;

    if (lista == NULL) {
        return;
    }

    aux = lista->inicio;
    while (aux != NULL) {
        temp = aux->proximo;
        free(aux->valor);
        free(aux);
        aux = temp;
    }

    lista->inicio = NULL;
    lista->fim = NULL;
}

void listaDuplaMostrarNodo(const nodoDupla_t *nodo) {
    if (nodo == NULL) {
        return;
    }

    printf("Tipo:\t%c\tTamanho:\t%u\tValor:\t", nodo->tipo, nodo->tamanho);
    comumListasMostrarValor(nodo->tipo, nodo->valor);
    printf("\n");
}