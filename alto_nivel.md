# Funcionamento da linguagem de alto nível

Novos Simbolos Terminais acrecentados
* Os Símbolos `true` e `false` representando os respectivos booleanos.
* O Símbolo `else`(`ELSE`) na condicional especificada abaixo.
* O Símbolo `for` (`FOR`) usado no loop especificdo abaixo.
* Os nomes das System Calls espeficados abaixo.
* Os Símbolos `CE` `NE` `NW` `EA` `WE` `SE` `SW` representando as possiveis direções (`DIR`).
* Os Símbolos referentes ao atributos de uma célula,onde nome da váiavel que representa a célula seguido do símbolo retorna o atributo, sendo eles:
    * `.terreno`: retorna o atributo contendo um número que representa o tipo do terreno da célula.
    * `.cristais`: retorna o atributo contendo a quantidade de cristais naquelaa célula.
    * `.ocup`: retorna o atributo contendo o id do robô naquela célula, ou -1, caso não haja robôs.
    * `.base`: retorna o atributo contendo o id da exrcito a qual a base existente naquela célula pertence, ou -1 se não há base.
##Condicionais

Gramaticalmente Condicionais foram definidas podendoo ser um `if` (já definido) ou um `if` seguido de um `else`
`else`: o `else` segue o a gramática: `ELSE` `Bloco`.

##Loops

Gramaticalmente Loops foram definidos podendo ser um `while` (já definido) ou um `for`
`for`: um for segue a gramática: `FOR` `OPEN` `Expr` `SEP` `Expr` `SEP` `Expr` `CLOSE`

##System Calls

As System Calls foram definidas como `Expr` e são feitas das seguindo o Padrão: nome_da_ação `OPEN` `DIR` `CLOSE` sendo elas:
* `move` = Representa ação de movimento em um determinada direção. Também retorna seu resultado como booleano.
* `collect` = Representa ação de coleta em um determinada direção. Também retorna seu resultado como booleano.
* `drop` = Representa ação de deposito em um determinada direção. Também retorna seu resultado como booleano.
* `atkmelee` = Representa ação de ataque corpo a corpo em um determinada direção. Também retorna seu resultado como booleano.
* `atkshort` = Representa ação de ataque de pequeno alcance em um determinada direção. Também retorna seu resultado como booleano.
* `atklong` = Representa ação de ataque de longo alcance em um determinada direção. Também retorna seu resultado como booleano.
* `see` = retorna a célula vizinha ao robô em uma determinada direção
* `my_id` = retorna o seu próprio id.

