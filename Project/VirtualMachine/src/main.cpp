#include <vector>

#include <controller/classes/code.h>
#include <controller/classes/action.h>
#include <controller/classes/number.h>
#include <controller/classes/instruction.h>

#include <model/entity/machine.h>
#include <util/globals.h>

using namespace std;

int main() {

    /// Change the prog value so you can test other programs
    int prog = 2;

    vector<Instruction> v;

    if (prog == 0) {
        /// Robot moving and collecting crystals
        v = {
            Instruction(Code::SYS, new Action(SystemCode::MOVE,Direction::NE))
            ,Instruction(Code::SYS, new Action(SystemCode::COLLECT,Direction::N))
            ,Instruction(Code::SYS, new Action(SystemCode::MOVE,Direction::N))
            ,Instruction(Code::SYS, new Action(SystemCode::COLLECT,Direction::SE))
            ,Instruction(Code::SYS, new Action(SystemCode::MOVE,Direction::N))
            ,Instruction(Code::SYS, new Action(SystemCode::COLLECT,Direction::N))
            ,Instruction(Code::JMP, new Number(0))};
    }
    if (prog == 1) {
        /// Robot only moves North
        v = {
                Instruction(Code::SYS, new Action(SystemCode::MOVE,Direction::N))
                ,Instruction(Code::JMP, new Number(0))};
    }
    if (prog == 2) {
        /// Robot moving, collecting and dropping crystals.
        v = {
            Instruction(Code::SYS, new Action(SystemCode::MOVE,Direction::NE))
            ,Instruction(Code::SYS, new Action(SystemCode::COLLECT,Direction::N))
            ,Instruction(Code::SYS, new Action(SystemCode::MOVE,Direction::SW))
            ,Instruction(Code::SYS, new Action(SystemCode::DROP,Direction::SE))
            ,Instruction(Code::SYS, new Action(SystemCode::MOVE,Direction::N))
            ,Instruction(Code::SYS, new Action(SystemCode::COLLECT,Direction::N))
            ,Instruction(Code::JMP, new Number(0))};
    }
    if (prog == 4) {
        /// Factorial function
        v = {
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
            ,Instruction(Code::RET, new Number(0))};
    }

    Army a1 ("Army 1");
    Army a2 ("Army 2");

    arena.insert_army(a1);
    arena.insert_army(a2);

    arena.create_robot(a1.get_id(), Hex(50, 50), v);
    arena.create_robot(a2.get_id(), Hex(40, 50), v);

    /// Main system loop, eventually will be infinite
    for (int i = 0; i < 10; i++) {
        arena.update();
    }
    return 0;
}