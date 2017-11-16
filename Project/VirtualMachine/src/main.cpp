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
	//arena.setDataFile("Z:/Daniel/USP/EPs/MAC0216/Projeto/Project/data/arena.terrain");

	Army army1("Army 1");
	arena.insert_army(army1);
	vector<Instruction> prog1 ({
        Instruction(Code::PUSH,make_shared<Number>(10))
        ,Instruction(Code::PUSH,make_shared<Number>(4))
        ,Instruction(Code::ADD,nullptr)
        ,Instruction(Code::PUSH,make_shared<Number>(3))
        ,Instruction(Code::MUL,nullptr)
        ,Instruction(Code::PRN,nullptr)
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

	Army army3("Army 3");
	arena.insert_army(army3);
	vector<Instruction> prog3 ({
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
		arena.create_robot(army3.get_id(), prog3);

	Army army4("Army 4");
	arena.insert_army(army4);
	vector<Instruction> prog4 ({
        Instruction(Code::SYS,make_shared<Action>(SystemCode::MOVE, Direction::NE))
        ,Instruction(Code::SYS,make_shared<Action>(SystemCode::COLLECT, Direction::N))
        ,Instruction(Code::SYS,make_shared<Action>(SystemCode::MOVE, Direction::N))
        ,Instruction(Code::SYS,make_shared<Action>(SystemCode::COLLECT, Direction::SE))
        ,Instruction(Code::SYS,make_shared<Action>(SystemCode::MOVE, Direction::N))
        ,Instruction(Code::SYS,make_shared<Action>(SystemCode::COLLECT, Direction::N))
        ,Instruction(Code::END,nullptr)
    });

	for(int i=0; i<1; i++)
		arena.create_robot(army4.get_id(), prog4);

	Army army5("Army 5");
	arena.insert_army(army5);
	vector<Instruction> prog5 ({
        Instruction(Code::PUSH,make_shared<Number>(3))
        ,Instruction(Code::PUSH,make_shared<Number>(5))
        ,Instruction(Code::PUSH,make_shared<Number>(7))
        ,Instruction(Code::PUSH,make_shared<Number>(9))
        ,Instruction(Code::CALL,make_shared<Number>(7))
        ,Instruction(Code::PRN,nullptr)
        ,Instruction(Code::END,nullptr)
        ,Instruction(Code::PUSH,make_shared<Number>(11))
        ,Instruction(Code::PUSH,make_shared<Number>(13))
        ,Instruction(Code::PUSH,make_shared<Number>(15))
        ,Instruction(Code::ALC,make_shared<Number>(4))
        ,Instruction(Code::STL,make_shared<Number>(2))
        ,Instruction(Code::STL,make_shared<Number>(3))
        ,Instruction(Code::STL,make_shared<Number>(4))
        ,Instruction(Code::PRN,nullptr)
        ,Instruction(Code::RCE,make_shared<Number>(3))
        ,Instruction(Code::PRN,nullptr)
        ,Instruction(Code::RCE,make_shared<Number>(2))
        ,Instruction(Code::PRN,nullptr)
        ,Instruction(Code::CALL,make_shared<Number>(21))
        ,Instruction(Code::RET,nullptr)
        ,Instruction(Code::PUSH,make_shared<Number>(95))
        ,Instruction(Code::PUSH,make_shared<Number>(39))
        ,Instruction(Code::ALC,make_shared<Number>(10))
        ,Instruction(Code::STL,make_shared<Number>(6))
        ,Instruction(Code::STL,make_shared<Number>(5))
        ,Instruction(Code::RCE,make_shared<Number>(6))
        ,Instruction(Code::RCE,make_shared<Number>(5))
        ,Instruction(Code::PRN,nullptr)
        ,Instruction(Code::PRN,nullptr)
        ,Instruction(Code::RET,nullptr)
    });

	for(int i=0; i<1; i++)
		arena.create_robot(army5.get_id(), prog5);
	while(true){
		arena.update();
		this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
}

