#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$DIR"
rm bin/VirtualMachine
cmake -H. -Bbuild
cmake --build build -- -j3
bin/VirtualMachine
sleep 10s
