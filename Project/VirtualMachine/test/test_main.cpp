#include <stdio.h>

#include "../include/code.h"
#include "../include/instruction.h"
#include "../include/machine.h"

void test_fibonnaci() {
    printf("\nTEST CASE [FIBONNACI] \n");

    Instruction prog[] = {
        Instruction(Code::PUSH, 1)
        ,Instruction(Code::DUP, 0)
        ,Instruction(Code::STO, 0)
        ,Instruction(Code::STO, 1)
        ,Instruction(Code::PUSH, 10)
        ,Instruction(Code::STO, 2)
        ,Instruction(Code::RCL, 0)
        ,Instruction(Code::RCL, 1)
        ,Instruction(Code::DUP, 0)
        ,Instruction(Code::STO, 0)
        ,Instruction(Code::ADD, 0)
        ,Instruction(Code::DUP, 0)
        ,Instruction(Code::STO, 1)
        ,Instruction(Code::PRN, 0)
        ,Instruction(Code::RCL, 2)
        ,Instruction(Code::PUSH, 1)
        ,Instruction(Code::SUB, 0)
        ,Instruction(Code::DUP, 0)
        ,Instruction(Code::STO, 2)
        ,Instruction(Code::PUSH, 0)
        ,Instruction(Code::EQ, 0)
        ,Instruction(Code::JIF, 6)
        ,Instruction(Code::END, 0)
    };
    Machine m (prog);
    m.execute();
}

void test_simple_operation() {
    printf("\nTEST CASE [SIMPLE_OPERATION] \n");
    
    Instruction prog[] = {
        Instruction(Code::PUSH, 10)
        ,Instruction(Code::PUSH, 4)
        ,Instruction(Code::ADD, 0)
        ,Instruction(Code::PUSH, 3)
        ,Instruction(Code::MUL, 0)
        ,Instruction(Code::PRN, 0)
        ,Instruction(Code::END, 0)
    };
    Machine m (prog);
    m.execute();
}

int main() {
    test_fibonnaci();
    test_simple_operation();
    return 0;
}