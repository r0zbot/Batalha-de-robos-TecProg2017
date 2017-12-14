## Arquivos de teste
Arquivos para teste, encontrados em `Project/data`.

OBS: há arquivos de teste além dos especificados nesse arquivo, porém talvez não tenham o funcionamento esperado.

#### Arenas disponíveis

* `empty.terrain`: Arena 20x10 vazia, feita 100% de grama.
* `random.terrain`: Arena 20x10 com terreno aleatório.
* `separated.terrain`: Arena 20x10 com separações entre os locais onde ficam as bases dos exércitos.
* `no_rocks.terrain`: Arena 20x10 com terreno aleatório, mas sem nenhum pedra.

#### Alto nível

* `smart_walk_collect_drop.gubic`: Anda a arena inteira para a direita coletando cristais, volta pra esquerda coletando cristais, e quando chega na base, coloca todos lá.
* `defender.gubic`: Ataca todos os robos que não são do seu exército.
* `attacker.gubic`: Anda pela arena e ataca todos os robôs de outros exércitos.

#### Assembly
Esses arquivos são exemplos de programas em assembly serem executados na maquina virtual para testar o funcionamento do projeto.

* `contaSimples.gubi`: Imprime (10+4)*3. Saida esperada: 42.

* `move_collect.gubi`: este programa faz o robô andar e coletar

* `move_attack_in_circles.gubi`: este programa faz o robô andar em volta da célula a sua equerda, atacando a cada 
moviemento a célula do lado oposto a que está rodeando

* `move_find_base.gubi`: este programa faz o robô andar e coletar cristais até achar a base de id 0, quando a acha 
ele coleta todas os cristais em volta e coloca na base e começa a atacar a célula de lado oposto ao da base

* `decision_robot1.gubi`: este programa faz o robô olhar para célula a noroeste e dependo do seu conteúdo ele toma 
diferentes atitudes, se nessa célula contém a base de id 0, ele coloca seus cristais nela, descobre se a célula a
sua esquerda está ocupada por algum robô inimigo, se sim ataca até não estar mais, se não anda nessa direção, já se a 
célula não contém uma base de id 0, ele olha se algum inimigo está nela e ataca até ele não estar mais, e então se 
move para está célula. 
