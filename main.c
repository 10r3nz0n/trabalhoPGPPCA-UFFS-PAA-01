#include <stdio.h>
#include "app.h"
#include "controller.h"
#include "listaabstrata.h"

int main(void) {
    int opcao;
    lista_t lista; 

    listaInicializar(&lista);
    appCorPadrao();
    
    do {
        
        appExibirMenu();
        opcao = appLerOpcao();
        controllerExecutarOpcao(opcao, &lista);
        
        if (opcao != 0) {
            appPausar();
        }

    } while (opcao != 0);
    
    appCorPadrao();
    return 0;
}