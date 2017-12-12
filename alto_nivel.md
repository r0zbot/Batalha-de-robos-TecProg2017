# Funcionamento da linguagem de alto nível

Novos Simbolos Terminais acrecentados
* Os Símbolos `true` e `false` representando os respectivos booleanos.
* O Símbolo `else` na condicional especificada abaixo.
* O Símbolo `for`usado no loop especificdo abaixo.
* Os nomes das System Calls espeficados abaixo.
* Os Símbolos `NE` `NW` `EA` `WE` `SE` `SW` representando as possiveis direções.
* Os Símbolos referentes ao atributos de uma célula,onde nome da váiavel que representa a célula seguido do símbolo retorna o atributo, sendo eles:
    * `.terreno`: retorna o atributo contendo um número que representa o tipo do terreno da célula.
    * `.cristais`: retorna o atributo contendo a quantidade de cristais naquelaa célula.
    * `.ocup`: retorna o atributo contendo o id do robô naquela célula, ou -1, caso não haja robôs.
    * `.base`: retorna o atributo contendo o id da exrcito a qual a base existente naquela célula pertence, ou -1 se não há base.
* Os símbolos `grass` `mountain` `street` `rock` `mud` representando os respectivos tipos de terreno. 
## Condicionais

Gramaticalmente Condicionais foram definidas podendoo ser um `if` (já definido) ou um `if` seguido de um `else`
`else`: o `else` segue o a gramática: else `Bloco`.
exemplo: if(x > y)
         {
            y = x;
         }
         else
         {
            x = y;
         }

## Loops

Gramaticalmente Loops foram definidos podendo ser um `while` (já definido) ou um `for`
`for`: um for segue a gramática: for(`Expr`, `Expr`, `Expr`) `Bloco`
exemplo: for(x = 4, x > 0, x = x - 1) {
               move(WE);
          }

## System Calls

As System Calls foram definidas como `Expr` e são feitas das seguindo o Padrão: nome_da_ação (DIRERAÇÃO) sendo elas:
* `move` = Representa ação de movimento em um determinada direção. Também retorna seu resultado como booleano.
* `collect` = Representa ação de coleta em um determinada direção. Também retorna seu resultado como booleano.
* `drop` = Representa ação de deposito em um determinada direção. Também retorna seu resultado como booleano.
* `atkmelee` = Representa ação de ataque corpo a corpo em um determinada direção. Também retorna seu resultado como booleano.
* `atkshort` = Representa ação de ataque de pequeno alcance em um determinada direção. Também retorna seu resultado como booleano.
* `atklong` = Representa ação de ataque de longo alcance em um determinada direção. Também retorna seu resultado como booleano.
* `see` = retorna a célula vizinha ao robô em uma determinada direção..

## Atributos do Robô

A gramática para acessar os atributos do próprio robô deve seguir o padrão: self.nome_do_atributo sendo eles:
* `id`: retorna a ID do robô
* `army`: retorna a ID do exército
* `full`: retorna qaunto de combustível que resta
* `hp`: retorna a HP restante
* `mycristals`: retorna a quantidade de cristais
* `cell`: retorna a célula em que o robô se encontra

