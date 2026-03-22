#include <stdio.h>
#include "app.h"
#include "controller.h"
#include "lista.h"

int main(void) {
    int opcao;
    lista_t lista; /*A declaraçao estrutura de dados ficou aqui*/

    listaInicializar(&lista);

    appCorPadrao();
    appLimparTela();
    appExibirCabecalho();

    do {
        
        appExibirMenu();
        opcao = appLerOpcao();
        controllerExecutarOpcao(opcao, &lista);
        
        if (opcao != 0) {
            appPausar();
            appLimparTela();
            appExibirCabecalho();
        }

    } while (opcao != 0);
    
    appCorPadrao();
    /*lista e limpada no service*/
    return 0;
}