// Move this file to /VirtualMachine/src so this can work on production

#include <vector>

#include <controller/classes/code.h>
#include <controller/classes/action.h>
#include <controller/classes/number.h>
#include <controller/classes/instruction.h>

#include <model/entity/machine.h>
#include <util/globals.h>
#include <thread>

using namespace std;

int main() {
	//arena.setDataFile("Z:/Daniel/USP/EPs/MAC0216/Projeto/Project/data/arena.terrain");

	Army army1("Army 1");
	arena.insert_army(army1);

	Army army2("Army 2");
	arena.insert_army(army2);

	Army army3("Army 3");
	arena.insert_army(army3);
	vector<Instruction> prog1 ({
        Instruction(Code::SYS,make_shared<Action>(SystemCode::MOVE, Direction::NE))
        ,Instruction(Code::SYS,make_shared<Action>(SystemCode::COLLECT, Direction::N))
        ,Instruction(Code::SYS,make_shared<Action>(SystemCode::MOVE, Direction::N))
        ,Instruction(Code::SYS,make_shared<Action>(SystemCode::COLLECT, Direction::SE))
        ,Instruction(Code::SYS,make_shared<Action>(SystemCode::MOVE, Direction::N))
        ,Instruction(Code::SYS,make_shared<Action>(SystemCode::COLLECT, Direction::N))
        ,Instruction(Code::END,nullptr)
    });

	for(int i=0; i<5; i++)
		arena.create_robot(army3.get_id(), prog1);
	while(true){
		arena.update();
		this_thread::sleep_for(std::chrono::milliseconds(200));
	}
}

