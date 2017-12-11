# Changelog

## Quarta fase
* Correção de bugs:
    * Resolvida Segfault ao modificar uma célula entre uma chamada de SEE e ATR
    * Resolvida segfault ao chamar ATR em uma célula de fora da Arena
* Adicionado montador para linguagem de alto nível

## Terceira fase
* Implementado manager.py
    * É possível alterar mais facilmente a configuração de diversos elementos da arena.
    * Maior facilidade para adicionar robôs e exércitos.
    * Geração de arenas aleatórias.
    * Importação de arenas salvas.
* Arena agora pode ser inicializada com um terreno definido.

## Segunda fase
* Implementadas classes e suas devidas funcionalidades (para mais detalhes, ver [documentação](https://r0zbot.github.io/Batalha-de-robos-TecProg2017/VirtualMachine/)): 
  * Entidade
    * Entidade estática
    * Entidade móvel
  * Robô
  * Arena
  * Exército
* Implementado sistema de log com 4 níveis de verbosidade (Debug, Info, Warn, Error)
* Refatorada pilha de execução usando nova implementação da [StackFrame](https://r0zbot.github.io/Batalha-de-robos-TecProg2017/VirtualMachine/class_stack_frame.html)
* Adicionadas propriedades ao robô, incluindo número de cristais, HP, e combustível.
* Execução de código agora gasta uma quantidade ~~muito~~ pequena de combustível a cada instrução, e quando ele acaba, a execução é interrompida.
* Implementado escalonador que executa cada máquina virtual da arena por uma quantidade limitada de ciclos de cada vez.
* Instrução PRN agora imprime ID do robô e nome do exército de origem.
* Implementadas chamadas de sistema
* Implementadas [instruções adicionais](instrucoes_adicionais.md) SYS, ATR e SEE.
* Implementada matriz e movimentação hexagonal.
* Robôs agora podem trabalhar com diversos tipos de dados.



## Primeira fase (mudanças em relação ao código fornecido pelo professor):

* Refatorado código para C++.
* Implementado arquivo _CMakeLists_ para construção do projeto _cross-platform_.
* Implementação completa do montador _builder.py_.
* Corrigido bug do montador no qual _CALLs_ e _JMP_ para labels posteriores gerava código inválido.
* Implementado espaço para variáveis locais na pilha de execução.
* Implementadas instruções _ALC_ e _FRE_, para alocação e liberação de memória local respectivamente.
* Implementadas instruções _STL_ e _RCE_ como especificado na documentação.
* Corrigida instrução _RET_ como especificado na documentação.
* Implementação própria de pilha para tornar possível alocar espaços de memória dentro dela.
* Criado script de execução e _build_ automático com detecção de erros para Windows.
