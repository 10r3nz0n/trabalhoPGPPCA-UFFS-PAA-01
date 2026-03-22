#ifndef REPOSITORY_H
#define REPOSITORY_H

#include "lista.h"

/*Como vou trabalhar com status, ao inves de 0,1,-1 vou usar enum com palavras*/
typedef enum retornoLeitura{
    RETORNA_FIM = 0,
    RETORNA_SUCESSO = 1,
    RETORNA_FALHA = -1
} retornoLeitura_t;

/*Caso muda-se o nome do arquivo, nao quis fazer pedir o nome ao usuario ainda*/

#define NOME_ARQUIVO "myfile.dat"

/*Aqui nenhuma estrutura global, para nao ser ma pratica, lista fica em main*/

retornoLeitura_t repositoryCarregarArquivo (const char *nomeArquivo, 
                                            lista_t    *lista);

#endif