# Batalha-de-robos-TecProg2017
## Requisitos

Para executar o projeto é necessário ter instaladas e no PATH do seu sistema as seguintes ferramentas:

* `CMake >= 3.8`
* `make >= 3.2 `
* `g++ >= 6.0`
* `Python 3`

## Compilando
Inicialmente, é necessário criar um arquivo assembly (.gubi) de teste de acordo com as especificações e salvá-lo em qualquer local (Há alguns exemplos em `Project/data`). 

### Windows
No Windows, basta arrastar um arquivo _.gubi_ para o batch script _run.bat_, ou passá-lo seu endereço como argumento da linha de comando. Isso montará e compilará os arquivos necessários, e executará o binário automaticamente.

### Linux
1. Criar um arquivo _main.cpp_, usando para isso o builder.py encontrado em `Project/Builder/src/`, e movê-lo para a pasta `Project/VirtualMachine/src/`. 

Ex: `Project/Builder/src/builder.py < Project/data/fibo.gubi > Project/VirtualMachine/src/main.cpp`

1. `cd Project/VirtualMachine`

1. Dentro da pasta `Project/VirtualMachine/`, checar o ambiente e criar a estrutura necessária para a compilação usando o comando `cmake -H. -G "MinGW Makefiles" -Bbuild`

1. Compilar os arquivos usando o comando `cmake --build build -- -j3`. O binário estará na pasta `Project/VirtualMachine/bin/`

1. Executar o binário compilado `bin/VirtualMachine`