@echo off
:: Futuramente pode ser usado para compilar diversos arquivos de maquina virtual de uma vez
:: set "acceptMultipleFiles=true"
setlocal ENABLEDELAYEDEXPANSION
:loop
    ::-------------------------- has argument ?
    if ["%~1"]==[""] (
        goto noarg
    )
    ::-------------------------- argument exist ?
    if not exist "%~1" (
        echo %~1 : no such file
        goto error
    ) else (
        :: Nao funciona em network drives =/
        rem if exist %~1\ (
        rem    echo %~1 : is a directory 
        rem    goto end
        rem ) else (
        rem    echo is a file
        rem )
        set "file=%~1"
        goto process
    )
    ::--------------------------
    if defined acceptMultipleFiles (
        shift
        goto loop
    )


:noarg
    if defined file goto process
    echo Arraste um arquivo .gubi para ca, digite seu nome ou o passe como argumento:
    set /p file=
    goto process
    

:process
    echo Building cpp file...
    cd %~dp0
    python "Builder\src\builder.py" %file% > "VirtualMachine\src\main.cpp"
    IF ERRORLEVEL 1 (
        echo Error building .cpp file
        goto error
    )
    echo Compiling virtual machine with cpp file...
    cd VirtualMachine
    call "build.bat"
    IF ERRORLEVEL 1 (
        echo Error compiling virtual machine
        goto error
    )
    echo Running virtual machine:
    cd %~dp0
    "VirtualMachine\bin\VirtualMachine.exe"
    IF ERRORLEVEL 1 (
        echo Error running virtual machine
        goto error
    )
    goto success


:error
    echo.
    echo -------------------------
    echo An error occurred
    goto end

:success
    echo.
    echo -------------------------
    echo Done

:end
pause