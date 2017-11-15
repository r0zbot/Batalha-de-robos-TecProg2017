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
	vector<Instruction> prog1 ({
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

	for(int i=0; i<5; i++)
		arena.create_robot(army1.get_id(), prog1);

	Army army2("Army 2");
	arena.insert_army(army2);
	vector<Instruction> prog2 ({
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
		arena.create_robot(army2.get_id(), prog2);
	while(true){
		arena.update();
		this_thread::sleep_for(std::chrono::milliseconds(200));
	}
}

