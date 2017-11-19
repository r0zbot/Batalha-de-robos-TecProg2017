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
* Linux: `xterm`
* Windows: `MinGW >= 2013072200`

## Execução

Inicialmente, é necessário criar um arquivo assembly ( _.gubi_ ) de teste de acordo com as especificações do projeto e salvá-lo em qualquer local (Há alguns exemplos em `Project/data`). 

Para executar o projeto, deve ser executado, usando Python2, o arquivo `Project/Manager/manager.py`. Esse script gerará um novo `main.cpp` e o executará.

As configurações da arena podem ser alteradas nas na seção _Arena settings_. A seguir, o terreno da arena deve ser especificado. Ele pode ser importado de um arquivo ou gerado aleatóriamente.

Para adicionar um robô a um dos exércitos, clicar em _Add Robots_ e selecionar um arquivo _.gubi_. É possível selecionar quantos robôs devem estar em cada exército com cada um dos programas. Além disso, é possível adicionar novos exércitos e renomeá-los.

Ao clicar em _Save and Run_, o arquivo `Project/VirtualMachine/src/main.cpp` será substituido por um novo contendo as alterações feitas, ele será compilado usando o CMake e executado em uma nova janela.
![interface manager.py](https://s33.postimg.org/xzypsl68f/image.png)
## Compilando manualmente 

1. Criar um arquivo _main.cpp_, usando para isso o manager.py encontrado em `Project/Manager/`, e salvá-lo sobre o existente em `Project/VirtualMachine/src/main.cpp`.

1. `cd Project/VirtualMachine`

1. Dentro da pasta `Project/VirtualMachine/`, checar o ambiente e criar a estrutura necessária para a compilação usando, no Linux, o comando `cmake -H. -Bbuild ` ou, no Windows, `cmake -H. -G "MinGW Makefiles" -Bbuild`

1. Compilar os arquivos usando o comando `cmake --build build -- -j3`. O binário estará na pasta `Project/VirtualMachine/bin/`

1. Executar o binário compilado dentro da pasta bin `bin/VirtualMachine` ou `bin/VirtualMachine.exe`

## Integrantes do grupo
* Daniel Martinez
* Lucas Moretto
* Pedro Paulo Bambace

## Comentários
Infelizmente, nosso visualizador _game_view.py_ não está muito rápido, então é necessário que a máquina virtual tenha um tempo de espera maior quando há muitos robôs presentes, para que o visualizador não fique atrasado em relação ao que acontece na máquina.
