#ifndef SERVICE_H
#define SERVICE_H

#include "lista.h"
#include "repository.h"

int              serviceListaPossuiDados (const lista_t *lista);
int              serviceListaEstaVazia   (const lista_t *lista);

retornoLeitura_t serviceCarregarDados    (lista_t       *lista,
                                          const char    *nomeArquivo);
                                          
int              serviceConsultarPorTipo (const lista_t *lista, 
                                          char           tipo);

int              serviceMostrarTodos     (const lista_t *lista);
void             serviceEncerrar         (lista_t *lista);

#endif