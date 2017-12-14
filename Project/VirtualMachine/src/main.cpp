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
	Config::machine_mov_fuel_usage = 0;

	const vector<vector<int>> terrain {
		{0, 3, 3, 2, 2, 1, 1, 4, 0, 1, 4, 4, 0, 2, 3, 3, 1, 3, 1, 2}, 
		{1, 2, 4, 0, 1, 2, 2, 3, 1, 4, 0, 4, 4, 0, 0, 2, 3, 2, 4, 3}, 
		{4, 1, 4, 1, 4, 2, 3, 4, 0, 3, 4, 4, 1, 2, 2, 4, 0, 0, 4, 0}, 
		{1, 2, 0, 1, 3, 2, 3, 3, 1, 3, 2, 4, 2, 3, 1, 0, 0, 2, 0, 2}, 
		{2, 0, 4, 2, 3, 3, 4, 2, 3, 2, 3, 0, 1, 3, 3, 0, 3, 2, 4, 1}, 
		{2, 0, 0, 1, 2, 1, 4, 4, 1, 2, 3, 3, 3, 1, 1, 4, 3, 1, 0, 1}, 
		{3, 2, 0, 3, 4, 0, 4, 1, 3, 4, 4, 0, 0, 0, 3, 0, 0, 2, 4, 1}, 
		{3, 4, 1, 2, 1, 2, 0, 1, 0, 4, 1, 4, 0, 3, 2, 4, 0, 4, 4, 2}, 
		{1, 4, 3, 4, 4, 0, 4, 2, 3, 1, 0, 0, 4, 4, 3, 4, 0, 2, 0, 1}, 
		{2, 1, 4, 3, 1, 3, 1, 1, 2, 0, 0, 2, 1, 0, 3, 0, 3, 2, 3, 3}, 
	};

	arena.import_terrain(terrain);

	Army army1("Army 1");
	arena.insert_army(army1);

	Army army2("Army 2");
	arena.insert_army(army2);

	Army army3("Army 3");
	arena.insert_army(army3);

	Army army4("Army 4");
	arena.insert_army(army4);
	const vector<Instruction> prog1 ({
        Instruction(Code::SYS,make_shared<Action>(SystemCode::SEE, Direction::CE))
        ,Instruction(Code::STO,make_shared<Number>(0))
        ,Instruction(Code::PUSH,make_shared<Number>(0))
        ,Instruction(Code::POP,make_shared<Number>(0))
        ,Instruction(Code::RCL,make_shared<Number>(0))
        ,Instruction(Code::ATR,make_shared<Number>(2))
        ,Instruction(Code::PRN,make_shared<Number>(0))
        ,Instruction(Code::SYS,make_shared<Action>(SystemCode::SEE, Direction::NE))
        ,Instruction(Code::STO,make_shared<Number>(0))
        ,Instruction(Code::PUSH,make_shared<Number>(0))
        ,Instruction(Code::POP,make_shared<Number>(0))
        ,Instruction(Code::RCL,make_shared<Number>(0))
        ,Instruction(Code::ATR,make_shared<Number>(2))
        ,Instruction(Code::PRN,make_shared<Number>(0))
        ,Instruction(Code::END,make_shared<Number>(0))
    });

	for(int i=0; i<1; i++)
		arena.create_robot(army4.get_id(), prog1);


	Core core(100);
	core.start();
}

