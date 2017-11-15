@echo off
cmake -H. -G "MinGW Makefiles" -Bbuild
cmake --build build -- -j3
"bin\VirtualMachine.exe"
pause