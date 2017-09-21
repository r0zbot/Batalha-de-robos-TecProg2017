## Changelog
### Primeira fase (mudanças em relação ao código fornecido pelo professor):
* Refatorado código para C++.
* Implementado arquivo _CMakeLists_ para construção do projeto _cross-platform_.
* Implementação completa do montador _builder.py_.
* Corrigido bug do montador no qual _CALLs_ e _JMP_ para labels posteriores gerava código inválido.
* Implementado espaço para variáveis locais na pilha de execução.
* Implementadas instruções _ALC_ e _FRE_, para alocação e liberação de memória local respectivamente.
* Implementadas instruções _STL_ e _RCE_ como especificado na documentação.
* Corrigida instrução _RET_ como especificado na documentação.
* Implementação própria de Pilha para tornar possível alocar espaços de memória dentro dela.
* Criado script de execução e _build_ automático com detecção de erros para Windows.