@echo off
cd %~dp0
del "bin\VirtualMachine.exe"
cmake -H. -G "MinGW Makefiles" -Bbuild
cmake --build build -- -j3
"bin\VirtualMachine.exe"
timeout /t 10
