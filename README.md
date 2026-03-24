# Documento explicativo da solução

## 1. Apresentação

Este documento descreve, de forma narrativa, técnica e objetiva, como a solução foi construída a partir dos arquivos-fonte da aplicação.

O foco está em explicar a ideia do sistema, a amarração entre as camadas e o fluxo de execução, mostrando como a solução foi organizada para atender ao problema proposto.

A proposta geral do trabalho consiste em:

- ler um arquivo binário com registros heterogêneos
- armazenar esses registros em memória usando uma estrutura dinâmica
- permitir consultas por tipo de dado

A solução foi organizada em camadas, com separação entre interface da aplicação, controle do fluxo, serviço, acesso ao arquivo e estrutura de dados. Além disso, a estrutura de dados foi evoluída para uma forma abstrata, permitindo uso de lista simplesmente encadeada ou lista duplamente encadeada.

---

## 2. Contexto acadêmico identificado na aplicação

Conforme declarado na própria aplicação, o trabalho está inserido no seguinte contexto:

- 2026.1 PGPPCA-UFFS
- Mestrado Profissional em Computação Aplicada
- MCET042 - Projeto e Análise de Algoritmos
- Professores: Dr. Denio Duarte e Dr. Samuel da Silva Feitosa
- Discente: Valdemar Lorenzon Junior

Esse cabeçalho aparece na camada de aplicação e situa formalmente a entrega.

---

## 3. Enunciado do problema

O problema pede uma solução em C ANSI para:

- abrir o arquivo `myfile.dat` em leitura binária
- ler os registros e carregá-los para a memória usando alguma estrutura de dados
- permitir uma projeção dos registros consultando apenas os registros de um determinado tipo

A estrutura lógica do arquivo é:

```text
+-----+-------+-------+----+------+--------
|Type |Length |Content|Type|Length|Content ...
+-----+-------+-------+----+------+--------
```

Onde:

- `Type` representa o tipo do conteúdo
- `C` para Character
- `I` para Integer
- `F` para Float
- `S` para String
- `Length` representa o tamanho, em bytes, do conteúdo do registro
- `Content` representa o dado armazenado

Além disso, a solução deve apresentar um menu para o usuário escolher a carga e a consulta. No caso da consulta, o usuário informa o tipo desejado, e a aplicação mostra apenas os registros daquele tipo.

---

## 4. Ideia geral da solução

A solução foi construída com uma organização em camadas. Essa organização não foi usada apenas como detalhe estético do código, mas como forma de distribuir responsabilidades de modo mais claro.

A arquitetura observada na versão atual é:

- `main.c`
- `app.c` e `app.h`
- `controller.c` e `controller.h`
- `service.c` e `service.h`
- `repository.c` e `repository.h`
- `listaabstrata.h`
- `lista.c` e `lista.h`
- `listadupla.c` e `listadupla.h`
- `comumlistas.c` e `comumlistas.h`

Em termos conceituais, a aplicação funciona assim:

Usuário  
↓  
Aplicação  
↓  
Controller  
↓  
Service  
↓  
Repository  
↓  
Lista em memória

Essa sequência mostra a amarração principal do sistema. O usuário interage com o menu. A aplicação apresenta a interface textual. O controller interpreta a opção e também concentra parte da leitura específica do fluxo escolhido. O service coordena o caso de uso. O repository acessa o arquivo binário. A lista guarda os dados carregados.

---

## 5. Papel de cada camada

### 5.1 `main.c` - ponto de entrada e orquestração

A função `main` atua como ponto de entrada da aplicação. Seu papel é iniciar a estrutura principal, preparar a interface inicial e manter o ciclo de interação com o usuário.

No fluxo principal, a `main`:

- inicializa a lista principal
- entra em laço de menu
- lê a opção digitada pelo usuário
- delega a execução para o controller
- pausa entre iterações
- encerra quando a opção escolhida é sair

Isso mostra que a `main` não concentra regra de negócio. Ela apenas orquestra o ciclo de vida da aplicação.

### 5.2 `app.c` - camada de aplicação e interação textual

A camada `app` concentra a interface textual com o usuário e também registra informações institucionais e descritivas do trabalho.

Entre suas responsabilidades, estão:

- exibir o cabeçalho acadêmico
- exibir o enunciado do problema
- exibir os detalhes de implementação
- mostrar o menu
- limpar buffer de entrada
- pausar a execução
- limpar a tela
- aplicar detalhes visuais simples no terminal
- informar qual estrutura de lista está configurada no momento

### 5.3 `controller.c` - interpretação das opções e controle do fluxo imediato

A camada de controle recebe a opção escolhida no menu e decide qual fluxo deve ser executado.

O `controller` atua como intermediário entre a aplicação e o serviço. Seu papel é transformar uma escolha do usuário em uma operação concreta do sistema. Na versão atual, ele também passou a concentrar leituras pontuais mais ligadas ao fluxo de controle, como a solicitação do tipo na consulta.

As opções principais identificadas são:

- `1` - carregar arquivo padrão
- `2` - consultar por tipo
- `3` - mostrar todos os registros
- `6` - gerar arquivo parcial para teste
- `7` - funcionalidade reservada para evolução
- `8` - exibir o enunciado do problema
- `9` - exibir os detalhes de implementação
- `0` - sair

A importância do controller está em centralizar o despacho das ações e parte das decisões imediatas do fluxo de interface.

### 5.4 `service.c` - coordenação dos casos de uso

A camada de serviço é a principal amarração funcional da solução. Ela coordena os casos de uso reais do sistema.

Entre suas responsabilidades, estão:

- verificar se há dados carregados
- carregar os dados do arquivo
- consultar dados por tipo
- mostrar todos os registros
- gerar arquivo parcial
- encerrar o sistema com liberação de memória

A camada de serviço é o ponto onde a intenção do usuário vira operação concreta. Ela não depende diretamente do menu, mas trabalha com a lógica necessária para atender às solicitações da aplicação.

### 5.5 `repository.c` - leitura e geração de arquivos binários

A camada de repositório é responsável pela manipulação física dos arquivos binários.

O papel desse módulo é:

- abrir o arquivo em modo binário
- ler o tipo do registro
- ler o tamanho do conteúdo
- ler o conteúdo bruto
- inserir o conteúdo na lista
- repetir esse processo até o final do arquivo
- gerar um arquivo parcial de teste a partir do arquivo original

Esse módulo isola o acesso aos dados persistidos em arquivo, mantendo a leitura e a geração binária separadas da interface e das regras de uso da aplicação.

### 5.6 Estruturas de dados - lista abstrata, lista simples, lista dupla e itens comuns

A estrutura de dados deixou de ser tratada apenas como uma lista simples fixa e passou a ser organizada em torno de uma abstração.

A ideia adotada foi:

- `listaabstrata.h` como ponto central de escolha da implementação
- `lista.h / lista.c` para a lista simplesmente encadeada
- `listadupla.h / listadupla.c` para a lista duplamente encadeada
- `comumlistas.h / comumlistas.c` para itens comuns entre as duas listas

Isso permite que o restante do sistema trabalhe com a mesma ideia de `lista_t`, `nodo_t` e operações de lista, enquanto a implementação concreta pode ser trocada por uma `#define` em `listaabstrata.h`.

#### Lista simples

Modelagem:

- `nodo_t : struct { char tipo; unsigned int tamanho; void *valor; struct nodo *prox; }`
- `lista_t : struct { nodo_t *inicio; nodo_t *fim; }`

#### Lista dupla

Modelagem:

- `nodoDupla_t : struct { char tipo; unsigned int tamanho; void *valor; struct nodoDupla *anterior; struct nodoDupla *proximo; }`
- `listaDupla_t : struct { nodoDupla_t *inicio; nodoDupla_t *fim; }`

#### Itens comuns

O módulo `comumlistas` concentra o que é compartilhado entre as duas estruturas, como:

- validação de tipos válidos
- exibição do valor conforme o tipo armazenado

---

## 6. Como a solução funciona na prática

A execução começa com a inicialização da lista principal. Em seguida, a aplicação mostra o menu.

Quando o usuário escolhe a opção de carga, o controller aciona o service. O service coordena a operação de leitura junto ao repository. O repository percorre o arquivo binário registro por registro, interpretando `Type`, `Length` e `Content`, e insere cada item na lista.

Depois que os dados estão em memória, o usuário pode solicitar uma projeção por tipo. Nesse caso, o controller obtém o tipo desejado, valida a entrada, e o service percorre a lista mostrando apenas os nodos compatíveis com o filtro.

Se o usuário optar por mostrar todos os registros, o service percorre a estrutura completa sem filtro.

Além disso, foi incluída uma opção de geração de arquivo parcial, pensada para testes menores em vez de sempre trabalhar com arquivos muito grandes. Nesse caso, o controller coleta nome e quantidade, o service coordena e o repository grava o novo arquivo binário parcial.

Ao sair do sistema, a solução libera a memória alocada, limpando a lista antes da finalização do programa.

---

## 7. Amarração entre as funções e as chamadas

A ideia da solução pode ser descrita como um fluxo encadeado de responsabilidades:

- a aplicação apresenta o menu e a parte textual
- o controller interpreta a opção escolhida
- o service coordena o caso de uso correspondente
- o repository acessa ou gera o arquivo binário, quando necessário
- a lista recebe e mantém os dados em memória
- o service consulta a lista e entrega a saída solicitada

Essa amarração mostra uma construção modular. A solução não foi pensada apenas para funcionar, mas também para manter separação entre entrada, coordenação, acesso ao dado e armazenamento.

---

## 8. Características técnicas declaradas e observadas na solução

Entre as decisões técnicas adotadas, destacam-se:

- desenvolvimento em camadas
- uso de lista abstrata
- possibilidade de lista simplesmente encadeada ou duplamente encadeada
- uso de `void *` para armazenamento genérico do valor no nodo
- gerenciamento de memória na recarga e na finalização do programa
- cópia de buffers com `memcpy`
- cuidado com strings que podem não ter terminador no arquivo
- uso de ponteiro `fim` para inserção em `O(1)` ao final da lista
- compilação em ANSI C89
- organização modular por arquivos `.h` e `.c`
- módulo comum para itens compartilhados das listas
- geração de arquivo parcial para apoio de testes

---

## 9. Compilação e escolha da estrutura de lista

A escolha entre lista simples e lista dupla é feita em `listaabstrata.h`, por meio da `#define USAR_LISTA_DUPLA`.

Exemplo de compilação incluindo as duas implementações:

```bash
gcc -std=c89 -Wall -Wextra -pedantic -g main.c app.c controller.c service.c repository.c lista.c listadupla.c comumlistas.c -o programa.exe
```

Nesse caso, as duas implementações entram no executável, e a escolha da estrutura efetivamente usada ocorre pela `#define`.

Se a intenção for evitar código sobrando no executável, o comando de compilação pode ser ajustado para compilar apenas a implementação correspondente à escolha feita em `listaabstrata.h`.

---

## 10. Leitura interpretativa da proposta

Observando a solução como um todo, a proposta pode ser entendida assim:

- representar registros binários heterogêneos em uma estrutura dinâmica única
- separar a apresentação da lógica de controle
- usar uma camada de serviço como ponto de amarração da aplicação
- encapsular a leitura física do arquivo em um repositório
- permitir evolução da estrutura de dados por meio de abstração
- preservar uma construção tradicional e compatível com ANSI C

Ou seja, a solução não foi modelada como um programa monolítico. Ela foi organizada para que cada parte cumpra uma função definida dentro do fluxo geral, com abertura para evolução estrutural da lista.

---

## 11. Casos de uso principais

Os casos de uso mais visíveis da aplicação são:

- carregar o arquivo binário
- consultar registros por tipo
- mostrar todos os registros
- gerar arquivo parcial para testes
- exibir o enunciado do problema
- exibir os detalhes de implementação
- sair do sistema

---

## 12. Conclusão

A solução apresentada organiza o problema de leitura e projeção de registros binários em uma arquitetura modular, com separação entre interface textual, controle de fluxo, coordenação do caso de uso, acesso ao arquivo e armazenamento em memória.

Na versão mais recente, a solução foi ampliada com:

- abstração da estrutura de lista
- possibilidade de lista simples ou dupla
- módulo comum entre listas
- geração de arquivo parcial para testes
- redistribuição de algumas responsabilidades de entrada e controle

Do ponto de vista narrativo e técnico, a aplicação foi estruturada para que a leitura do arquivo, a persistência temporária em memória e a consulta dos dados ocorram de forma integrada, mas com responsabilidades separadas. Essa amarração entre camadas continua sendo um dos pontos mais relevantes da solução, agora com uma base mais flexível para evolução da estrutura de dados.
