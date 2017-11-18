// Move this file to /VirtualMachine/src so this can work on production

#include <vector>

#include <controller/classes/code.h>
#include <controller/classes/action.h>
#include <controller/classes/number.h>
#include <controller/classes/instruction.h>

#include <model/entity/machine.h>
#include <util/globals.h>
#include <util/sleep.h>

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
	vector<vector<int>> terrain {
		{2, 4, 2, 1, 4, 2, 3, 1, 0, 4, 2, 0, 4, 4, 0, 2, 0, 2, 1, 1}, 
		{0, 3, 3, 3, 3, 2, 3, 1, 2, 4, 1, 3, 0, 0, 4, 1, 0, 0, 3, 1}, 
		{4, 2, 3, 1, 4, 2, 2, 0, 1, 0, 2, 4, 0, 1, 3, 1, 0, 2, 1, 4}, 
		{0, 0, 4, 4, 3, 2, 3, 1, 1, 1, 3, 1, 0, 4, 0, 0, 4, 1, 4, 3}, 
		{3, 2, 4, 1, 2, 1, 0, 3, 1, 3, 2, 4, 4, 1, 3, 3, 2, 3, 4, 0}, 
		{4, 1, 0, 0, 1, 4, 0, 4, 2, 0, 1, 1, 0, 1, 1, 2, 3, 3, 4, 0}, 
		{4, 2, 2, 3, 3, 2, 3, 3, 2, 0, 3, 1, 4, 4, 2, 0, 1, 1, 2, 0}, 
		{4, 2, 1, 0, 3, 3, 4, 4, 3, 1, 0, 1, 3, 3, 1, 2, 0, 2, 3, 2}, 
		{0, 2, 3, 4, 1, 0, 1, 3, 1, 0, 0, 3, 3, 0, 4, 4, 0, 3, 4, 3}, 
		{3, 0, 2, 2, 0, 0, 3, 2, 2, 0, 1, 4, 2, 0, 4, 3, 3, 0, 3, 1}, 
	};
	arena.import_terrain(terrain);

	Army army1("Army 1");
	arena.insert_army(army1);

	Army army2("Army 2");
	arena.insert_army(army2);
	vector<Instruction> prog1 ({
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

	for(int i=0; i<5; i++)
		arena.create_robot(army2.get_id(), prog1);
	while(true){
		arena.update();
		arena_sleep(arenaSleepTime);
	}
}

