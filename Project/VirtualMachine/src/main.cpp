// Move this file to /VirtualMachine/src so this can work on production

#include <vector>

#include <controller/classes/code.h>
#include <controller/classes/instruction.h>
#include <model/entity/machine.h>
#include <util/globals.h>
#include <controller/classes/number.h>

using namespace std;

int main() {

    vector<Instruction> prog2 ({
       Instruction(Code::PUSH, new Number(8))
       ,Instruction(Code::CALL, new Number(4))
       ,Instruction(Code::PRN, new Number(0))
       ,Instruction(Code::END, new Number(0))
       ,Instruction(Code::ALC, new Number(1))
       ,Instruction(Code::DUP, new Number(0))
       ,Instruction(Code::STL, new Number(1))
       ,Instruction(Code::PUSH, new Number(1))
       ,Instruction(Code::EQ, new Number(0))
       ,Instruction(Code::JIF, new Number(13))
       ,Instruction(Code::PUSH, new Number(1))
       ,Instruction(Code::FRE, new Number(1))
       ,Instruction(Code::RET, new Number(0))
       ,Instruction(Code::RCE, new Number(1))
       ,Instruction(Code::PUSH, new Number(1))
       ,Instruction(Code::SUB, new Number(0))
       ,Instruction(Code::CALL, new Number(4))
       ,Instruction(Code::RCE, new Number(1))
       ,Instruction(Code::MUL, new Number(0))
       ,Instruction(Code::FRE, new Number(1))
       ,Instruction(Code::RET, new Number(0))
    });

    //Alternative syntaxm, also valid.
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

    vector<Instruction> prog3 ({
      Instruction(Code::PUSH, 8)
      ,Instruction(Code::CALL, new Hex(0,5))
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
//    vector<Instruction> fighterDumb ({
//        Instruction(Code::SEE, 1)
//        ,Instruction(Code::ATR, 2)
//        ,Instruction(Code::EQ, 1) //considerando que 1 representa a existencia de um robo naquele lugar
//        ,Instruction(Code::JIF, 5)
//        ,Instruction(Code::PUSH, 1)
//        ,Instruction(Code::SYS, 4)
//        ,Instruction(Code::SEE, 2)
//        ,Instruction(Code::ATR, 2)
//        ,Instruction(Code::EQ, 1)
//        ,Instruction(Code::JIF, 11)
//        ,Instruction(Code::PUSH, 2)
//        ,Instruction(Code::SYS, 4)
//        ,Instruction(Code::SEE, 3)
//        ,Instruction(Code::ATR, 2)
//        ,Instruction(Code::EQ, 1)
//        ,Instruction(Code::JIF, 17)
//        ,Instruction(Code::PUSH, 3)
//        ,Instruction(Code::SYS, 4)
//        ,Instruction(Code::SEE, 4)
//        ,Instruction(Code::ATR, 2)
//        ,Instruction(Code::EQ, 1)
//        ,Instruction(Code::JIF, 23)
//        ,Instruction(Code::PUSH, 4)
//        ,Instruction(Code::SYS, 4)
//        ,Instruction(Code::SEE, 5)
//        ,Instruction(Code::ATR, 2)
//        ,Instruction(Code::EQ, 1)
//        ,Instruction(Code::JIF, 29)
//        ,Instruction(Code::PUSH, 5)
//        ,Instruction(Code::SYS, 4)
//        ,Instruction(Code::SEE, 6)
//        ,Instruction(Code::ATR, 2)
//        ,Instruction(Code::EQ, 1)
//        ,Instruction(Code::JIF, 35)
//        ,Instruction(Code::PUSH, 6)
//        ,Instruction(Code::SYS, 4)
//        ,Instruction(Code::END, 0)
//    });
//    vector<Instruction> fighter ({
//        Instruction(Code::PUSH, 1)
//        ,Instruction(Code::SEE, 1)
//        ,Instruction(Code::CALL,19)
//        ,Instruction(Code::PUSH, 2)
//        ,Instruction(Code::SEE, 2)
//        ,Instruction(Code::CALL,19)
//        ,Instruction(Code::PUSH, 3)
//        ,Instruction(Code::SEE, 3)
//        ,Instruction(Code::CALL,19)
//        ,Instruction(Code::PUSH, 4)
//        ,Instruction(Code::SEE, 4)
//        ,Instruction(Code::CALL,19)
//        ,Instruction(Code::PUSH, 5)
//        ,Instruction(Code::SEE, 5)
//        ,Instruction(Code::CALL,19)
//        ,Instruction(Code::PUSH, 6)
//        ,Instruction(Code::SEE, 6)
//        ,Instruction(Code::CALL,19)
//        ,Instruction(Code::END, 0)
//        ,Instruction(Code::ATR, 2)
//        ,Instruction(Code::EQ, 1)
//        ,Instruction(Code::JIF, 23)
//        ,Instruction(Code::SYS, 4)
//        ,Instruction(Code::RET, 0)
//    });
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
    });

    Army army1("USA");
    Army army2("North Korea");
    arena.insert_army(army1);
    arena.insert_army(army2);
    arena.create_robot(arena.get_army(army1.get_id()), Hex(0, 0), prog);
    arena.create_robot(arena.get_army(army2.get_id()), Hex(0, 1), prog2);
    arena.create_robot(arena.get_army(army2.get_id()), Hex(0, 3), prog3);
    //arena.create_robot(arena.get_army(army1.get_id()), Hex(1, 1), estWalker);
    //arena.create_robot(arena.get_army(army2.get_id()), Hex(1, 0), walkAndCollect1);

    //main system loop, eventually will be infinite
    for(int i=0; i<10; i++){
        arena.update();
    }
    return 0;
}
