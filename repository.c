#include "repository.h"
#include <stdio.h>
#include <stdlib.h>

static retornoLeitura_t repositoryLerRegistro            
       (FILE *arquivo, lista_t *lista, unsigned int *quantidadeRegistros);
       
static int repositoryLerConteudoEInserir    
       (FILE *arquivo, lista_t *lista, char tipo, unsigned int tamanho);

retornoLeitura_t repositoryCarregarArquivo(const char *nomeArquivo, lista_t *lista) {
    FILE *arquivo;
    unsigned int quantidadeRegistros = 0;
    retornoLeitura_t resultado;

    if (nomeArquivo == NULL || lista == NULL) {
        return RETORNA_FALHA;
    }

    arquivo = fopen(nomeArquivo, "rb");

    if (arquivo == NULL) {
        /*printf("\nNao foi possivel abrir o arquivo %s.\n", nomeArquivo);*/
        return RETORNA_FALHA;
    }

    do {
        resultado = repositoryLerRegistro(arquivo, lista, &quantidadeRegistros);

        if (resultado == RETORNA_FALHA) {
            /*printf("\nErro ao ler o arquivo binario.\n");*/
            fclose(arquivo);
            return RETORNA_FALHA; /*Early return, nao coloquei na condicao*/
        }
        
    } while (resultado == RETORNA_SUCESSO);


    fclose(arquivo);

    /*printf("\nArquivo %s carregado com sucesso.\n", nomeArquivo);
    printf("Quantidade de registros carregados: %u\n", quantidadeRegistros);*/

    return RETORNA_SUCESSO;
}

static retornoLeitura_t repositoryLerRegistro(FILE *arquivo, lista_t *lista, unsigned int *quantidadeRegistros) {
    char tipo;
    unsigned int tamanho;
    size_t lidos;

    lidos = fread(&tipo, sizeof(char), 1, arquivo);

    if (lidos == 0) {
        if (feof(arquivo)) {
            return RETORNA_FIM;
        }
        return RETORNA_FALHA;
    }

    if (!listaTipoEhValido(tipo)) {
        printf("\nTipo de registro invalido encontrado no arquivo: %c\n", tipo);
        return RETORNA_FALHA;
    }

    lidos = fread(&tamanho, sizeof(unsigned int), 1, arquivo);
    if (lidos != 1) {
        return RETORNA_FALHA;
    }

    if (tamanho == 0) {
        printf("\nRegistro com tamanho zero encontrado.\n");
        return RETORNA_FALHA;
    }

    if (!repositoryLerConteudoEInserir(arquivo, lista, tipo, tamanho)) {
        return RETORNA_FALHA;
    }

    *quantidadeRegistros = *quantidadeRegistros + 1;
    return RETORNA_SUCESSO;
}

static int repositoryLerConteudoEInserir(FILE *arquivo, lista_t *lista, char tipo, unsigned int tamanho) {
    void *buffer;
    size_t lidos;
    int inseriu;

    if (arquivo == NULL || lista == NULL) {
        return 0;
    }

    buffer = malloc(tamanho);
    if (buffer == NULL) {
        return 0;
    }

    lidos = fread(buffer, 1, tamanho, arquivo);
    if (lidos != tamanho) {
        free(buffer);
        return 0;
    }

    inseriu = listaInserirNoFim(lista, tipo, tamanho, buffer);

    free(buffer);
    return inseriu;
}