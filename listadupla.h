#ifndef LISTADUPLA_H
#define LISTADUPLA_H

#include "comumlistas.h"

typedef struct nodoDupla {
    
    void              *valor;
    struct nodo       *prox;
    struct nodoDupla  *anterior;
    struct nodoDupla  *proximo;
    unsigned int       tamanho;
    char               tipo;
    
} nodoDupla_t;

typedef struct listaDupla {
    
    nodoDupla_t       *inicio;
    nodoDupla_t       *fim;
    
} listaDupla_t;

void        listaDuplaInicializar        (listaDupla_t        *lista);
int         listaDuplaEstaVazia          (const listaDupla_t  *lista);

nodoDupla_t
           *listaDuplaAlocarNodo         (void);

int         listaDuplaDefinirValorNodo   (nodoDupla_t         *nodo, 
                                          char                 tipo, 
                                          unsigned int         tamanho, 
                                          const void          *valor);
                                     
int         listaDuplaInserirNoFim       (listaDupla_t        *lista, 
                                          char                 tipo, 
                                          unsigned int         tamanho, 
                                          const void          *valor);
                                     
void        listaDuplaLimpar             (listaDupla_t        *lista);
void        listaDuplaMostrarNodo        (const nodoDupla_t   *nodo);

#endif