#ifndef SERVICE_H
#define SERVICE_H

#include "listaabstrata.h"
#include "repository.h"

int              serviceListaPossuiDados (const lista_t *lista);
int              serviceListaEstaVazia   (const lista_t *lista);

statusRetornoArquivo_t serviceCarregarDados    
                                         (lista_t       *lista,
                                          const char    *nomeArquivo);
                                          
int              serviceConsultarPorTipo (const lista_t *lista, 
                                          char           tipo);

int              serviceMostrarTodos     (const lista_t *lista);
void             serviceEncerrar         (lista_t *lista);


statusRetornoArquivo_t serviceGerarArquivoParcial
                                         (const char *nomeOrigem,
                                          const char *nomeDestino,
                                          unsigned int quantidadeRegistros);
                                          

#endif