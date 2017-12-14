# Funcionamento da linguagem de alto nível

Novos Simbolos Terminais acrecentados
* Os símbolos `true` e `false` representando os respectivos booleanos.
* O símbolo `else` na condicional especificada abaixo.
* O símbolo `for`usado no loop especificado abaixo.
* Os nomes das System Calls espeficados abaixo.
* Os símbolos `NE` `NW` `EA` `WE` `SE` `SW` representando as possíveis direções.
* Os símbolos referentes ao atributos de uma célula, onde nome da váiavel que representa a célula seguido do símbolo retorna o atributo. Exemplo de uso:
 
  ```
  cell = see(NW);
  quantidade_de_cristais_na_celula = cell.cristais
  ```

    * `.terreno`: retorna um número que representa o tipo do terreno da célula, no qual:
        * `0` representa terreno normal/grama.
        * `1` representa terreno montanhoso/acidentado.
        * `2` representa terreno pavimentado/ruas.
        * `3` representa terreno inacessível/com pedras.
        * `4` representa terreno barroso/lama. 
    * `.cristais`: retorna o atributo contendo a quantidade de cristais naquelaa célula.
    * `.ocup`: retorna um número que representa o id do exército do robô naquela célula, ou -1, caso não haja robôs.
    * `.base`: retorna um número que representa o id da exército ao qual a base existente naquela célula pertence, ou -1 caso não for uma base.
* Os símbolos `grass` `mountain` `street` `rock` `mud` representando os respectivos tipos de terreno. 
* Os símbolos `!` `&` e `|` representação respectivamente a negação de um booleano e as operação de "E" e a "OU" entre booleanos. 

## Condicionais

Gramaticalmente Condicionais foram definidas podendoo ser um `if` (já definido) ou um `if` seguido de um `else`
`else`: o `else` segue o a gramática: else `Bloco`.
Exemplo:
 
```
if(x > y) {
    y = x;
}
else {
    x = y;
}
```

## Loops

Gramaticalmente Loops foram definidos podendo ser um `while` (já definido) ou um `for`: um for segue a gramática: for(`Expr`, `Expr`, `Expr`) `Bloco`

Exemplo: 

```
for(x = 4, x > 0, x = x - 1) {
    move(WE);
}

while (true) {
    move(SE);
}
```

## System Calls

As System Calls foram definidas como `Expr` e são feitas das seguindo o padrão `nome_da_ação (direção)`, sendo elas:
* `move`: Representa ação de movimento em um determinada direção. Também retorna seu resultado como booleano.
* `collect`: Representa ação de coleta em um determinada direção. Também retorna seu resultado como booleano.
* `drop`: Representa ação de deposito em um determinada direção. Também retorna seu resultado como booleano.
* `atkmelee`: Representa ação de ataque corpo a corpo em um determinada direção. Também retorna seu resultado como booleano.
* `see`: retorna a célula vizinha ao robô em uma determinada direção.

Exemplo:

```
resultado = collect(NE);
if(resultado == true) {
    move(NE);
}
```

## Atributos do Robô

Atributos do próprio robô podem ser acessados seguindo o padrão `self.nome_do_atributo`. Os atributos disponíveis são:
* `id`: retorna a ID do robô.
* `army`: retorna a ID do seu exército.
* `fuel`: retorna a quantidade de combustível restante.
* `hp`: retorna a vida restante do robô.
* `mycrystals`: retorna a quantidade de cristais que o robô está carregando.
* `cell`: retorna a célula em que o robô se encontra.

Exemplo:

```
celula_atual = self.cell;
if(celula_atual.base == self.army) {
    ...
}
```
(o código acima verifica se o robô está em uma base do seu próprio exército)
