// Move this file to /VirtualMachine/src so this can work on production

#include <vector>

#include <controller/classes/code.h>
#include <controller/classes/instruction.h>
#include <model/entity/machine.h>
#include <util/globals.h>

using namespace std;

int main() {

    vector<Instruction> prog ({
        Instruction(Code::PUSH, 8)
        ,Instruction(Code::CALL, 4)
        ,Instruction(Code::PRN, 0)
        ,Instruction(Code::END, 0)
        ,Instruction(Code::ALC, 1)
        ,Instruction(Code::DUP, 0)
        ,Instruction(Code::STL, 1)
        ,Instruction(Code::PUSH, 1)
        ,Instruction(Code::EQ, 0)
        ,Instruction(Code::JIF, 13)
        ,Instruction(Code::PUSH, 1)
        ,Instruction(Code::FRE, 1)
        ,Instruction(Code::RET, 0)
        ,Instruction(Code::RCE, 1)
        ,Instruction(Code::PUSH, 1)
        ,Instruction(Code::SUB, 0)
        ,Instruction(Code::CALL, 4)
        ,Instruction(Code::RCE, 1)
        ,Instruction(Code::MUL, 0)
        ,Instruction(Code::FRE, 1)
        ,Instruction(Code::RET, 0)
    });
    vector<Instruction> estWalker ({
        Instruction(Code::PUSH, 3)
        ,Instruction(Code::SYS, 1)
        ,Instruction(Code::JMP, 0)
    });
    vector<Instruction> fighterDumb ({
        Instruction(Code::SEE, 1)
        ,Instruction(Code::ATR, 2)
        ,Instruction(Code::EQ, 1) //considerando que 1 representa a existencia de um robo naquele lugar
        ,Instruction(Code::JIF, 5)
        ,Instruction(Code::PUSH, 1)
        ,Instruction(Code::SYS, 4) 
        ,Instruction(Code::SEE, 2)
        ,Instruction(Code::ATR, 2)
        ,Instruction(Code::EQ, 1)
        ,Instruction(Code::JIF, 11)
        ,Instruction(Code::PUSH, 2)
        ,Instruction(Code::SYS, 4) 
        ,Instruction(Code::SEE, 3)
        ,Instruction(Code::ATR, 2)
        ,Instruction(Code::EQ, 1)
        ,Instruction(Code::JIF, 17)
        ,Instruction(Code::PUSH, 3)
        ,Instruction(Code::SYS, 4) 
        ,Instruction(Code::SEE, 4)
        ,Instruction(Code::ATR, 2)
        ,Instruction(Code::EQ, 1)
        ,Instruction(Code::JIF, 23)
        ,Instruction(Code::PUSH, 4)
        ,Instruction(Code::SYS, 4) 
        ,Instruction(Code::SEE, 5)
        ,Instruction(Code::ATR, 2)
        ,Instruction(Code::EQ, 1)
        ,Instruction(Code::JIF, 29)
        ,Instruction(Code::PUSH, 5)
        ,Instruction(Code::SYS, 4) 
        ,Instruction(Code::SEE, 6)
        ,Instruction(Code::ATR, 2)
        ,Instruction(Code::EQ, 1)
        ,Instruction(Code::JIF, 35)
        ,Instruction(Code::PUSH, 6)
        ,Instruction(Code::SYS, 4)
        ,Instruction(Code::END, 0) 
    })
    vector<Instruction> fighter ({
        Instruction(Code::PUSH, 1)
        ,Instruction(Code::SEE, 1)
        ,Instruction(Code::CALL,19)
        ,Instruction(Code::PUSH, 2)
        ,Instruction(Code::SEE, 2)
        ,Instruction(Code::CALL,19)
        ,Instruction(Code::PUSH, 3)
        ,Instruction(Code::SEE, 3)
        ,Instruction(Code::CALL,19)
        ,Instruction(Code::PUSH, 4)
        ,Instruction(Code::SEE, 4)
        ,Instruction(Code::CALL,19)
        ,Instruction(Code::PUSH, 5)
        ,Instruction(Code::SEE, 5)
        ,Instruction(Code::CALL,19)
        ,Instruction(Code::PUSH, 6)
        ,Instruction(Code::SEE, 6)
        ,Instruction(Code::CALL,19)
        ,Instruction(Code::END, 0)
        ,Instruction(Code::ATR, 2)
        ,Instruction(Code::EQ, 1)
        ,Instruction(Code::JIF, 23)
        ,Instruction(Code::SYS, 4)
        ,Instruction(Code::RET, 0)
    })
    vector<Instruction> walkAndCollect1 ({
        Instruction(Code::PUSH, 1)
        ,Instruction(Code::SYS, 1) // anda para NE
        ,Instruction(Code::PUSH, 2)
        ,Instruction(Code::SYS, 2) // coleta de NO
        ,Instruction(Code::PUSH, 3)
        ,Instruction(Code::DUP, 0)
        ,Instruction(Code::DUP, 0)
        ,Instruction(Code::SYS, 1) // anda para L
        ,Instruction(Code::PUSH, 5)
        ,Instruction(Code::SYS, 2) // coleta de SE
        ,Instruction(Code::SYS, 1) // anda para L
        ,Instruction(Code::SYS, 2) // coleta de L
    })

    //Machine m (prog);
    //m.execute();
    Army army1("PORRA");
    Army army2("CARAI");
    arena.insert_army(army1);
    arena.insert_army(army2);
    arena.create_robot(arena.get_army(army1.get_id()), Hex(0,0), prog);
    arena.create_robot(arena.get_army(army1.get_id()), Hex(0,1), prog);
    arena.update();
    arena.update();
    return 0;
}
