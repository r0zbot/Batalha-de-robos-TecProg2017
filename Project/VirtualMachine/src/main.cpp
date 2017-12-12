// Move this file to /VirtualMachine/src so this can work on production

#include <vector>

#include <controller/classes/action.h>
#include <controller/classes/code.h>
#include <controller/classes/number.h>
#include <controller/classes/instruction.h>

#include <controller/classes/core.h>

#include <util/config.h>
#include <util/globals.h>

using namespace std;

int main() {
    //Settings
    Config::machine_health = 100;
    Config::machine_instructions_cycle = 50;
    Config::machine_melee_attack = 20;
    Config::machine_fuel = 100;
    Config::max_crystals_per_cell = 20;
    Config::machine_inst_fuel_usage = 0.01;
    Config::available_crystals = 120;
    Config::machine_mov_fuel_usage = 1.5;

	const vector<vector<int>> terrain {
		{2, 4, 1, 2, 3, 0, 3, 2, 3, 4, 2, 1, 0, 2, 4, 1, 0, 4, 2, 3}, 
		{0, 0, 3, 0, 4, 0, 3, 3, 0, 2, 0, 2, 2, 0, 0, 3, 1, 4, 0, 3}, 
		{4, 0, 2, 4, 1, 3, 0, 4, 2, 4, 4, 4, 3, 1, 2, 0, 2, 1, 3, 3}, 
		{0, 1, 0, 2, 0, 0, 4, 4, 1, 1, 4, 3, 3, 0, 4, 2, 3, 0, 4, 1}, 
		{4, 1, 4, 0, 3, 0, 2, 3, 0, 3, 1, 4, 2, 3, 0, 0, 1, 1, 3, 2}, 
		{4, 4, 0, 1, 4, 0, 4, 3, 2, 1, 4, 1, 0, 3, 2, 4, 0, 1, 0, 3}, 
		{1, 4, 2, 2, 2, 1, 1, 4, 2, 3, 4, 1, 3, 4, 0, 3, 3, 4, 2, 0}, 
		{0, 2, 2, 2, 1, 1, 2, 2, 3, 3, 2, 0, 3, 3, 4, 4, 0, 1, 0, 0}, 
		{4, 1, 2, 0, 3, 2, 0, 0, 1, 4, 0, 2, 0, 4, 4, 1, 4, 2, 3, 4}, 
		{2, 1, 2, 2, 3, 4, 4, 1, 1, 3, 1, 0, 4, 0, 2, 2, 1, 3, 0, 0}, 
	};

    arena.import_terrain(terrain);

    Army army1("Army 1");
    arena.insert_army(army1);
    const vector<Instruction> prog1 ({
         Instruction(Code::MATR,make_shared<Number>(1))
         ,Instruction(Code::STO,make_shared<Number>(0))
         ,Instruction(Code::PUSH,make_shared<Number>(1))
         ,Instruction(Code::JIF,make_shared<Number>(329))
         ,Instruction(Code::SYS,make_shared<Action>(SystemCode::SEE, Direction::EA))
         ,Instruction(Code::STO,make_shared<Number>(1))
         ,Instruction(Code::RCL,make_shared<Number>(1))
         ,Instruction(Code::ATR,make_shared<Number>(0))
         ,Instruction(Code::PUSH,make_shared<Number>(3))
         ,Instruction(Code::NE,make_shared<Number>(0))
         ,Instruction(Code::DUP,make_shared<Number>(0))
         ,Instruction(Code::JIF,make_shared<Number>(57))
         ,Instruction(Code::RCL,make_shared<Number>(1))
         ,Instruction(Code::ATR,make_shared<Number>(2))
         ,Instruction(Code::PUSH,make_shared<Number>(1))
         ,Instruction(Code::PUSH,make_shared<Number>(-1))
         ,Instruction(Code::MUL,make_shared<Number>(0))
         ,Instruction(Code::EQ,make_shared<Number>(0))
         ,Instruction(Code::DUP,make_shared<Number>(0))
         ,Instruction(Code::JIF,make_shared<Number>(46))
         ,Instruction(Code::RCL,make_shared<Number>(1))
         ,Instruction(Code::ATR,make_shared<Number>(3))
         ,Instruction(Code::PUSH,make_shared<Number>(1))
         ,Instruction(Code::PUSH,make_shared<Number>(-1))
         ,Instruction(Code::MUL,make_shared<Number>(0))
         ,Instruction(Code::EQ,make_shared<Number>(0))
         ,Instruction(Code::DUP,make_shared<Number>(0))
         ,Instruction(Code::JIF,make_shared<Number>(30))
         ,Instruction(Code::SYS,make_shared<Action>(SystemCode::MOVE, Direction::EA))
         ,Instruction(Code::PUSH,make_shared<Number>(1))
         ,Instruction(Code::NOP,make_shared<Number>(0))
         ,Instruction(Code::JIT,make_shared<Number>(44))
         ,Instruction(Code::RCL,make_shared<Number>(1))
         ,Instruction(Code::ATR,make_shared<Number>(3))
         ,Instruction(Code::RCL,make_shared<Number>(0))
         ,Instruction(Code::EQ,make_shared<Number>(0))
         ,Instruction(Code::DUP,make_shared<Number>(0))
         ,Instruction(Code::JIF,make_shared<Number>(40))
         ,Instruction(Code::SYS,make_shared<Action>(SystemCode::DROP, Direction::EA))
         ,Instruction(Code::PUSH,make_shared<Number>(1))
         ,Instruction(Code::NOP,make_shared<Number>(0))
         ,Instruction(Code::JIT,make_shared<Number>(43))
         ,Instruction(Code::SYS,make_shared<Action>(SystemCode::COLLECT, Direction::EA))
         ,Instruction(Code::NOP,make_shared<Number>(0))
         ,Instruction(Code::NOP,make_shared<Number>(0))
         ,Instruction(Code::PUSH,make_shared<Number>(1))
         ,Instruction(Code::NOP,make_shared<Number>(0))
         ,Instruction(Code::JIT,make_shared<Number>(56))
         ,Instruction(Code::RCL,make_shared<Number>(1))
         ,Instruction(Code::ATR,make_shared<Number>(2))
         ,Instruction(Code::RCL,make_shared<Number>(0))
         ,Instruction(Code::NE,make_shared<Number>(0))
         ,Instruction(Code::DUP,make_shared<Number>(0))
         ,Instruction(Code::JIF,make_shared<Number>(55))
         ,Instruction(Code::SYS,make_shared<Action>(SystemCode::ATKMELEE, Direction::EA))
         ,Instruction(Code::NOP,make_shared<Number>(0))
         ,Instruction(Code::NOP,make_shared<Number>(0))
         ,Instruction(Code::NOP,make_shared<Number>(0))
         ,Instruction(Code::SYS,make_shared<Action>(SystemCode::SEE, Direction::SE))
         ,Instruction(Code::STO,make_shared<Number>(1))
         ,Instruction(Code::RCL,make_shared<Number>(1))
         ,Instruction(Code::ATR,make_shared<Number>(0))
         ,Instruction(Code::PUSH,make_shared<Number>(3))
         ,Instruction(Code::NE,make_shared<Number>(0))
         ,Instruction(Code::DUP,make_shared<Number>(0))
         ,Instruction(Code::JIF,make_shared<Number>(111))
         ,Instruction(Code::RCL,make_shared<Number>(1))
         ,Instruction(Code::ATR,make_shared<Number>(2))
         ,Instruction(Code::PUSH,make_shared<Number>(1))
         ,Instruction(Code::PUSH,make_shared<Number>(-1))
         ,Instruction(Code::MUL,make_shared<Number>(0))
         ,Instruction(Code::EQ,make_shared<Number>(0))
         ,Instruction(Code::DUP,make_shared<Number>(0))
         ,Instruction(Code::JIF,make_shared<Number>(100))
         ,Instruction(Code::RCL,make_shared<Number>(1))
         ,Instruction(Code::ATR,make_shared<Number>(3))
         ,Instruction(Code::PUSH,make_shared<Number>(1))
         ,Instruction(Code::PUSH,make_shared<Number>(-1))
         ,Instruction(Code::MUL,make_shared<Number>(0))
         ,Instruction(Code::EQ,make_shared<Number>(0))
         ,Instruction(Code::DUP,make_shared<Number>(0))
         ,Instruction(Code::JIF,make_shared<Number>(84))
         ,Instruction(Code::SYS,make_shared<Action>(SystemCode::MOVE, Direction::SE))
         ,Instruction(Code::PUSH,make_shared<Number>(1))
         ,Instruction(Code::NOP,make_shared<Number>(0))
         ,Instruction(Code::JIT,make_shared<Number>(98))
         ,Instruction(Code::RCL,make_shared<Number>(1))
         ,Instruction(Code::ATR,make_shared<Number>(3))
         ,Instruction(Code::RCL,make_shared<Number>(0))
         ,Instruction(Code::EQ,make_shared<Number>(0))
         ,Instruction(Code::DUP,make_shared<Number>(0))
         ,Instruction(Code::JIF,make_shared<Number>(94))
         ,Instruction(Code::SYS,make_shared<Action>(SystemCode::DROP, Direction::SE))
         ,Instruction(Code::PUSH,make_shared<Number>(1))
         ,Instruction(Code::NOP,make_shared<Number>(0))
         ,Instruction(Code::JIT,make_shared<Number>(97))
         ,Instruction(Code::SYS,make_shared<Action>(SystemCode::COLLECT, Direction::SE))
         ,Instruction(Code::NOP,make_shared<Number>(0))
         ,Instruction(Code::NOP,make_shared<Number>(0))
         ,Instruction(Code::PUSH,make_shared<Number>(1))
         ,Instruction(Code::NOP,make_shared<Number>(0))
         ,Instruction(Code::JIT,make_shared<Number>(110))
         ,Instruction(Code::RCL,make_shared<Number>(1))
         ,Instruction(Code::ATR,make_shared<Number>(2))
         ,Instruction(Code::RCL,make_shared<Number>(0))
         ,Instruction(Code::NE,make_shared<Number>(0))
         ,Instruction(Code::DUP,make_shared<Number>(0))
         ,Instruction(Code::JIF,make_shared<Number>(109))
         ,Instruction(Code::SYS,make_shared<Action>(SystemCode::ATKMELEE, Direction::SE))
         ,Instruction(Code::NOP,make_shared<Number>(0))
         ,Instruction(Code::NOP,make_shared<Number>(0))
         ,Instruction(Code::NOP,make_shared<Number>(0))
         ,Instruction(Code::SYS,make_shared<Action>(SystemCode::SEE, Direction::SW))
         ,Instruction(Code::STO,make_shared<Number>(1))
         ,Instruction(Code::RCL,make_shared<Number>(1))
         ,Instruction(Code::ATR,make_shared<Number>(0))
         ,Instruction(Code::PUSH,make_shared<Number>(3))
         ,Instruction(Code::NE,make_shared<Number>(0))
         ,Instruction(Code::DUP,make_shared<Number>(0))
         ,Instruction(Code::JIF,make_shared<Number>(165))
         ,Instruction(Code::RCL,make_shared<Number>(1))
         ,Instruction(Code::ATR,make_shared<Number>(2))
         ,Instruction(Code::PUSH,make_shared<Number>(1))
         ,Instruction(Code::PUSH,make_shared<Number>(-1))
         ,Instruction(Code::MUL,make_shared<Number>(0))
         ,Instruction(Code::EQ,make_shared<Number>(0))
         ,Instruction(Code::DUP,make_shared<Number>(0))
         ,Instruction(Code::JIF,make_shared<Number>(154))
         ,Instruction(Code::RCL,make_shared<Number>(1))
         ,Instruction(Code::ATR,make_shared<Number>(3))
         ,Instruction(Code::PUSH,make_shared<Number>(1))
         ,Instruction(Code::PUSH,make_shared<Number>(-1))
         ,Instruction(Code::MUL,make_shared<Number>(0))
         ,Instruction(Code::EQ,make_shared<Number>(0))
         ,Instruction(Code::DUP,make_shared<Number>(0))
         ,Instruction(Code::JIF,make_shared<Number>(138))
         ,Instruction(Code::SYS,make_shared<Action>(SystemCode::MOVE, Direction::SW))
         ,Instruction(Code::PUSH,make_shared<Number>(1))
         ,Instruction(Code::NOP,make_shared<Number>(0))
         ,Instruction(Code::JIT,make_shared<Number>(152))
         ,Instruction(Code::RCL,make_shared<Number>(1))
         ,Instruction(Code::ATR,make_shared<Number>(3))
         ,Instruction(Code::RCL,make_shared<Number>(0))
         ,Instruction(Code::EQ,make_shared<Number>(0))
         ,Instruction(Code::DUP,make_shared<Number>(0))
         ,Instruction(Code::JIF,make_shared<Number>(148))
         ,Instruction(Code::SYS,make_shared<Action>(SystemCode::DROP, Direction::SW))
         ,Instruction(Code::PUSH,make_shared<Number>(1))
         ,Instruction(Code::NOP,make_shared<Number>(0))
         ,Instruction(Code::JIT,make_shared<Number>(151))
         ,Instruction(Code::SYS,make_shared<Action>(SystemCode::COLLECT, Direction::SW))
         ,Instruction(Code::NOP,make_shared<Number>(0))
         ,Instruction(Code::NOP,make_shared<Number>(0))
         ,Instruction(Code::PUSH,make_shared<Number>(1))
         ,Instruction(Code::NOP,make_shared<Number>(0))
         ,Instruction(Code::JIT,make_shared<Number>(164))
         ,Instruction(Code::RCL,make_shared<Number>(1))
         ,Instruction(Code::ATR,make_shared<Number>(2))
         ,Instruction(Code::RCL,make_shared<Number>(0))
         ,Instruction(Code::NE,make_shared<Number>(0))
         ,Instruction(Code::DUP,make_shared<Number>(0))
         ,Instruction(Code::JIF,make_shared<Number>(163))
         ,Instruction(Code::SYS,make_shared<Action>(SystemCode::ATKMELEE, Direction::SW))
         ,Instruction(Code::NOP,make_shared<Number>(0))
         ,Instruction(Code::NOP,make_shared<Number>(0))
         ,Instruction(Code::NOP,make_shared<Number>(0))
         ,Instruction(Code::SYS,make_shared<Action>(SystemCode::SEE, Direction::WE))
         ,Instruction(Code::STO,make_shared<Number>(1))
         ,Instruction(Code::RCL,make_shared<Number>(1))
         ,Instruction(Code::ATR,make_shared<Number>(0))
         ,Instruction(Code::PUSH,make_shared<Number>(3))
         ,Instruction(Code::NE,make_shared<Number>(0))
         ,Instruction(Code::DUP,make_shared<Number>(0))
         ,Instruction(Code::JIF,make_shared<Number>(219))
         ,Instruction(Code::RCL,make_shared<Number>(1))
         ,Instruction(Code::ATR,make_shared<Number>(2))
         ,Instruction(Code::PUSH,make_shared<Number>(1))
         ,Instruction(Code::PUSH,make_shared<Number>(-1))
         ,Instruction(Code::MUL,make_shared<Number>(0))
         ,Instruction(Code::EQ,make_shared<Number>(0))
         ,Instruction(Code::DUP,make_shared<Number>(0))
         ,Instruction(Code::JIF,make_shared<Number>(208))
         ,Instruction(Code::RCL,make_shared<Number>(1))
         ,Instruction(Code::ATR,make_shared<Number>(3))
         ,Instruction(Code::PUSH,make_shared<Number>(1))
         ,Instruction(Code::PUSH,make_shared<Number>(-1))
         ,Instruction(Code::MUL,make_shared<Number>(0))
         ,Instruction(Code::EQ,make_shared<Number>(0))
         ,Instruction(Code::DUP,make_shared<Number>(0))
         ,Instruction(Code::JIF,make_shared<Number>(192))
         ,Instruction(Code::SYS,make_shared<Action>(SystemCode::MOVE, Direction::WE))
         ,Instruction(Code::PUSH,make_shared<Number>(1))
         ,Instruction(Code::NOP,make_shared<Number>(0))
         ,Instruction(Code::JIT,make_shared<Number>(206))
         ,Instruction(Code::RCL,make_shared<Number>(1))
         ,Instruction(Code::ATR,make_shared<Number>(3))
         ,Instruction(Code::RCL,make_shared<Number>(0))
         ,Instruction(Code::EQ,make_shared<Number>(0))
         ,Instruction(Code::DUP,make_shared<Number>(0))
         ,Instruction(Code::JIF,make_shared<Number>(202))
         ,Instruction(Code::SYS,make_shared<Action>(SystemCode::DROP, Direction::WE))
         ,Instruction(Code::PUSH,make_shared<Number>(1))
         ,Instruction(Code::NOP,make_shared<Number>(0))
         ,Instruction(Code::JIT,make_shared<Number>(205))
         ,Instruction(Code::SYS,make_shared<Action>(SystemCode::COLLECT, Direction::WE))
         ,Instruction(Code::NOP,make_shared<Number>(0))
         ,Instruction(Code::NOP,make_shared<Number>(0))
         ,Instruction(Code::PUSH,make_shared<Number>(1))
         ,Instruction(Code::NOP,make_shared<Number>(0))
         ,Instruction(Code::JIT,make_shared<Number>(218))
         ,Instruction(Code::RCL,make_shared<Number>(1))
         ,Instruction(Code::ATR,make_shared<Number>(2))
         ,Instruction(Code::RCL,make_shared<Number>(0))
         ,Instruction(Code::NE,make_shared<Number>(0))
         ,Instruction(Code::DUP,make_shared<Number>(0))
         ,Instruction(Code::JIF,make_shared<Number>(217))
         ,Instruction(Code::SYS,make_shared<Action>(SystemCode::ATKMELEE, Direction::WE))
         ,Instruction(Code::NOP,make_shared<Number>(0))
         ,Instruction(Code::NOP,make_shared<Number>(0))
         ,Instruction(Code::NOP,make_shared<Number>(0))
         ,Instruction(Code::SYS,make_shared<Action>(SystemCode::SEE, Direction::NW))
         ,Instruction(Code::STO,make_shared<Number>(1))
         ,Instruction(Code::RCL,make_shared<Number>(1))
         ,Instruction(Code::ATR,make_shared<Number>(0))
         ,Instruction(Code::PUSH,make_shared<Number>(3))
         ,Instruction(Code::NE,make_shared<Number>(0))
         ,Instruction(Code::DUP,make_shared<Number>(0))
         ,Instruction(Code::JIF,make_shared<Number>(273))
         ,Instruction(Code::RCL,make_shared<Number>(1))
         ,Instruction(Code::ATR,make_shared<Number>(2))
         ,Instruction(Code::PUSH,make_shared<Number>(1))
         ,Instruction(Code::PUSH,make_shared<Number>(-1))
         ,Instruction(Code::MUL,make_shared<Number>(0))
         ,Instruction(Code::EQ,make_shared<Number>(0))
         ,Instruction(Code::DUP,make_shared<Number>(0))
         ,Instruction(Code::JIF,make_shared<Number>(262))
         ,Instruction(Code::RCL,make_shared<Number>(1))
         ,Instruction(Code::ATR,make_shared<Number>(3))
         ,Instruction(Code::PUSH,make_shared<Number>(1))
         ,Instruction(Code::PUSH,make_shared<Number>(-1))
         ,Instruction(Code::MUL,make_shared<Number>(0))
         ,Instruction(Code::EQ,make_shared<Number>(0))
         ,Instruction(Code::DUP,make_shared<Number>(0))
         ,Instruction(Code::JIF,make_shared<Number>(246))
         ,Instruction(Code::SYS,make_shared<Action>(SystemCode::MOVE, Direction::NW))
         ,Instruction(Code::PUSH,make_shared<Number>(1))
         ,Instruction(Code::NOP,make_shared<Number>(0))
         ,Instruction(Code::JIT,make_shared<Number>(260))
         ,Instruction(Code::RCL,make_shared<Number>(1))
         ,Instruction(Code::ATR,make_shared<Number>(3))
         ,Instruction(Code::RCL,make_shared<Number>(0))
         ,Instruction(Code::EQ,make_shared<Number>(0))
         ,Instruction(Code::DUP,make_shared<Number>(0))
         ,Instruction(Code::JIF,make_shared<Number>(256))
         ,Instruction(Code::SYS,make_shared<Action>(SystemCode::DROP, Direction::NW))
         ,Instruction(Code::PUSH,make_shared<Number>(1))
         ,Instruction(Code::NOP,make_shared<Number>(0))
         ,Instruction(Code::JIT,make_shared<Number>(259))
         ,Instruction(Code::SYS,make_shared<Action>(SystemCode::COLLECT, Direction::NW))
         ,Instruction(Code::NOP,make_shared<Number>(0))
         ,Instruction(Code::NOP,make_shared<Number>(0))
         ,Instruction(Code::PUSH,make_shared<Number>(1))
         ,Instruction(Code::NOP,make_shared<Number>(0))
         ,Instruction(Code::JIT,make_shared<Number>(272))
         ,Instruction(Code::RCL,make_shared<Number>(1))
         ,Instruction(Code::ATR,make_shared<Number>(2))
         ,Instruction(Code::RCL,make_shared<Number>(0))
         ,Instruction(Code::NE,make_shared<Number>(0))
         ,Instruction(Code::DUP,make_shared<Number>(0))
         ,Instruction(Code::JIF,make_shared<Number>(271))
         ,Instruction(Code::SYS,make_shared<Action>(SystemCode::ATKMELEE, Direction::NW))
         ,Instruction(Code::NOP,make_shared<Number>(0))
         ,Instruction(Code::NOP,make_shared<Number>(0))
         ,Instruction(Code::NOP,make_shared<Number>(0))
         ,Instruction(Code::SYS,make_shared<Action>(SystemCode::SEE, Direction::NE))
         ,Instruction(Code::STO,make_shared<Number>(1))
         ,Instruction(Code::RCL,make_shared<Number>(1))
         ,Instruction(Code::ATR,make_shared<Number>(0))
         ,Instruction(Code::PUSH,make_shared<Number>(3))
         ,Instruction(Code::NE,make_shared<Number>(0))
         ,Instruction(Code::DUP,make_shared<Number>(0))
         ,Instruction(Code::JIF,make_shared<Number>(327))
         ,Instruction(Code::RCL,make_shared<Number>(1))
         ,Instruction(Code::ATR,make_shared<Number>(2))
         ,Instruction(Code::PUSH,make_shared<Number>(1))
         ,Instruction(Code::PUSH,make_shared<Number>(-1))
         ,Instruction(Code::MUL,make_shared<Number>(0))
         ,Instruction(Code::EQ,make_shared<Number>(0))
         ,Instruction(Code::DUP,make_shared<Number>(0))
         ,Instruction(Code::JIF,make_shared<Number>(316))
         ,Instruction(Code::RCL,make_shared<Number>(1))
         ,Instruction(Code::ATR,make_shared<Number>(3))
         ,Instruction(Code::PUSH,make_shared<Number>(1))
         ,Instruction(Code::PUSH,make_shared<Number>(-1))
         ,Instruction(Code::MUL,make_shared<Number>(0))
         ,Instruction(Code::EQ,make_shared<Number>(0))
         ,Instruction(Code::DUP,make_shared<Number>(0))
         ,Instruction(Code::JIF,make_shared<Number>(300))
         ,Instruction(Code::SYS,make_shared<Action>(SystemCode::MOVE, Direction::NE))
         ,Instruction(Code::PUSH,make_shared<Number>(1))
         ,Instruction(Code::NOP,make_shared<Number>(0))
         ,Instruction(Code::JIT,make_shared<Number>(314))
         ,Instruction(Code::RCL,make_shared<Number>(1))
         ,Instruction(Code::ATR,make_shared<Number>(3))
         ,Instruction(Code::RCL,make_shared<Number>(0))
         ,Instruction(Code::EQ,make_shared<Number>(0))
         ,Instruction(Code::DUP,make_shared<Number>(0))
         ,Instruction(Code::JIF,make_shared<Number>(310))
         ,Instruction(Code::SYS,make_shared<Action>(SystemCode::DROP, Direction::NE))
         ,Instruction(Code::PUSH,make_shared<Number>(1))
         ,Instruction(Code::NOP,make_shared<Number>(0))
         ,Instruction(Code::JIT,make_shared<Number>(313))
         ,Instruction(Code::SYS,make_shared<Action>(SystemCode::COLLECT, Direction::NE))
         ,Instruction(Code::NOP,make_shared<Number>(0))
         ,Instruction(Code::NOP,make_shared<Number>(0))
         ,Instruction(Code::PUSH,make_shared<Number>(1))
         ,Instruction(Code::NOP,make_shared<Number>(0))
         ,Instruction(Code::JIT,make_shared<Number>(326))
         ,Instruction(Code::RCL,make_shared<Number>(1))
         ,Instruction(Code::ATR,make_shared<Number>(2))
         ,Instruction(Code::RCL,make_shared<Number>(0))
         ,Instruction(Code::NE,make_shared<Number>(0))
         ,Instruction(Code::DUP,make_shared<Number>(0))
         ,Instruction(Code::JIF,make_shared<Number>(325))
         ,Instruction(Code::SYS,make_shared<Action>(SystemCode::ATKMELEE, Direction::NE))
         ,Instruction(Code::NOP,make_shared<Number>(0))
         ,Instruction(Code::NOP,make_shared<Number>(0))
         ,Instruction(Code::NOP,make_shared<Number>(0))
         ,Instruction(Code::JMP,make_shared<Number>(2))
         ,Instruction(Code::NOP,make_shared<Number>(0))
         ,Instruction(Code::END,make_shared<Number>(0))
     });

    for(int i=0; i<1; i++)
        arena.create_robot(army1.get_id(), prog1);

    Army army2("Army 2");
    arena.insert_army(army2);
    const vector<Instruction> prog2 ({
         Instruction(Code::PUSH,make_shared<Number>(1))
         ,Instruction(Code::JIF,make_shared<Number>(33))
         ,Instruction(Code::SYS,make_shared<Action>(SystemCode::MOVE, Direction::WE))
         ,Instruction(Code::JIF,make_shared<Number>(6))
         ,Instruction(Code::SYS,make_shared<Action>(SystemCode::COLLECT, Direction::NW))
         ,Instruction(Code::JMP,make_shared<Number>(2))
         ,Instruction(Code::NOP,make_shared<Number>(0))
         ,Instruction(Code::SYS,make_shared<Action>(SystemCode::MOVE, Direction::NW))
         ,Instruction(Code::JIF,make_shared<Number>(11))
         ,Instruction(Code::SYS,make_shared<Action>(SystemCode::COLLECT, Direction::NE))
         ,Instruction(Code::JMP,make_shared<Number>(7))
         ,Instruction(Code::NOP,make_shared<Number>(0))
         ,Instruction(Code::SYS,make_shared<Action>(SystemCode::MOVE, Direction::NE))
         ,Instruction(Code::JIF,make_shared<Number>(16))
         ,Instruction(Code::SYS,make_shared<Action>(SystemCode::COLLECT, Direction::EA))
         ,Instruction(Code::JMP,make_shared<Number>(12))
         ,Instruction(Code::NOP,make_shared<Number>(0))
         ,Instruction(Code::SYS,make_shared<Action>(SystemCode::MOVE, Direction::EA))
         ,Instruction(Code::JIF,make_shared<Number>(21))
         ,Instruction(Code::SYS,make_shared<Action>(SystemCode::COLLECT, Direction::SE))
         ,Instruction(Code::JMP,make_shared<Number>(17))
         ,Instruction(Code::NOP,make_shared<Number>(0))
         ,Instruction(Code::SYS,make_shared<Action>(SystemCode::MOVE, Direction::SE))
         ,Instruction(Code::JIF,make_shared<Number>(26))
         ,Instruction(Code::SYS,make_shared<Action>(SystemCode::COLLECT, Direction::SW))
         ,Instruction(Code::JMP,make_shared<Number>(22))
         ,Instruction(Code::NOP,make_shared<Number>(0))
         ,Instruction(Code::SYS,make_shared<Action>(SystemCode::MOVE, Direction::SW))
         ,Instruction(Code::JIF,make_shared<Number>(31))
         ,Instruction(Code::SYS,make_shared<Action>(SystemCode::COLLECT, Direction::WE))
         ,Instruction(Code::JMP,make_shared<Number>(27))
         ,Instruction(Code::NOP,make_shared<Number>(0))
         ,Instruction(Code::JMP,make_shared<Number>(0))
         ,Instruction(Code::NOP,make_shared<Number>(0))
         ,Instruction(Code::END,make_shared<Number>(0))
     });

    for(int i=0; i<1; i++)
        arena.create_robot(army2.get_id(), prog2);

    Core core(arena, 1000);
    core.start();
}