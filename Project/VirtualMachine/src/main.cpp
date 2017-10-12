// Move this file to /VirtualMachine/src so this can work on production

#include <vector>

#include <controller/classes/code.h>
#include <controller/classes/instruction.h>

#include <model/entity/arena.h>
#include <concat.hpp>
#include <util/log.h>
#include <util/globals.h>

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

    vector<Instruction> prog2 ({
            Instruction(Code::PUSH, 1),
            Instruction(Code::SYS, 2),
            Instruction(Code::PUSH, 3),
            Instruction(Code::SYS, 1),
            Instruction(Code::END, 0)
                               });

    //Machine m(prog);
    //m.execute();
    int armyId1 = arena.insert_army("Exercito loko");
    arena.create_robot(arena.get_army(armyId1), 0, 0, prog);
    //arena.create_robot(arena.get_army(armyId1), 0, 1, prog);
    //arena.create_robot(arena.get_army(armyId1), 0, 2, prog);

    int armyId2 = arena.insert_army("Exercito bosta");
    arena.create_robot(arena.get_army(armyId2), 1, 0, prog2);
    //arena.create_robot(arena.get_army(armyId2), 1, 1, prog);
    //arena.create_robot(arena.get_army(armyId2), 1, 2, prog);

    arena.update();
    arena.update();
    arena.update();
    arena.update();
    arena.update();
    arena.update();
    arena.update();
    arena.update();
    arena.update();
    arena.update();
    arena.update();
    arena.update();
    arena.update();
    arena.update();
    arena.update();
    arena.update();
    arena.update();
    arena.update();
    arena.update();
    arena.update();
    arena.update();
    arena.update();
    arena.update();
    arena.update();
    arena.update();
    arena.update();
    arena.update();
    arena.update();
    arena.update();
    arena.update();
    arena.update();
    arena.update();
    arena.update();
    arena.update();
    arena.update();
    arena.update();
    arena.update();
    arena.update();
    arena.update();
    arena.update();
    arena.update();
    arena.update();
    arena.update();
    arena.update();
    arena.update();
    arena.update();
    arena.update();
    arena.update();
    arena.update();
    arena.update();
    arena.update();
    arena.update();
    arena.update();
    arena.update();
    arena.update();
    arena.update();
    arena.update();
    arena.update();
    arena.update();
    arena.update();
    arena.update();
    arena.update();
    arena.update();
    arena.update();
    arena.update();
    arena.update();

    Log::debug(concat("Fuel left: ",arena.get_army(armyId1).get_robot(0).get_fuel()));
    return 0;
}
