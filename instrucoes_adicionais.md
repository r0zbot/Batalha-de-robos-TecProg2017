# Instruções adicionais
As instruções listadas nesse arquivo são aquelas não especificadas em 2.2.1 no arquivo [batalha.pdf](https://r0zbot.github.io/Batalha-de-robos-TecProg2017/pdfs/Batalha_Fase2.pdf).

Obs: Em todos os casos abaixo, _X_ é um inteiro.
* `ALC X`: Aloca _X_ espaços na pilha de execução para variáveis locais.
* `FRE X`: Libera _X_ espaços de variáveis locais na pilha de execução.
* `STL X`: Remove o elemento do topo da pilha e o armazena no espaço de variáveis locais na pilha de execução na posição _X_.
* `RCE X`: Empilha o elemento da posição _X_ do espaço de variáveis locais na pilha de execução .
* `SYS OP`: Executa a chamada de systema identificada por _OP_.
Obs: Antes de ser chamada, seus argumentos devem ser empilhados na pilha de dados.
    * `OP = 1`: Move o robô na direção empilhada e a remove a direção da pilha.
    * `OP = 2`: Coleta um cristal na direção empilhada e remove a direção da pilha.
    * `OP = 3`: Deposita um cristal na direção empilhada e remove a direção da pilha.
    * `OP = 4`: Realiza um ataque a um inimigo em uma célula imediata na direção empilhada e remove a direção da pilha.
    * `OP = 5`: Realiza um ataque a um inimigo em curta distância na direção empilhada e remove a direção da pilha.
    * `OP = 6`: Realiza um ataque a um inimigo em longa distância na direção empilhada e remove a direção da pilha.
    
    Para empilhar a direção, deve ser executado `PUSH D`, onde D:
    * `D = 1` Direção a NORDESTE.
    * `D = 2` Direção a NOROESTE.
    * `D = 3` Direção a LESTE.
    * `D = 4` Direção a OESTE.
    * `D = 5` Direção a SUDESTE.
    * `D = 6` Direção a SUDOESTE.