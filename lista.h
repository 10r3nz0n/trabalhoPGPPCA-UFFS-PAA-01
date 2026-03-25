#ifndef LISTA_H
#define LISTA_H

#include "comumlistas.h"

typedef struct nodo {
    
    void         *valor;
    struct nodo  *prox;
    unsigned int  tamanho;
    char          tipo;
    
} nodo_t;

typedef struct lista {
    
    nodo_t       *inicio;
    nodo_t       *fim;
    
} lista_t;

void        listaInicializar        (lista_t        *lista);
int         listaEstaVazia          (const lista_t  *lista);
nodo_t     *listaAlocarNodo         (void);

int         listaDefinirValorNodo   (nodo_t         *nodo, 
                                     char            tipo, 
                                     unsigned int    tamanho, 
                                     const void     *valor);
                                     
int         listaInserirNoFim       (lista_t        *lista, 
                                     char            tipo, 
                                     unsigned int    tamanho, 
                                     const void     *valor);
                                     
void        listaLimpar             (lista_t        *lista);
void        listaMostrarNodo        (const nodo_t   *nodo);

#endif