#include "comumlistas.h"
#include <stdio.h>


int comumListasListaTipoEhValido(char tipo) {
    return tipo == TIPO_CHAR ||
           tipo == TIPO_INT ||
           tipo == TIPO_FLOAT ||
           tipo == TIPO_STRING;
}


void comumListasMostrarValor(char tipo, const void *valor) {
    switch (tipo) {
        case TIPO_CHAR:
            printf("%c", *(const char *) valor);
            break;

        case TIPO_INT:
            printf("%d", *(const int *) valor);
            break;

        case TIPO_FLOAT:
            printf("%f", *(const float *) valor);
            break;

        case TIPO_STRING:
            printf("%s", (const char *) valor);
            break;

        default:
            printf("Tipo desconhecido");
            break;
    }
}