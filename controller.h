#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "listaabstrata.h"


char appLerTipo              (void);
char appNormalizarTipo       (char tipo);
void controllerExecutarOpcao (int opcao, lista_t *lista);

#endif