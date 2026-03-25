#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*No material, a insercao no fim usa um ponteiro auxiliar chamado aux para 
  guardar o ultimo nodo da lista. Na minha implementacao, esse mesmo papel 
  foi incorporado ao campo fim da estrutura _t. Assim, o first do material 
  corresponde ao meu inicio, o 'aux' corresponde ao meu fim e o 's' corresponde 
  ao meu novo nodo. 
  
  A logica de encadeamento continua a mesma: no primeiro 
  elemento, inicio e fim apontam para o mesmo nodo; nos proximos, o fim atual 
  aponta para o novo nodo e depois o fim passa a ser atualizado para esse 
  novo nodo.*/

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

        /*copiando os dados, evitando tratar aqui caso a caso void */
        /*o buffer terá free depois*/
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
    comumListasMostrarValor(nodo->tipo, nodo->valor);
    printf("\n");
}