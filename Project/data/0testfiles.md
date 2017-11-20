## Arquivos de teste
Esses arquivos são exemplos de programas a serem executados na maquina virtual para testar o funcionamento do projeto.

* `move_collect.gubi`: este programa faz o robô andar e coletar

* `move_attack_in_circles.gubi`: este programa faz o robô andar em volta da célula a sua equerda, atacando a cada 
moviemento a célula do lado oposto a que está rodeando

* `good_walk.gubi`: este programa faz o robô andar na mesma direção, até que não seja possível andar para ela (seja 
por conta de uma pedra, ou por conta de um robô), neste caso ele muda a direção e continua o processo

* `move_find_base.gubi`: este programa faz o robô andar e coletar cristais até achar a base de id 0, quando a acha 
ele coleta todas os cristais em volta e coloca na base e começa a atacar a célula de lado oposto ao da base

* `decision_robot1.gubi`: este programa faz o robô olhar para célula a noroeste e dependo do seu conteúdo ele toma 
diferentes atitudes, se nessa célula contém a base de id 0, ele coloca seus cristais nela, descobre se a célula a
sua esquerda está ocupada por algum robô inimigo, se sim ataca até não estar mais, se não anda nessa direção, já se a 
célula não contém uma base de id 0, ele olha se algum inimigo está nela e ataca até ele não estar mais, e então se 
move para está célula e reinicia o processo 
