# Batalha de robôs - TecProg2017

## [Changelog](changelog.md)

## [Documentação da Virtual Machine](https://r0zbot.github.io/Batalha-de-robos-TecProg2017/VirtualMachine/)
 Também pode ser vista em `docs/VirtualMachine`.

#### Veja também as [Instruções adicionais implementadas](instrucoes_adicionais.md).

## Requisitos

Para executar o projeto é necessário ter instaladas e no PATH do seu sistema as seguintes ferramentas:

* `CMake >= 3.2`
* `make >= 3.2 `
* `g++ >= 6.0` (são usadas features do C++11)
* `Python 2`
* `TKinter`
* Windows: `MinGW >= 2013072200`

## Compilando
Inicialmente, é necessário criar um arquivo assembly (.gubi) de teste de acordo com as especificações do projeto e salvá-lo em qualquer local (Há alguns exemplos em `Project/data`). 

### Script automático

#### Windows 
~~No Windows, basta arrastar um arquivo _.gubi_ para o batch script _run.bat_, ou passá-lo seu endereço como argumento da linha de comando. Isso montará e compilará os arquivos necessários, e executará o binário automaticamente.~~

#### Linux
~~Executar o _run.sh_ com o endereço do arquivo _.gubi_ como argumento da linha de comando. Isso montará e compilará os arquivos necessários, e executará o binário automaticamente.~~

OBS: Como nessa fase há outros componentes além da máquina virtual, tal script não é tão util, pois seria necessária uma configuração adicional. Logo, sua execução não foi testada e não é recomendada.

### Compilando manualmente 

1. Criar um arquivo _main.cpp_ (substituindo o existente se necessário), usando para isso o builder.py encontrado em `Project/Builder/src/`, e movê-lo para a pasta `Project/VirtualMachine/src/`. 
Ex: `Project/Builder/src/builder.py < Project/data/fibo.gubi > Project/VirtualMachine/src/main.cpp`

1. `cd Project/VirtualMachine`

1. Dentro da pasta `Project/VirtualMachine/`, checar o ambiente e criar a estrutura necessária para a compilação usando, no Linux, o comando `cmake -H. -Bbuild ` ou, no Windows, `cmake -H. -G "MinGW Makefiles" -Bbuild`

1. Compilar os arquivos usando o comando `cmake --build build -- -j3`. O binário estará na pasta `Project/VirtualMachine/bin/`

1. Executar o binário compilado dentro da pasta bin `bin/VirtualMachine` ou `bin/VirtualMachine.exe`

## Integrantes do grupo
* Daniel Martinez
* Lucas Moretto
* Pedro Paulo Bambace
