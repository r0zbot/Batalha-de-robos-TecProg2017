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

    Config::available_crystals         = 120;
    Config::machine_health             = 100;
    Config::machine_fuel               = 100;
    Config::machine_melee_attack       = 20;
    Config::machine_short_attack       = 10;
    Config::machine_long_attack        = 20;
    Config::machine_mov_fuel_usage     = 1.5;
    Config::machine_inst_fuel_usage    = 0.01;
    Config::machine_instructions_cycle = 50;
    Config::max_crystals_per_cell      = 20;

	const vector<vector<int>> terrain {
		{3, 4, 3, 1, 0, 1, 4, 0, 3, 3, 4, 4}, 
		{0, 1, 2, 4, 2, 4, 3, 3, 2, 4, 1, 1}, 
		{2, 2, 0, 1, 1, 1, 1, 2, 4, 0, 0, 3}, 
		{3, 2, 1, 2, 3, 3, 1, 0, 0, 3, 1, 0}, 
		{3, 0, 0, 1, 0, 2, 0, 3, 4, 2, 1, 3}, 
		{2, 4, 0, 2, 2, 0, 4, 3, 0, 4, 2, 1}, 
		{2, 2, 1, 2, 4, 0, 3, 2, 3, 4, 4, 0}, 
		{1, 2, 0, 2, 3, 4, 1, 3, 1, 0, 4, 4}, 
		{0, 3, 3, 3, 0, 3, 1, 3, 3, 2, 1, 4}, 
		{3, 4, 0, 3, 2, 1, 4, 0, 1, 3, 1, 1}, 
		{3, 4, 1, 1, 0, 1, 4, 0, 3, 2, 2, 3}, 
		{0, 0, 2, 1, 3, 4, 3, 0, 4, 2, 3, 0}
	};
	arena.import_terrain(terrain);

	Army army1("Army 1");
    Army army2("Army 2");

	arena.insert_army(army1);
	arena.insert_army(army2);

	const vector<Instruction> prog ({
        Instruction(Code::SYS,  make_shared<Action>(SystemCode::MOVE,    Direction::NE))
        ,Instruction(Code::SYS, make_shared<Action>(SystemCode::COLLECT, Direction::SE))
        ,Instruction(Code::SYS, make_shared<Action>(SystemCode::MOVE,    Direction::SE))
        ,Instruction(Code::SYS, make_shared<Action>(SystemCode::COLLECT, Direction::SE))
        ,Instruction(Code::SYS, make_shared<Action>(SystemCode::MOVE,    Direction::NW))
        ,Instruction(Code::SYS, make_shared<Action>(SystemCode::COLLECT, Direction::NW))
        ,Instruction(Code::JMP, make_shared<Number>(0))
        ,Instruction(Code::END, nullptr)
    });


	for (int i = 0; i < 3; i++) {
        arena.create_robot(army1.get_id(), prog);
        arena.create_robot(army2.get_id(), prog);
    }

	Core core(arena, 1000);
	core.start();
}
