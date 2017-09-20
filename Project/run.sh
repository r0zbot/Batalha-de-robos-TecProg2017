#!/bin/bash
python3 Builder/src/builder.py < $* > VirtualMachine/src/main.cpp
cd VirtualMachine
./build.sh
bin/VirtualMachine
