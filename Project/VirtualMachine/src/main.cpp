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
	Config::machine_mov_fuel_usage = 1;

	const vector<vector<int>> terrain {
		{0, 2, 3, 1, 3, 1, 2, 0, 1, 1, 3, 4, 0, 4, 3, 2, 0, 2, 4, 3}, 
		{1, 1, 0, 3, 3, 0, 0, 2, 4, 3, 0, 1, 0, 2, 1, 0, 4, 1, 2, 2}, 
		{4, 3, 3, 2, 4, 4, 4, 1, 3, 1, 4, 4, 4, 2, 2, 0, 2, 0, 1, 2}, 
		{3, 2, 0, 2, 2, 1, 3, 0, 2, 4, 2, 4, 3, 4, 3, 4, 4, 4, 1, 3}, 
		{2, 4, 3, 1, 3, 2, 0, 2, 4, 0, 2, 0, 2, 1, 0, 0, 0, 3, 3, 0}, 
		{2, 0, 1, 1, 4, 0, 3, 3, 4, 3, 3, 0, 2, 2, 3, 0, 0, 3, 3, 0}, 
		{3, 1, 4, 3, 2, 2, 2, 2, 4, 2, 4, 2, 3, 3, 4, 1, 4, 2, 4, 0}, 
		{0, 2, 2, 4, 1, 4, 2, 1, 3, 4, 3, 3, 1, 1, 0, 3, 1, 0, 3, 0}, 
		{1, 2, 2, 1, 3, 4, 4, 4, 2, 3, 2, 0, 2, 4, 1, 1, 2, 3, 1, 2}, 
		{0, 2, 3, 3, 0, 4, 4, 1, 4, 1, 1, 0, 2, 0, 4, 0, 4, 2, 4, 0}, 
	};

	arena.import_terrain(terrain);

	Army army1("Army 1");
	arena.insert_army(army1);
	const vector<Instruction> prog1 ({
        Instruction(Code::PUSH,make_shared<Number>(8))
        ,Instruction(Code::CALL,make_shared<Number>(4))
        ,Instruction(Code::PRN,make_shared<Number>(0))
        ,Instruction(Code::END,make_shared<Number>(0))
        ,Instruction(Code::ALC,make_shared<Number>(1))
        ,Instruction(Code::DUP,make_shared<Number>(0))
        ,Instruction(Code::STL,make_shared<Number>(1))
        ,Instruction(Code::PUSH,make_shared<Number>(1))
        ,Instruction(Code::EQ,make_shared<Number>(0))
        ,Instruction(Code::JIF,make_shared<Number>(13))
        ,Instruction(Code::PUSH,make_shared<Number>(1))
        ,Instruction(Code::FRE,make_shared<Number>(1))
        ,Instruction(Code::RET,make_shared<Number>(0))
        ,Instruction(Code::RCE,make_shared<Number>(1))
        ,Instruction(Code::PUSH,make_shared<Number>(1))
        ,Instruction(Code::SUB,make_shared<Number>(0))
        ,Instruction(Code::CALL,make_shared<Number>(4))
        ,Instruction(Code::RCE,make_shared<Number>(1))
        ,Instruction(Code::MUL,make_shared<Number>(0))
        ,Instruction(Code::FRE,make_shared<Number>(1))
        ,Instruction(Code::RET,make_shared<Number>(0))
    });

	for(int i=0; i<1; i++)
		arena.create_robot(army1.get_id(), prog1);
	const vector<Instruction> prog2 ({
        Instruction(Code::PUSH,make_shared<Number>(1))
        ,Instruction(Code::DUP,nullptr)
        ,Instruction(Code::STO,make_shared<Number>(0))
        ,Instruction(Code::STO,make_shared<Number>(1))
        ,Instruction(Code::PUSH,make_shared<Number>(10))
        ,Instruction(Code::STO,make_shared<Number>(2))
        ,Instruction(Code::RCL,make_shared<Number>(0))
        ,Instruction(Code::RCL,make_shared<Number>(1))
        ,Instruction(Code::DUP,nullptr)
        ,Instruction(Code::STO,make_shared<Number>(0))
        ,Instruction(Code::ADD,nullptr)
        ,Instruction(Code::DUP,nullptr)
        ,Instruction(Code::STO,make_shared<Number>(1))
        ,Instruction(Code::PRN,nullptr)
        ,Instruction(Code::RCL,make_shared<Number>(2))
        ,Instruction(Code::PUSH,make_shared<Number>(1))
        ,Instruction(Code::SUB,nullptr)
        ,Instruction(Code::DUP,nullptr)
        ,Instruction(Code::STO,make_shared<Number>(2))
        ,Instruction(Code::PUSH,make_shared<Number>(0))
        ,Instruction(Code::EQ,nullptr)
        ,Instruction(Code::JIF,make_shared<Number>(6))
        ,Instruction(Code::END,nullptr)
    });

	for(int i=0; i<1; i++)
		arena.create_robot(army1.get_id(), prog2);
	const vector<Instruction> prog3 ({
        Instruction(Code::SYS,make_shared<Action>(SystemCode::SEE, Direction::EA))
        ,Instruction(Code::ATR,make_shared<Number>(3))
        ,Instruction(Code::PUSH,make_shared<Number>(0))
        ,Instruction(Code::EQ,nullptr)
        ,Instruction(Code::JIT,make_shared<Number>(14))
        ,Instruction(Code::SYS,make_shared<Action>(SystemCode::COLLECT, Direction::NW))
        ,Instruction(Code::SYS,make_shared<Action>(SystemCode::SEE, Direction::SE))
        ,Instruction(Code::ATR,make_shared<Number>(2))
        ,Instruction(Code::PUSH,make_shared<Number>(-1))
        ,Instruction(Code::EQ,nullptr)
        ,Instruction(Code::JIF,make_shared<Number>(12))
        ,Instruction(Code::SYS,make_shared<Action>(SystemCode::MOVE, Direction::SE))
        ,Instruction(Code::SYS,make_shared<Action>(SystemCode::MOVE, Direction::NW))
        ,Instruction(Code::JMP,make_shared<Number>(0))
        ,Instruction(Code::SYS,make_shared<Action>(SystemCode::COLLECT, Direction::NW))
        ,Instruction(Code::SYS,make_shared<Action>(SystemCode::COLLECT, Direction::WE))
        ,Instruction(Code::SYS,make_shared<Action>(SystemCode::COLLECT, Direction::NE))
        ,Instruction(Code::SYS,make_shared<Action>(SystemCode::COLLECT, Direction::SE))
        ,Instruction(Code::SYS,make_shared<Action>(SystemCode::COLLECT, Direction::SW))
        ,Instruction(Code::SYS,make_shared<Action>(SystemCode::DROP, Direction::EA))
        ,Instruction(Code::SYS,make_shared<Action>(SystemCode::ATKMELEE, Direction::WE))
        ,Instruction(Code::JMP,make_shared<Number>(20))
    });

	for(int i=0; i<1; i++)
		arena.create_robot(army1.get_id(), prog3);

	Army army2("Army 2");
	arena.insert_army(army2);

	Core core(100);
	core.start();
}

