#include "service.h"
#include "app.h"
#include <stdio.h>

static int  servicePerguntarPaginacao       (void);
static int  serviceDesejaContinuarPaginacao (void);
static int  serviceDeveMostrarNodo          (const nodo_t *nodo,
                                             int usarFiltro,
                                             char tipoFiltro);
static int  serviceMostrarComFiltro         (const lista_t *lista,
                                             int usarFiltro,
                                             char tipoFiltro);

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
    lista_t listaLocal;

    if (lista == NULL || nomeArquivo == NULL) {
        return RETORNA_FALHA;
    }

    listaInicializar(&listaLocal);

    carregou = repositoryCarregarArquivo(nomeArquivo, &listaLocal);

    if (carregou != RETORNA_SUCESSO) {
        listaLimpar(&listaLocal);
        return RETORNA_FALHA;
    }

    listaLimpar(lista);
    *lista = listaLocal;

    return RETORNA_SUCESSO;
}

int serviceConsultarPorTipo(const lista_t *lista, char tipo) {
    if (lista == NULL || listaEstaVazia(lista)) {
        return FALSE;
    }

    if (!listaTipoEhValido(tipo)) {
        return FALSE;
    }

    return serviceMostrarComFiltro(lista, TRUE, tipo);
}

int serviceMostrarTodos(const lista_t *lista) {
    if (lista == NULL || listaEstaVazia(lista)) {
        return FALSE;
    }

    return serviceMostrarComFiltro(lista, FALSE, '\0');
}

void serviceEncerrar(lista_t *lista) {
    if (lista == NULL) {
        return;
    }

    listaLimpar(lista);
}

static int servicePerguntarPaginacao(void) {
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

static int serviceDesejaContinuarPaginacao(void) {
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

static int serviceDeveMostrarNodo(const nodo_t *nodo, int usarFiltro, char tipoFiltro) {
    if (nodo == NULL) {
        return FALSE;
    }

    if (!usarFiltro) {
        return TRUE;
    }

    return nodo->tipo == tipoFiltro;
}

static int serviceMostrarComFiltro(const lista_t *lista, int usarFiltro, char tipoFiltro) {
    nodo_t *aux;
    int encontrou = FALSE;
    int paginar;
    int count = 0;

    if (lista == NULL || listaEstaVazia(lista)) {
        return FALSE;
    }

    paginar = servicePerguntarPaginacao();

    if (usarFiltro) {
        printf("\nProjecao por tipo %c:\n", tipoFiltro);
    } else {
        printf("\nRegistros carregados:\n");
    }

    aux = lista->inicio;
    appCorVerdeMatrix();

    while (aux != NULL) {
        if (serviceDeveMostrarNodo(aux, usarFiltro, tipoFiltro)) {
            listaMostrarNodo(aux);
            encontrou = TRUE;
            count++;

            if (paginar && (count % 50 == 0)) {
                appCorPadrao();

                if (!serviceDesejaContinuarPaginacao()) {
                    appCorPadrao();
                    return TRUE;
                }

                appCorVerdeMatrix();
            }
        }

        aux = aux->prox;
    }

    appCorPadrao();
    return encontrou;
}