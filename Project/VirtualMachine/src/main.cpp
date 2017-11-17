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

//Global variables and settings
Arena arena;
int lastRobotPos = 0;
int availableCrystals = 120;
unsigned int robotHealth = 100;
int arenaSleepTime = 1000;
double robotFuel = 100;
int robotMeleeAttack = 20;
int maxCrystalsPerCell = 20;
double robotMovFuelUsage = 1.5;
int machineInstructionsPerCycle = 50;
double robotInstFuelUsage = 0.01;

int main() {
	int terrain[10][20] = {
		{3, 1, 3, 3, 4, 2, 3, 0, 2, 3, 0, 3, 3, 0, 4, 1, 2, 3, 1, 1}, 
		{0, 1, 1, 1, 1, 1, 3, 4, 3, 3, 0, 3, 0, 2, 0, 1, 1, 1, 3, 4}, 
		{4, 4, 0, 4, 3, 4, 0, 2, 2, 0, 4, 1, 4, 1, 4, 1, 0, 2, 3, 3}, 
		{1, 0, 3, 1, 2, 2, 3, 2, 1, 1, 0, 4, 3, 3, 0, 1, 1, 3, 1, 1}, 
		{2, 4, 1, 2, 1, 4, 0, 3, 1, 4, 3, 2, 1, 4, 3, 2, 0, 1, 2, 2}, 
		{2, 3, 0, 4, 4, 0, 4, 4, 3, 2, 1, 3, 0, 2, 2, 0, 1, 0, 1, 1}, 
		{4, 2, 1, 2, 3, 4, 4, 0, 4, 0, 3, 4, 4, 2, 1, 3, 4, 4, 4, 3}, 
		{4, 0, 0, 2, 0, 1, 2, 4, 2, 3, 2, 0, 0, 2, 2, 0, 4, 2, 1, 1}, 
		{3, 3, 1, 2, 3, 3, 4, 4, 4, 0, 2, 2, 4, 4, 4, 4, 4, 2, 1, 2}, 
		{4, 3, 4, 4, 4, 4, 2, 1, 2, 1, 1, 4, 0, 4, 1, 3, 1, 0, 4, 2}, 
	};
	//arena.setTerrain(terrain);

	Army army1("Army 1");
	arena.insert_army(army1);
	vector<Instruction> prog1 ({
        Instruction(Code::SYS,make_shared<Action>(SystemCode::MOVE, Direction::NE))
        ,Instruction(Code::SYS,make_shared<Action>(SystemCode::COLLECT, Direction::N))
        ,Instruction(Code::SYS,make_shared<Action>(SystemCode::MOVE, Direction::N))
        ,Instruction(Code::SYS,make_shared<Action>(SystemCode::COLLECT, Direction::SE))
        ,Instruction(Code::SYS,make_shared<Action>(SystemCode::MOVE, Direction::N))
        ,Instruction(Code::SYS,make_shared<Action>(SystemCode::COLLECT, Direction::N))
        ,Instruction(Code::END,nullptr)
    });

	for(int i=0; i<1; i++)
		arena.create_robot(army1.get_id(), prog1);

	Army army2("Army 2");
	arena.insert_army(army2);
	vector<Instruction> prog2 ({
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
		arena.create_robot(army2.get_id(), prog2);
	while(true){
		arena.update();
		this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
}

