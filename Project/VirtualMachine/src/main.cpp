// Move this file to /VirtualMachine/src so this can work on production

#include <vector>

#include <controller/classes/code.h>
#include <controller/classes/instruction.h>

#include <model/entity/arena.h>

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
    int armyId1 = a.insert_army("Exercito loko");
    a.create_robot(a.get_army(armyId1), 0, 0, prog);
    a.create_robot(a.get_army(armyId1), 0, 1, prog);
    a.create_robot(a.get_army(armyId1), 0, 2, prog);

    int armyId2 = a.insert_army("Exercito bosta");
    a.create_robot(a.get_army(armyId2), 1, 0, prog);
    a.create_robot(a.get_army(armyId2), 1, 1, prog);
    a.create_robot(a.get_army(armyId2), 1, 2, prog);

    a.update();
    return 0;
}
