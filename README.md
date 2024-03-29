# Batalha de robôs - TecProg2017

## [Changelog](changelog.md)

## [Documentação da Virtual Machine](https://r0zbot.github.io/Batalha-de-robos-TecProg2017/VirtualMachine/)
 Também pode ser vista em `docs/VirtualMachine`.

#### Veja também as [instruções adicionais implementadas](instrucoes_adicionais.md) e o [funcionamento da linguagem de alto nível](alto_nivel.md).

## Requisitos

Para executar o projeto é necessário ter instaladas e no PATH do seu sistema as seguintes ferramentas:

* `CMake >= 3.2`
* `make >= 3.2 `
* `g++ >= 6.0` (são usadas features do C++11)
* `Python 2.7.12`
* `TKinter`
* `Tk`
* `Pygame 1.9.3`
* Linux: `xterm`
* Windows: `MinGW >= 2013072200`

## Funcionamento

Nosso projeto é dividido em 4 módulos:
* Assembler: Responsável por transformar o código de alto nível em assembly, ambos no padrão especificado acima e pelos PDFs do projeto. Ele lê arquivos _.gubic_ e transforma-os em _.gubi_.
* Manager: Interface gráfica utilizada para configurar os parâmetros da VirtualMachine. Responsável pela transformação do código assembly (gerado pelo Assembler ou especificado manualmente) em um formato que possa ser compilado juntamente com a VirtualMachine, com as devidas configurações, exércitos e robôs. Ele lê arquivos _.gubi_ ou _.gubic_ e gera o _main.cpp_ no local apropriado, e em seguida, o compila usando _CMake_, e o executa.
* VirtualMachine: É a parte central do projeto, que executa o código compilado para cada um dos robôs, e gerencia as interações entre eles, mostrando o seu resultado tanto como texto no log quanto no visualizador da arena GameView.
* GameView: Responsável por mostrar o status da arena e dos robôs em uma interface gráfica.   

## Execução

Inicialmente, é necessário criar um arquivo assembly ( _.gubi_ ) ou um arquivo de linguagem de alto nível ( _.gubic_ )de teste de acordo com as especificações do projeto e salvá-lo em qualquer local (Há alguns exemplos em `Project/data`. Veja mais detalhes [aqui](testfiles.md)). 

Em seguida, é necessario compilar o assembler, localizado em `Project/Assembler`, usando para isso o comando `make assembler` no Linux ou `build.bat` no Windows. 

Para executar o projeto, deve ser executado, usando Python2, o arquivo `Project/Manager/manager.py`. Esse script gerará um novo `main.cpp` e o executará.

As configurações da arena podem ser alteradas nas na seção _Arena settings_. A seguir, o terreno da arena deve ser especificado. Ele pode ser importado de um arquivo ou gerado aleatóriamente.

Para adicionar um robô a um dos exércitos, clicar em _Add Robots_ e selecionar um arquivo com seu código. Se esse arquivo tiver a extensão _.gubic_, ele será montado/convertido para seu código assembly antes de ser adicionado à maquina virtual. É possível selecionar quantos robôs devem estar em cada exército com cada um dos programas. Além disso, é possível adicionar novos exércitos e renomeá-los.

Ao clicar em _Save and Run_, o arquivo `Project/VirtualMachine/src/main.cpp` será substituido por um novo contendo as alterações feitas, ele será compilado usando o CMake e executado em uma nova janela.

Informações adicionais de depuração são escritas na saida padrão do console. 

![interface manager.py](https://s33.postimg.org/xzypsl68f/image.png)
## Compilando manualmente 

1. Entrar no diretório do Assembler. `cd Project/Assembler`

1. Compilar o Assembler usando `make assembler` no Linux ou `build.bat` no Windows

1. Criar um arquivo _main.cpp_, usando para isso o manager.py encontrado em `Project/Manager/`, e salvá-lo sobre o existente em `Project/VirtualMachine/src/main.cpp`

1. `cd Project/VirtualMachine`

1. Dentro da pasta `Project/VirtualMachine/`, checar o ambiente e criar a estrutura necessária para a compilação usando, no Linux, o comando `cmake -H. -Bbuild ` ou, no Windows, `cmake -H. -G "MinGW Makefiles" -Bbuild`

1. Compilar os arquivos usando o comando `cmake --build build -- -j3`. O binário estará na pasta `Project/VirtualMachine/bin/`

1. Executar o binário compilado dentro da pasta bin `bin/VirtualMachine` ou `bin/VirtualMachine.exe`

## Integrantes do grupo
* Daniel Martinez
* Lucas Moretto
* Pedro Paulo Bambace

## Comentários
