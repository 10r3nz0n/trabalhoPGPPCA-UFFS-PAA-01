#ifndef LISTAABSTRATA_H
#define LISTAABSTRATA_H


#define USAR_LISTA_DUPLA 0 /*0 para simples - 1 pra dupla*/

/*
gcc -std=c89 -Wall -Wextra main.c app.c controller.c service.c repository.c lista.c listadupla.c comumlistas.c -o programa.exe

Assim as duas implementacoes entram no executavel. se nao quiser, adequar:
USAR_LISTA_DUPLA 0, manter apenas lista.c
USAR_LISTA_DUPLA 1, manter apenas listadupla.c

Ao adequar, nao tera codigo sobrando no .exe
*/


#if USAR_LISTA_DUPLA

#include "listadupla.h"

typedef listaDupla_t lista_t;
typedef nodoDupla_t  nodo_t;

#define listaInicializar        listaDuplaInicializar
#define listaEstaVazia          listaDuplaEstaVazia
#define listaAlocarNodo         listaDuplaAlocarNodo
#define listaDefinirValorNodo   listaDuplaDefinirValorNodo
#define listaInserirNoFim       listaDuplaInserirNoFim
#define listaLimpar             listaDuplaLimpar
#define listaMostrarNodo        listaDuplaMostrarNodo
#define prox                    proximo /*para o caso isolado do servive*/

#else

#include "lista.h"

#endif

#endif