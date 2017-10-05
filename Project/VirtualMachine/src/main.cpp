// Move this file to /VirtualMachine/src so this can work on production

#include <vector>

#include "../include/code.h"
#include "../include/instruction.h"
#include "../include/machine.h"

using namespace std;

int main() {

    vector<Instruction> prog ({
        Instruction(Code::PUSH, 10)
        ,Instruction(Code::PUSH, 4)
        ,Instruction(Code::ADD, 0)
        ,Instruction(Code::PUSH, 3)
        ,Instruction(Code::MUL, 0)
        ,Instruction(Code::PRN, 0)
        ,Instruction(Code::END, 0)
    });

    Machine m (prog);
    m.execute();
    return 0;
}
