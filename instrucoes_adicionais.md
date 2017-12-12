# Instruções adicionais
As instruções listadas nesse arquivo são aquelas não especificadas em 2.2.1 no arquivo [batalha.pdf](https://r0zbot.github.io/Batalha-de-robos-TecProg2017/pdfs/Batalha_Fase2.pdf).

Obs: Em todos os casos abaixo, _X_ é um inteiro.
* `ALC X`: Aloca _X_ espaços na pilha de execução para variáveis locais.
* `FRE X`: Libera _X_ espaços de variáveis locais na pilha de execução.
* `STL X`: Remove o elemento do topo da pilha e o armazena no espaço de variáveis locais na pilha de execução na posição _X_.
* `RCE X`: Empilha o elemento da posição _X_ do espaço de variáveis locais na pilha de execução .
* `NOP 0`: Nenhuma operação.

## Instruções leitura de dados

* `ATR X`: Lê  atributos da célula empilhada. X pode ser:
    * `0`: Tipo de terreno. Empilha um inteiro que representa o tipo de terreno da célula.
    * `1`: Quantidade de cristais. Empilha a quantidade de cristais que o robô esta carregando.
    * `2`: Ocupação. Empilha a ID do robô que se encontra ali, ou -1 se nenhum.
    * `3`: Base. Empilha a ID do exército que tem base ali, ou -1 se nenhum. 
    
    
* `MATR X`: Lê atributos sobre a máquina atual e empilha o resultado. X pode ser:
    * `0`: ID do robô
    * `1`: ID do exército
    * `2`: Combustível restante
    * `3`: HP restante
    * `4`: Quantidade de cristais
    * `5`: Célula atual. Empilha a célula em que o robô se encontra

## Instruções com tipos de dados compostos
Para passar um tipo composto em Assembly basta utilizar a seguinte sintaxe: `INTR {TYPE, {ARGUMENTS}}`,onde _INTR_ é o código da instrução a ser executa, _TYPE_ é o tipo do objeto que esta sendo passado, e _ARGUMENTS_ são os parametros necessários para a construção do objeto.

Existem três tipos de dados compostos que podem ser passados como parametro para as instruções:
* Number: pode ser passado diretamente como parametro, por exemplo: `PUSH 3`
* Action: deve ser passado como `INTR {ACTION, {SYS_CODE, DIRECTION}}`. Exemplo: `PUSH {ACTION, {MOVE, NW}}`
* Cell: deve ser passado como `INTR {CELL, {COLUNA, LINHA, BASE, OCUPAÇÃO, CRISTAIS, TERRENO}}`. Por Exemplo: `PUSH {CELL, {0, 0, 3, 2, 1, 8}}`

Obs: no caso de Cell os únicos argumentos obrigatórios para sua construção são _coluna_ e _linha_.

## System Calls

Chamadas ao sistema dependem de um _SystemCode_ e uma _Direction_. Seus valores estão declarados em seus respectivos enums e são os seguintes:

1. SystemCode
* `MOVE` = Representa ação de movimento em um determinada direção. Também empilha seu resultado como booleano.
* `COLLECT` = Representa ação de coleta em um determinada direção. Também empilha seu resultado como booleano.
* `DROP` = Representa ação de deposito em um determinada direção. Também empilha seu resultado como booleano.
* `ATKMELEE` = Representa ação de ataque corpo a corpo em um determinada direção. Também empilha seu resultado como booleano.
* `ATKSHORT` = Representa ação de ataque de pequeno alcance em um determinada direção. Também empilha seu resultado como booleano.
* `ATKLONG` = Representa ação de ataque de longo alcance em um determinada direção. Também empilha seu resultado como booleano.
* `SEE` = Empilha a célula vizinha ao robô em uma determinada direção
  
2. Direction
* `NE` = Representa direção nordeste
* `NW` = Representa direção noroeste
* `EA`  = Representa direção leste
* `WE`  = Representa direção oeste
* `SE` = Representa direção sudeste
* `SW` = Representa direção sudoeste

As chamadas ao sistema são realizadas por meio da instrução `SYS` que recebe como parametro um objeto do tipo _Action_.
Dessa forma, sua utilização deve ser feita da seguinte maneira: `SYS {ACTION, {SYS_CODE, DIRECTION}}`.

Exemplo:
* `SYS {ACTION, {MOVE, NE}}` = Faz uma requisição ao sistema para realizar uma ação de movimento na direção nordeste.
* `SYS {ACTION, {DROP, S}}` = Faz uma requisição ao sistema para realizar uma ação de depósito na direção sul.
