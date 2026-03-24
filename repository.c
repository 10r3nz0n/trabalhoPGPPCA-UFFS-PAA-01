#include "repository.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Resolvi tirar as mensagens aqui por entender que estariam em camada inadequada
  Foram para o controller, mas com menor precisão para erros*/

static statusRetornoArquivo_t repositoryLerRegistro            
       (FILE *arquivo, lista_t *lista, unsigned int *quantidadeRegistros);
       
static int repositoryLerConteudoEInserir
       (FILE *arquivo, lista_t *lista, const char tipo, const unsigned int tamanho);

statusRetornoArquivo_t repositoryCarregarArquivo(const char *nomeArquivo, lista_t *lista) {
    FILE *arquivo;
    unsigned int quantidadeRegistros = 0;
    statusRetornoArquivo_t resultado;
    
    if ((nomeArquivo == NULL) || 
        (strcmp (nomeArquivo, "") == 0) ||  /*(nomeArquivo[0] == '\0')*/
        (lista == NULL)) {
        return RETORNA_FALHA;
    }

    arquivo = fopen(nomeArquivo, "rb");

    if (arquivo == NULL) {
        return RETORNA_FALHA;
    }
    
    if (fseek(arquivo, 0, SEEK_SET) != 0) {
        fclose(arquivo);
        return RETORNA_FALHA;
    }

    do {
        resultado = repositoryLerRegistro(arquivo, lista, &quantidadeRegistros);

        if (resultado == RETORNA_FALHA) {
            fclose(arquivo);
            return RETORNA_FALHA;
        }
        
    } while (resultado == RETORNA_SUCESSO);


    fclose(arquivo);

    /*printf("\nArquivo %s carregado com sucesso.\n", nomeArquivo);
    printf("Quantidade de registros carregados: %u\n", quantidadeRegistros);*/
    

    return RETORNA_SUCESSO;
}

static statusRetornoArquivo_t repositoryLerRegistro(FILE *arquivo, lista_t *lista, unsigned int *quantidadeRegistros) {
    char tipo;
    unsigned int tamanho;
    size_t lidos;

    lidos = fread(&tipo, sizeof(char), 1, arquivo);

    if (lidos == 0) { /*when fread returns 0 bytes, end of file - via aula*/
        /*entao tenta feof*/
        if (feof(arquivo)) {
            return RETORNA_FIM;
        }
        return RETORNA_FALHA;
    }

    if (!comumListasListaTipoEhValido(tipo)) {
        /*printf("\nTipo de registro invalido encontrado no arquivo: %c\n", tipo);*/
        return RETORNA_FALHA;
    }

    lidos = fread(&tamanho, sizeof(unsigned int), 1, arquivo); /*unsigned*/
    if (lidos != 1) {
        return RETORNA_FALHA;
    }

    if (tamanho == 0) {
        /*printf("\nRegistro com tamanho zero encontrado.\n");*/
        return RETORNA_FALHA;
    }

    if (!repositoryLerConteudoEInserir(arquivo, lista, tipo, tamanho)) {
        return RETORNA_FALHA;
    }

    *quantidadeRegistros = *quantidadeRegistros + 1;
    return RETORNA_SUCESSO;
}

static int repositoryLerConteudoEInserir(FILE *arquivo, lista_t *lista, const char tipo, const unsigned int tamanho) {
    void *buffer;
    size_t lidos;
    int inseriu;

    if (arquivo == NULL || lista == NULL) {
        return FALSE;
    }

    buffer = malloc(tamanho);
    if (buffer == NULL) {
        return FALSE;
    }

    lidos = fread(buffer, 1, tamanho, arquivo);
    if (lidos != tamanho) {
        free(buffer);
        return FALSE;
    }

    inseriu = listaInserirNoFim(lista, tipo, tamanho, buffer);

    free(buffer);
    return inseriu;
}

statusRetornoArquivo_t repositoryGerarArquivoParcial(const char *nomeOrigem,
                                               const char *nomeDestino,
                                               unsigned int quantidadeRegistros) {
    FILE *arquivoOrigem;
    FILE *arquivoDestino;
    char tipo;
    unsigned int tamanho;
    unsigned int quantidadeGravada;
    void *buffer;
    size_t lidos;
    statusRetornoArquivo_t retorno;

    if ((nomeOrigem == NULL) ||
        (nomeDestino == NULL) ||
        (strcmp(nomeOrigem, "") == 0) ||
        (strcmp(nomeDestino, "") == 0) ||
        (quantidadeRegistros == 0)) {
        return RETORNA_FALHA;
    }

    arquivoOrigem = fopen(nomeOrigem, "rb");
    if (arquivoOrigem == NULL) {
        return RETORNA_FALHA;
    }

    arquivoDestino = fopen(nomeDestino, "wb");
    if (arquivoDestino == NULL) {
        fclose(arquivoOrigem);
        return RETORNA_FALHA;
    }

    quantidadeGravada = 0;
    retorno = RETORNA_SUCESSO;

    while (quantidadeGravada < quantidadeRegistros) {
        lidos = fread(&tipo, sizeof(char), 1, arquivoOrigem);

        if (lidos == 0) {
            if (feof(arquivoOrigem)) {
                break;
            }

            retorno = RETORNA_FALHA;
            break;
        }

        if (!comumListasListaTipoEhValido(tipo)) {
            retorno = RETORNA_FALHA;
            break;
        }

        lidos = fread(&tamanho, sizeof(unsigned int), 1, arquivoOrigem);
        if (lidos != 1) {
            retorno = RETORNA_FALHA;
            break;
        }

        if (tamanho == 0) {
            retorno = RETORNA_FALHA;
            break;
        }

        buffer = malloc(tamanho);
        if (buffer == NULL) {
            retorno = RETORNA_FALHA;
            break;
        }

        lidos = fread(buffer, 1, tamanho, arquivoOrigem);
        if (lidos != tamanho) {
            free(buffer);
            retorno = RETORNA_FALHA;
            break;
        }

        if (fwrite(&tipo, sizeof(char), 1, arquivoDestino) != 1) {
            free(buffer);
            retorno = RETORNA_FALHA;
            break;
        }

        if (fwrite(&tamanho, sizeof(unsigned int), 1, arquivoDestino) != 1) {
            free(buffer);
            retorno = RETORNA_FALHA;
            break;
        }

        if (fwrite(buffer, 1, tamanho, arquivoDestino) != tamanho) {
            free(buffer);
            retorno = RETORNA_FALHA;
            break;
        }

        free(buffer);
        quantidadeGravada = quantidadeGravada + 1;
    }

    fclose(arquivoOrigem);
    fclose(arquivoDestino);

    return retorno;
}
