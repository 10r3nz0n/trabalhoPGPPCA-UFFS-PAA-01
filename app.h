#ifndef APP_H
#define APP_H

#include "comumlistas.h"
#include "listaabstrata.h"

void appLimparBuffer                (void);
void appLimparTela                  (void);
void appPausar                      (void);
void appExibirCabecalho             (void);
void appExibirSobre                 (void);
void appExibirMenu                  (void);
int  appLerOpcao                    (void);
void appCorVerdeMatrix              (void);
void appCorPadrao                   (void);
void appExibirDealhes               (void);
void appExibirQualEstruturaLista    (void);

#endif