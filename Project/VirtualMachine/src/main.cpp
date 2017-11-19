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
		{0, 3, 1, 0, 4, 3, 3, 0, 2, 4, 4, 1, 1, 1, 0, 3, 1, 3, 3, 3},
		{0, 2, 2, 4, 2, 4, 0, 4, 0, 4, 3, 4, 3, 4, 2, 2, 2, 4, 0, 2},
		{2, 0, 2, 2, 1, 4, 0, 1, 3, 1, 1, 4, 1, 1, 1, 2, 4, 1, 3, 4},
		{1, 2, 0, 2, 4, 2, 0, 2, 2, 0, 1, 2, 3, 2, 4, 2, 2, 3, 4, 2},
		{1, 0, 3, 3, 1, 3, 0, 2, 3, 4, 4, 2, 3, 4, 4, 2, 2, 0, 1, 3},
		{2, 4, 0, 0, 0, 1, 0, 0, 1, 0, 4, 0, 4, 4, 3, 2, 0, 4, 0, 1},
		{4, 4, 4, 1, 3, 3, 4, 1, 4, 3, 2, 2, 2, 4, 4, 3, 2, 4, 3, 1},
		{4, 4, 1, 2, 4, 3, 4, 1, 0, 3, 4, 1, 3, 3, 4, 2, 4, 0, 1, 0},
		{1, 4, 0, 2, 1, 0, 3, 3, 1, 1, 4, 1, 1, 4, 3, 1, 1, 2, 4, 1},
		{1, 0, 3, 3, 1, 3, 0, 2, 3, 4, 4, 2, 3, 4, 4, 2, 2, 0, 1, 3}
	};

	arena.import_terrain(terrain);

	Army army1("Army 1");
	arena.insert_army(army1);
	const vector<Instruction> prog1 ({
        Instruction(Code::SYS,make_shared<Action>(SystemCode::MOVE, Direction::NE))
        ,Instruction(Code::SYS,make_shared<Action>(SystemCode::COLLECT, Direction::SE))
        ,Instruction(Code::SYS,make_shared<Action>(SystemCode::MOVE, Direction::SE))
        ,Instruction(Code::SYS,make_shared<Action>(SystemCode::COLLECT, Direction::SE))
        ,Instruction(Code::SYS,make_shared<Action>(SystemCode::MOVE, Direction::NW))
        ,Instruction(Code::SYS,make_shared<Action>(SystemCode::COLLECT, Direction::NW))
        ,Instruction(Code::JMP,make_shared<Number>(0))
        ,Instruction(Code::END,nullptr)
    });

	for(int i=0; i<3; i++)
		arena.create_robot(army1.get_id(), prog1);

	Army army2("Army 2");
	arena.insert_army(army2);
	const vector<Instruction> prog2 ({
        Instruction(Code::SYS,make_shared<Action>(SystemCode::MOVE, Direction::NE))
        ,Instruction(Code::SYS,make_shared<Action>(SystemCode::COLLECT, Direction::SE))
        ,Instruction(Code::SYS,make_shared<Action>(SystemCode::MOVE, Direction::SE))
        ,Instruction(Code::SYS,make_shared<Action>(SystemCode::COLLECT, Direction::SE))
        ,Instruction(Code::SYS,make_shared<Action>(SystemCode::MOVE, Direction::NW))
        ,Instruction(Code::SYS,make_shared<Action>(SystemCode::COLLECT, Direction::NW))
        ,Instruction(Code::JMP,make_shared<Number>(0))
        ,Instruction(Code::END,nullptr)
    });

	for(int i=0; i<3; i++)
		arena.create_robot(army2.get_id(), prog2);

	Army army3("Army 3");
	arena.insert_army(army3);
	const vector<Instruction> prog3 ({
        Instruction(Code::SYS,make_shared<Action>(SystemCode::MOVE, Direction::NE))
        ,Instruction(Code::SYS,make_shared<Action>(SystemCode::COLLECT, Direction::SE))
        ,Instruction(Code::SYS,make_shared<Action>(SystemCode::MOVE, Direction::SE))
        ,Instruction(Code::SYS,make_shared<Action>(SystemCode::COLLECT, Direction::SE))
        ,Instruction(Code::SYS,make_shared<Action>(SystemCode::MOVE, Direction::NW))
        ,Instruction(Code::SYS,make_shared<Action>(SystemCode::COLLECT, Direction::NW))
        ,Instruction(Code::JMP,make_shared<Number>(0))
        ,Instruction(Code::END,nullptr)
    });

	for(int i=0; i<3; i++)
		arena.create_robot(army3.get_id(), prog3);

	Army army4("Army 4");
	arena.insert_army(army4);
	const vector<Instruction> prog4 ({
        Instruction(Code::SYS,make_shared<Action>(SystemCode::MOVE, Direction::NE))
        ,Instruction(Code::SYS,make_shared<Action>(SystemCode::COLLECT, Direction::SE))
        ,Instruction(Code::SYS,make_shared<Action>(SystemCode::MOVE, Direction::SE))
        ,Instruction(Code::SYS,make_shared<Action>(SystemCode::COLLECT, Direction::SE))
        ,Instruction(Code::SYS,make_shared<Action>(SystemCode::MOVE, Direction::NW))
        ,Instruction(Code::SYS,make_shared<Action>(SystemCode::COLLECT, Direction::NW))
        ,Instruction(Code::JMP,make_shared<Number>(0))
        ,Instruction(Code::END,nullptr)
    });

	for(int i=0; i<3; i++)
		arena.create_robot(army4.get_id(), prog4);

	Army army5("Army 5");
	arena.insert_army(army5);
	const vector<Instruction> prog5 ({
        Instruction(Code::SYS,make_shared<Action>(SystemCode::MOVE, Direction::NE))
        ,Instruction(Code::SYS,make_shared<Action>(SystemCode::COLLECT, Direction::SE))
        ,Instruction(Code::SYS,make_shared<Action>(SystemCode::MOVE, Direction::SE))
        ,Instruction(Code::SYS,make_shared<Action>(SystemCode::COLLECT, Direction::SE))
        ,Instruction(Code::SYS,make_shared<Action>(SystemCode::MOVE, Direction::NW))
        ,Instruction(Code::SYS,make_shared<Action>(SystemCode::COLLECT, Direction::NW))
        ,Instruction(Code::JMP,make_shared<Number>(0))
        ,Instruction(Code::END,nullptr)
    });

	for(int i=0; i<3; i++)
		arena.create_robot(army5.get_id(), prog5);

	Army army6("Army 6");
	arena.insert_army(army6);
	const vector<Instruction> prog6 ({
        Instruction(Code::SYS,make_shared<Action>(SystemCode::MOVE, Direction::NE))
        ,Instruction(Code::SYS,make_shared<Action>(SystemCode::COLLECT, Direction::SE))
        ,Instruction(Code::SYS,make_shared<Action>(SystemCode::MOVE, Direction::SE))
        ,Instruction(Code::SYS,make_shared<Action>(SystemCode::COLLECT, Direction::SE))
        ,Instruction(Code::SYS,make_shared<Action>(SystemCode::MOVE, Direction::NW))
        ,Instruction(Code::SYS,make_shared<Action>(SystemCode::COLLECT, Direction::NW))
        ,Instruction(Code::JMP,make_shared<Number>(0))
        ,Instruction(Code::END,nullptr)
    });

	for(int i=0; i<3; i++)
		arena.create_robot(army6.get_id(), prog6);

	Army army7("Army 7");
	arena.insert_army(army7);
	const vector<Instruction> prog7 ({
        Instruction(Code::SYS,make_shared<Action>(SystemCode::MOVE, Direction::NE))
        ,Instruction(Code::SYS,make_shared<Action>(SystemCode::COLLECT, Direction::SE))
        ,Instruction(Code::SYS,make_shared<Action>(SystemCode::MOVE, Direction::SE))
        ,Instruction(Code::SYS,make_shared<Action>(SystemCode::COLLECT, Direction::SE))
        ,Instruction(Code::SYS,make_shared<Action>(SystemCode::MOVE, Direction::NW))
        ,Instruction(Code::SYS,make_shared<Action>(SystemCode::COLLECT, Direction::NW))
        ,Instruction(Code::JMP,make_shared<Number>(0))
        ,Instruction(Code::END,nullptr)
    });

	Army army8  ("Army 8");
	Army army9  ("Army 9");
	Army army10 ("Army 10");

	arena.insert_army(army8);
	arena.insert_army(army9);
	arena.insert_army(army10);

	for(int i=0; i<3; i++) {
		arena.create_robot(army7.get_id(), prog7);
		arena.create_robot(army8.get_id(), prog7);
		arena.create_robot(army9.get_id(), prog7);
		arena.create_robot(army10.get_id(), prog7);
	}

	Core core(arena, 1000);
	core.start();
}
