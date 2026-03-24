#ifndef LISTADUPLA_H
#define LISTADUPLA_H

#include "comumlistas.h"

typedef struct nodoDupla {
    
    char               tipo;
    unsigned int       tamanho;
    void              *valor;
    struct nodoDupla  *anterior;
    struct nodoDupla  *proximo;
    
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