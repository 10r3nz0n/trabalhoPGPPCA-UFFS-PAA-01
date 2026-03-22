# Documento explicativo da solução

## 1. Apresentação

Este documento descreve, de forma narrativa, técnica e objetiva, como a solução foi construída a partir dos arquivos-fonte da aplicação. 

O foco está em explicar a ideia do sistema, a amarração entre as camadas e o fluxo de execução, mostrando como o aluno organizou a solução para atender ao problema proposto.

A proposta geral do trabalho consiste em ler um arquivo binário com registros heterogêneos, armazenar esses registros em memória usando uma estrutura dinâmica e permitir consultas por tipo de dado. 

A solução foi organizada em camadas, com separação entre interface da aplicação, controle do fluxo, serviço, acesso ao arquivo e estrutura de dados.

---

## 2. Contexto acadêmico identificado na aplicação

Conforme declarado na própria aplicação, o trabalho está inserido no seguinte contexto:

- 2026.1 PGPPCA-UFFS
- Mestrado Profissional em Computação Aplicada
- MCET042 - Projeto e Análise de Algoritmos
- Professores: Dr. Denio Duarte e Dr. Samuel da Silva Feitosa
- Discente: Valdemar Lorenzon Junior

Esse cabeçalho aparece na camada de aplicação e ajuda a situar formalmente a entrega.

---

## 3. Enunciado do problema, conforme a aplicação

A própria aplicação apresenta o enunciado da atividade. Em termos técnicos, o problema pede uma solução em C ANSI para:

- abrir o arquivo `myfile.dat` em leitura binária
- ler os registros e carregá-los para a memória usando alguma estrutura de dados
- permitir uma projeção dos registros consultando apenas os registros de um determinado tipo

A estrutura do arquivo é apresentada conceitualmente assim:

```text
+-----+-------+-------+----+------+--------
|Type |Length |Content|Type|Length|Content ...
+-----+-------+-------+----+------+--------
Onde:

Type representa o tipo do conteúdo
C para Character
I para Integer
F para Float
S para String
Length representa o tamanho, em bytes, do conteúdo do registro
Content representa o valor armazenado

Além disso, a solução deve apresentar um menu para o usuário escolher a carga e a consulta. No caso da consulta, o usuário informa o tipo desejado, e a aplicação mostra apenas os registros daquele tipo.

4. Ideia geral da solução

A solução foi construída com uma organização em camadas. Essa organização não foi usada apenas como detalhe estético do código, mas como forma de distribuir responsabilidades de modo mais claro.

A arquitetura observada é a seguinte:

main.c
app.c e app.h
controller.c e controller.h
service.c e service.h
repository.c e repository.h
lista.c e lista.h

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

Essa sequência mostra a amarração principal do sistema. O usuário interage com o menu. A aplicação coleta a entrada. O controller interpreta a opção. O service coordena o caso de uso. O repository acessa o arquivo binário. A lista guarda os dados carregados.

5. Papel de cada camada
5.1 main.c - ponto de entrada e orquestração

A função main atua como ponto de entrada da aplicação. Seu papel é iniciar a estrutura principal, preparar a interface inicial e manter o ciclo de interação com o usuário.

No fluxo principal, a main:

inicializa a lista principal
configura a exibição inicial
mostra o cabeçalho do trabalho
entra em laço de menu
lê a opção digitada pelo usuário
delega a execução para o controller

Isso mostra que a main não concentra regra de negócio. Ela apenas orquestra o ciclo de vida da aplicação.

5.2 app.c - camada de aplicação e interação textual

A camada app concentra a interação textual com o usuário e também registra informações institucionais e descritivas do trabalho.

Entre suas responsabilidades, estão:

exibir o cabeçalho acadêmico
exibir o enunciado do problema
exibir os detalhes de implementação
mostrar o menu
ler a opção escolhida
ler e normalizar o tipo informado
limpar buffer de entrada
pausar a execução
limpar a tela
aplicar detalhes visuais simples no terminal

Essa camada é importante porque torna a aplicação mais comunicativa. Ela não executa a lógica de leitura do arquivo, mas prepara a experiência de uso e documenta a intenção da solução.

5.3 controller.c - interpretação das opções

A camada de controle recebe a opção escolhida no menu e decide qual fluxo da aplicação deve ser executado.

O controller atua como intermediário entre a aplicação e o serviço. Seu papel é transformar uma escolha do usuário em uma operação concreta do sistema.

As opções principais identificadas são:

1 - carregar arquivo
2 - consultar por tipo
3 - mostrar todos os registros
8 - exibir o enunciado do problema
9 - exibir os detalhes de implementação
0 - sair

A importância do controller está em centralizar o despacho das ações. Assim, o menu não precisa conhecer a lógica interna do serviço, e o serviço também não precisa conhecer os detalhes da leitura de entrada do usuário.

5.4 service.c - coordenação dos casos de uso

A camada de serviço é a principal amarração funcional da solução. Ela coordena os casos de uso reais do sistema.

Entre suas responsabilidades, estão:

verificar se há dados carregados
carregar os dados do arquivo
consultar dados por tipo
mostrar todos os registros
encerrar o sistema com liberação de memória

A camada de serviço é o ponto onde a intenção do usuário vira operação concreta. Ela não depende diretamente do menu, mas trabalha com a lógica necessária para atender às solicitações da aplicação.

Esse ponto é importante para entender o desenho do sistema: o aluno não colocou toda a lógica em main nem jogou tudo diretamente no repositório. A solução tem um centro coordenador, que é justamente o service.

5.5 repository.c - leitura do arquivo binário

A camada de repositório é responsável pela leitura física do arquivo myfile.dat.

O papel desse módulo é:

abrir o arquivo em modo binário
ler o tipo do registro
ler o tamanho do conteúdo
ler o conteúdo bruto
inserir o conteúdo na lista
repetir esse processo até o final do arquivo

Esse módulo isola o acesso aos dados persistidos no arquivo, mantendo a leitura binária separada da interface e das regras de uso da aplicação.

5.6 lista.c - estrutura de dados em memória

A estrutura de dados escolhida para armazenar os registros foi uma lista simplesmente encadeada.

A modelagem descrita na própria aplicação é:

nodo_t  : struct { char tipo; unsigned int tamanho; void *valor; struct nodo *prox; }
lista_t : struct { nodo_t *inicio; nodo_t *fim; }

Essa escolha mostra alguns pontos relevantes:

cada nodo armazena o tipo do registro
cada nodo armazena o tamanho do conteúdo
o valor é mantido por meio de void *
a lista mantém ponteiro para o início e para o fim
a presença do ponteiro fim permite inserção em O(1) ao final

A estrutura foi pensada para suportar registros heterogêneos sem depender de uma única tipagem fixa.

6. Como a solução funciona na prática

A execução começa com a inicialização da lista principal. Em seguida, a aplicação mostra o cabeçalho do trabalho e apresenta o menu.

Quando o usuário escolhe a opção de carga, o controller aciona o service. O service coordena a operação de leitura junto ao repository. O repository percorre o arquivo binário registro por registro, interpretando Type, Length e Content, e insere cada item na lista.

Depois que os dados estão em memória, o usuário pode solicitar uma projeção por tipo. Nesse caso, o controller lê o tipo informado, a aplicação normaliza a entrada para maiúsculo, e o service percorre a lista mostrando apenas os nodos compatíveis com o filtro.

Se o usuário optar por mostrar todos os registros, o service percorre a estrutura completa sem filtro.

Ao sair do sistema, a solução libera a memória alocada, limpando a lista antes da finalização do programa.

7. Amarração entre as funções e as chamadas

A ideia da solução pode ser descrita como um fluxo encadeado de responsabilidades:

a aplicação apresenta o menu e coleta a entrada
o controller interpreta a opção escolhida
o service coordena o caso de uso correspondente
o repository acessa o arquivo binário, quando necessário
a lista recebe e mantém os dados em memória
o service consulta a lista e entrega a saída solicitada

Essa amarração é uma das características mais relevantes do trabalho, porque mostra uma construção modular. A solução não foi pensada apenas para funcionar, mas também para manter separação entre entrada, coordenação, acesso ao dado e armazenamento.

8. Características técnicas declaradas na própria aplicação

A função de detalhes da implementação destaca explicitamente várias decisões técnicas adotadas pelo aluno. Entre elas:

desenvolvimento em camadas
repository
service
controller
aplicação
uso de lista simplesmente encadeada
uso de void * para armazenamento genérico do valor no nodo
gerenciamento de memória na recarga e na finalização do programa
cópia de buffers com memcpy
cuidado com strings que podem não ter terminador no arquivo
uso de ponteiro fim para inserção em O(1) ao final da lista
compilação em ANSI C89
organização modular por arquivos .h e .c

Esses pontos ajudam a explicar a solução de forma técnica, mas ainda objetiva.

9. Leitura interpretativa da proposta do aluno

Observando a solução como um todo, a proposta do aluno pode ser entendida assim:

representar registros binários heterogêneos em uma estrutura dinâmica única
separar a apresentação da lógica de controle
usar uma camada de serviço como ponto de amarração da aplicação
encapsular a leitura física do arquivo em um repositório
preservar uma estrutura simples, tradicional e compatível com ANSI C

Ou seja, a solução não foi modelada como um programa monolítico. Ela foi organizada para que cada parte do sistema cumpra uma função definida dentro do fluxo geral.

10. Caso de uso principal da aplicação

Os principais casos de uso que emergem da solução são:

carregar o arquivo binário
consultar registros por tipo
mostrar todos os registros
exibir o enunciado do problema
exibir os detalhes de implementação
sair do sistema

Esses casos de uso ajudam a representar o sistema tanto no nível da aplicação quanto no nível do serviço.

11. Conclusão

A solução apresentada organiza o problema de leitura e projeção de registros binários em uma arquitetura modular, com separação entre interface textual, controle de fluxo, coordenação do caso de uso, acesso ao arquivo e armazenamento em memória.

Do ponto de vista narrativo e técnico, o aluno estruturou a aplicação para que a leitura do arquivo, a persistência temporária em memória e a consulta dos dados ocorram de forma integrada, mas com responsabilidades separadas. Essa amarração entre camadas é um dos pontos mais relevantes da solução, pois permite compreender claramente o que cada parte faz e como elas cooperam para atender ao enunciado.
