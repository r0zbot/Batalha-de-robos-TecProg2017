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
	Config::available_crystals = 250;
	Config::machine_mov_fuel_usage = 0.5;

	const vector<vector<int>> terrain {
		{2, 0, 1, 2, 2, 0, 0, 4, 3, 3, 1, 0, 3, 1, 2, 0, 0, 2, 1, 0}, 
		{2, 3, 4, 1, 4, 0, 2, 1, 0, 2, 1, 4, 0, 2, 0, 4, 1, 2, 0, 1}, 
		{4, 2, 4, 3, 4, 2, 2, 3, 3, 1, 3, 3, 2, 0, 2, 3, 3, 1, 3, 3}, 
		{3, 3, 4, 3, 3, 4, 4, 4, 2, 2, 1, 3, 2, 0, 3, 2, 1, 0, 3, 4}, 
		{3, 0, 1, 2, 3, 4, 0, 0, 3, 2, 2, 2, 0, 0, 0, 3, 1, 0, 3, 2}, 
		{4, 1, 4, 1, 2, 1, 4, 0, 2, 3, 0, 1, 4, 3, 2, 3, 4, 2, 1, 0}, 
		{3, 2, 0, 4, 0, 2, 4, 2, 4, 2, 2, 1, 1, 1, 2, 2, 4, 1, 2, 3}, 
		{1, 3, 2, 0, 2, 4, 1, 1, 4, 4, 3, 2, 0, 1, 1, 1, 4, 3, 0, 1}, 
		{1, 0, 2, 4, 0, 4, 1, 0, 3, 3, 1, 2, 2, 1, 2, 1, 2, 1, 4, 0}, 
		{4, 4, 2, 4, 2, 2, 3, 2, 0, 1, 3, 1, 3, 1, 3, 4, 0, 1, 2, 3}, 
	};

	arena.import_terrain(terrain);

	Army army1("Army 1");
	arena.insert_army(army1);
	const vector<Instruction> prog1 ({
        Instruction(Code::JMP,make_shared<Number>(28))
        ,Instruction(Code::SYS,make_shared<Action>(SystemCode::MOVE, Direction::WE))
        ,Instruction(Code::PUSH,make_shared<Number>(0))
        ,Instruction(Code::EQ,make_shared<Number>(0))
        ,Instruction(Code::DUP,make_shared<Number>(0))
        ,Instruction(Code::JIF,make_shared<Number>(24))
        ,Instruction(Code::SYS,make_shared<Action>(SystemCode::MOVE, Direction::SW))
        ,Instruction(Code::PUSH,make_shared<Number>(0))
        ,Instruction(Code::EQ,make_shared<Number>(0))
        ,Instruction(Code::DUP,make_shared<Number>(0))
        ,Instruction(Code::JIF,make_shared<Number>(23))
        ,Instruction(Code::SYS,make_shared<Action>(SystemCode::MOVE, Direction::NW))
        ,Instruction(Code::PUSH,make_shared<Number>(0))
        ,Instruction(Code::EQ,make_shared<Number>(0))
        ,Instruction(Code::DUP,make_shared<Number>(0))
        ,Instruction(Code::JIF,make_shared<Number>(22))
        ,Instruction(Code::PUSH,make_shared<Number>(1))
        ,Instruction(Code::PUSH,make_shared<Number>(-1))
        ,Instruction(Code::MUL,make_shared<Number>(0))
        ,Instruction(Code::PRN,make_shared<Number>(0))
        ,Instruction(Code::PUSH,make_shared<Number>(0))
        ,Instruction(Code::RET,make_shared<Number>(0))
        ,Instruction(Code::NOP,make_shared<Number>(0))
        ,Instruction(Code::NOP,make_shared<Number>(0))
        ,Instruction(Code::NOP,make_shared<Number>(0))
        ,Instruction(Code::PUSH,make_shared<Number>(1))
        ,Instruction(Code::RET,make_shared<Number>(0))
        ,Instruction(Code::RET,make_shared<Number>(0))
        ,Instruction(Code::NOP,make_shared<Number>(0))
        ,Instruction(Code::JMP,make_shared<Number>(57))
        ,Instruction(Code::SYS,make_shared<Action>(SystemCode::MOVE, Direction::EA))
        ,Instruction(Code::PUSH,make_shared<Number>(0))
        ,Instruction(Code::EQ,make_shared<Number>(0))
        ,Instruction(Code::DUP,make_shared<Number>(0))
        ,Instruction(Code::JIF,make_shared<Number>(53))
        ,Instruction(Code::SYS,make_shared<Action>(SystemCode::MOVE, Direction::SE))
        ,Instruction(Code::PUSH,make_shared<Number>(0))
        ,Instruction(Code::EQ,make_shared<Number>(0))
        ,Instruction(Code::DUP,make_shared<Number>(0))
        ,Instruction(Code::JIF,make_shared<Number>(52))
        ,Instruction(Code::SYS,make_shared<Action>(SystemCode::MOVE, Direction::NE))
        ,Instruction(Code::PUSH,make_shared<Number>(0))
        ,Instruction(Code::EQ,make_shared<Number>(0))
        ,Instruction(Code::DUP,make_shared<Number>(0))
        ,Instruction(Code::JIF,make_shared<Number>(51))
        ,Instruction(Code::PUSH,make_shared<Number>(1))
        ,Instruction(Code::PUSH,make_shared<Number>(-1))
        ,Instruction(Code::MUL,make_shared<Number>(0))
        ,Instruction(Code::PRN,make_shared<Number>(0))
        ,Instruction(Code::PUSH,make_shared<Number>(0))
        ,Instruction(Code::RET,make_shared<Number>(0))
        ,Instruction(Code::NOP,make_shared<Number>(0))
        ,Instruction(Code::NOP,make_shared<Number>(0))
        ,Instruction(Code::NOP,make_shared<Number>(0))
        ,Instruction(Code::PUSH,make_shared<Number>(1))
        ,Instruction(Code::RET,make_shared<Number>(0))
        ,Instruction(Code::RET,make_shared<Number>(0))
        ,Instruction(Code::NOP,make_shared<Number>(0))
        ,Instruction(Code::JMP,make_shared<Number>(66))
        ,Instruction(Code::SYS,make_shared<Action>(SystemCode::COLLECT, Direction::WE))
        ,Instruction(Code::SYS,make_shared<Action>(SystemCode::COLLECT, Direction::SW))
        ,Instruction(Code::SYS,make_shared<Action>(SystemCode::COLLECT, Direction::NW))
        ,Instruction(Code::SYS,make_shared<Action>(SystemCode::COLLECT, Direction::EA))
        ,Instruction(Code::SYS,make_shared<Action>(SystemCode::COLLECT, Direction::SE))
        ,Instruction(Code::SYS,make_shared<Action>(SystemCode::COLLECT, Direction::NE))
        ,Instruction(Code::RET,make_shared<Number>(0))
        ,Instruction(Code::NOP,make_shared<Number>(0))
        ,Instruction(Code::JMP,make_shared<Number>(81))
        ,Instruction(Code::PUSH,make_shared<Number>(0))
        ,Instruction(Code::STO,make_shared<Number>(1))
        ,Instruction(Code::RCL,make_shared<Number>(1))
        ,Instruction(Code::RCL,make_shared<Number>(0))
        ,Instruction(Code::LT,make_shared<Number>(0))
        ,Instruction(Code::JIF,make_shared<Number>(79))
        ,Instruction(Code::RCL,make_shared<Number>(1))
        ,Instruction(Code::PUSH,make_shared<Number>(1))
        ,Instruction(Code::ADD,make_shared<Number>(0))
        ,Instruction(Code::STO,make_shared<Number>(1))
        ,Instruction(Code::JMP,make_shared<Number>(70))
        ,Instruction(Code::NOP,make_shared<Number>(0))
        ,Instruction(Code::RET,make_shared<Number>(0))
        ,Instruction(Code::NOP,make_shared<Number>(0))
        ,Instruction(Code::PUSH,make_shared<Number>(1))
        ,Instruction(Code::JIF,make_shared<Number>(94))
        ,Instruction(Code::ENTRY,make_shared<Number>(4))
        ,Instruction(Code::CALL,make_shared<Number>(30))
        ,Instruction(Code::JIF,make_shared<Number>(92))
        ,Instruction(Code::ENTRY,make_shared<Number>(4))
        ,Instruction(Code::CALL,make_shared<Number>(59))
        ,Instruction(Code::MATR,make_shared<Number>(4))
        ,Instruction(Code::PRN,make_shared<Number>(0))
        ,Instruction(Code::JMP,make_shared<Number>(84))
        ,Instruction(Code::NOP,make_shared<Number>(0))
        ,Instruction(Code::JMP,make_shared<Number>(82))
        ,Instruction(Code::NOP,make_shared<Number>(0))
        ,Instruction(Code::END,make_shared<Number>(0))
    });

	for(int i=0; i<1; i++)
		arena.create_robot(army1.get_id(), prog1);

	Army army2("Army 2");
	arena.insert_army(army2);

	Core core(200);
	core.start();
}

