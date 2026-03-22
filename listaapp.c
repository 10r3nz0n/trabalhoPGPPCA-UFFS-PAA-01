#include "listaapp.h"
#include <stdio.h>


static int  listaPerguntarPaginacao       (void);
static int  listaDeveMostrarNodo          (const nodo_t *nodo, 
                                           int usarFiltro, 
                                           char tipoFiltro);
static void listaMostrarComFiltro         (const lista_t *lista, 
                                           int usarFiltro, 
                                           char tipoFiltro);
static int  listaDesejaContinuarPaginacao (void);


static int listaPerguntarPaginacao(void) {
    char resposta;

    printf("\nDeseja paginar a apresentacao a cada 50 registros? (S/N): ");
    if (scanf(" %c", &resposta) != 1) {
        appLimparBuffer();
        return FALSE;
    }
    
    appLimparBuffer();

    if (resposta == 'S' || resposta == 's') {
        return TRUE;
    }

    return FALSE;
}

static int listaDesejaContinuarPaginacao(void) {
    char resposta;

    printf("\nPressione ENTER para continuar ou 0 para parar: ");
    resposta = getchar();

    if (resposta != '\n') {
        appLimparBuffer();
    }

    if (resposta == '0') {
        return FALSE;
    }

    return TRUE;
}

static int listaDeveMostrarNodo(const nodo_t *nodo, int usarFiltro, char tipoFiltro) {
    if (nodo == NULL) {
        return FALSE;
    }

    if (!usarFiltro) {
        return TRUE;
    }

    return nodo->tipo == tipoFiltro;
}

static void listaMostrarComFiltro(const lista_t *lista, int usarFiltro, char tipoFiltro) {
    nodo_t *aux;
    int encontrou = FALSE;
    int paginar;
    int count = 0;

    if (lista == NULL || listaEstaVazia(lista)) {
        printf("\nLista vazia.\n");
        return;
    }

    paginar = listaPerguntarPaginacao();

    if (usarFiltro) {
        printf("\nProjecao por tipo %c:\n", tipoFiltro);
    } else {
        printf("\nRegistros carregados:\n");
    }

    aux = lista->inicio;
    appCorVerdeMatrix();
    while (aux != NULL) {
        if (listaDeveMostrarNodo(aux, usarFiltro, tipoFiltro)) {
            listaMostrarNodo(aux);
            encontrou = TRUE;
            count++;

            if (paginar && (count % 50 == 0)) {
                appCorPadrao();
                if (!listaDesejaContinuarPaginacao()) {
                    printf("\nExibicao interrompida pelo usuario.\n");
                    return;
                }
                appCorVerdeMatrix();
            }
        }

        aux = aux->prox;
    }
    
    appCorPadrao();
    if (!encontrou) {
        if (usarFiltro) {
            printf("Nenhum registro encontrado para este tipo.\n");
        } else {
            printf("Nenhum registro encontrado.\n");
        }
    }
}

void listaMostrarTodos(const lista_t *lista) {
    listaMostrarComFiltro(lista, FALSE, '\0');
}

void listaMostrarPorTipo(const lista_t *lista, char tipo) {
    if (!listaTipoEhValido(tipo)) {
        printf("\nTipo invalido.\n");
        return;
    }

    listaMostrarComFiltro(lista, TRUE, tipo);
}