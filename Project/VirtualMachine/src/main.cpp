// Move this file to /VirtualMachine/src so this can work on production

#include <vector>

#include <code.h>
#include <instruction.h>
#include <arena.h>

using namespace std;

int main() {

    vector<Instruction> prog ({
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
    });

    Machine m (prog);
    //m.execute();
    Arena a;
    Army exercito1("Exercito loko");
    Army exercito2("Exercito bosta");
    a.insert_army(exercito1);
    a.insert_army(exercito2);
    a.create_machine(exercito1, prog);
    a.create_machine(exercito2, prog);
    a.create_machine(exercito2, prog);
    a.create_machine(exercito2, prog);

    a.update();
    a.update();
    a.update();
    a.update();
    a.update();
    return 0;
}
