## Changelog
### Primeira fase (mudanças em relação ao código fornecido pelo professor):
* Refatorado código para C++.
* Implementado arquivo CMakeLists para construção do projeto _cross-platform_.
* Implementado Montador completo.
* Corrigido bug do montador no qual _CALLs_ e _JMP_ para labels posteriores gerava código inválido.
* Implementado espaço para variáveis locais na pilha de execução.
* Implementadas instruções ALC e FRE, para alocação e liberação de memória local respectivamente.
* Implementadas instruções STL e RCE como especificado na documentação.
* Implementação própria de _Pilha_ para tornar possível alocar espaçoes de memória dentro dela.
* Criado script de execução e _build_ automático com detecção de erros para Windows.