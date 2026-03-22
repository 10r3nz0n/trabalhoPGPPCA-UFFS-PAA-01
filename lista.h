#ifndef LISTA_H
#define LISTA_H

#define TIPO_CHAR   'C'
#define TIPO_INT    'I'
#define TIPO_FLOAT  'F'
#define TIPO_STRING 'S'
#define TRUE 1
#define FALSE 0

typedef struct nodo {
    
    char          tipo;
    unsigned int  tamanho;
    void         *valor;
    struct nodo  *prox;
    
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
int         listaTipoEhValido       (char            tipo);
void        listaMostrarNodo        (const nodo_t   *nodo);

#endif