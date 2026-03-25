## Esta implementação pode ser descrita conforme segue

## Ambiente de desenvolvimento

- onlinegdb.com : onlinegdb.com/OVDuM_ldmT
- flags de compilacao: `-std=c89 -Wall -Wextra`

## Ambiente de compilação local

- Windows 11 / w64devkit
- Padrao adotado: ANSI C89

## Comandos de compilação

### Compilando tudo

```bash
gcc -std=c89 -Wall -Wextra -pedantic main.c app.c controller.c service.c repository.c lista.c listadupla.c comumlistas.c -o programa.exe
```

- Assim, as duas implementacoes entram no executavel
- e a escolha entre lista simples e dupla ocorre por define
- em `listaabstrata.h`

### Se quiser evitar código sobrando no executável

- `USAR_LISTA_DUPLA 0` - compilar com `lista.c`
- `USAR_LISTA_DUPLA 1` - compilar com `listadupla.c`

## Padrão da linguagem

- ANSI C89

## Estratégia arquitetural

- Desenvolvimento em camadas: lista, repository, service, controller e aplicacao

## Estrutura de dados

- Solucao com lista abstrata
- A estrutura concreta pode ser uma lista simples encadeada ou uma lista duplamente encadeada
- A configuração de entraga está para lista simples

## Abstração da lista

- O sistema utiliza `listaabstrata.h` como ponto central
- para escolha da implementacao da lista
- Assim, o restante do sistema trabalha com a mesma ideia
- de `lista_t`, `nodo_t` e operacoes da lista, enquanto a
- implementacao concreta pode ser trocada por define

## Definições estruturais

- Organizado em bytes de maior pra menor `size_t` devido padding

### Lista simples

```c
nodo_t : struct { void *valor; struct nodo *prox;
unsigned int tamanho; char tipo; }

lista_t : struct { nodo_t *inicio; nodo_t *fim; }
```

### Lista dupla

```c
nodoDupla_t : struct { void *valor; struct nodo *prox;
struct nodoDupla *anterior;
struct nodoDupla *proximo;
unsigned int tamanho;
char tipo;
char tipo; unsigned int tamanho; }

listaDupla_t : struct { nodoDupla_t *inicio;
nodoDupla_t *fim; }
```

## Organização modular

- lista simples : `lista.h / lista.c`
- lista dupla : `listadupla.h / listadupla.c`
- abstracao : `listaabstrata.h`
- itens comuns : `comumlistas.h / comumlistas.c`
- repository : `repository.h / repository.c`
- service : `service.h / service.c`
- controller : `controller.h / controller.c`
- aplicacao : `app.h / app.c`

## Fluxo de execução

- O entrypoint (`main`) invoca um menu de opcoes, que aciona o controller
- Este delega ao service, que coordena as operacoes sobre repository e lista, com apoio da camada de aplicacao
- Opcoes extras de menu foram adicionadas para apoio mesmo que nao pertencam diretamente a solicitacao principal

## Gerenciamento de memória

- Tratamento de liberacao de memoria na recarga e na finalizacao do programa

## Manipulação de dados

- Observado o caso de nao haver terminador de string no arquivo, sendo feita adequacao no buffer em memoria
- Copia de buffers realizada via `memcpy` para armazenamento nos nodos da lista

## Uso de macros e enumerações

- Macros (`#define`) utilizadas para mascaras simbolicas
- inclusive na selecao da implementacao da lista abstrata
- Uso adicional de `enum` no repository para controle do fluxo de leitura do arquivo

## Observações de código pertinentes

- O ponteiro `fim` garante insercao `O(1)` ao final da lista
- Na lista dupla, alem do encadeamento para frente, tambem ha o encadeamento para tras
- A abstracao da lista foi feita para manter o restante do sistema com a mesma ideia de uso
- A lista e limpada ao sair do sistema, nao em `main`
- Insercao de caractere de fim na string do buffer
- Uso de `memcpy` para o buffer ser copiado para o nodo
- Uso de comentarios de bloco em compatibilidade com C89
- Mantive a ideia de repository mesmo sem abstrair a estrutura de lista dentro dele
- Foram feitos incrementos na solucao para melhor organizacao, reaproveitamento e apresentacao

## Uso de agentes de IA

- IA foi utilizda para gerar codigo operacional que não depende de logica
- como nesta função para harmonizar escrita e jogar pra printfs na app.c
- Analise de solucao de codigo para certificacao de coerencia logica do que se propunha a funcao
- Pesquisas diversas sobre caracteristicas de funcoes, sintaxe e requisitos do trabalho: 
-  padrao C ANSI, confronto de minha implementao pessoal de listas x apresentacao pelo material da disciplina, analise de alguma necessidade de refatoracao

## Observações finais

- Buscado evitar redundancia de codigo
- Trazer responsabilidade dentro de um contexto unico aceitavel para a funcao
- A construcao em camadas foi para explorar um estudo atual pessoal do aluno
- A implementacao abstrata foi o mais perto de caso polimorfico de lista no paradigma
- Buscou-se uma pre implementacao de listas para trabalho futuro
- Tempo desempenhado: inicio sex20-03-2026(2h)+sab(7h)+dom(3h)+seg(2h)+ter(4h)+qua(2) = 20.. horas
