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
	//arena.setDataFile("/home/lucas/Documentos/IME-USP/MAC-0216/Batalha-de-robos-TecProg2017/Project/data/arena.terrain");

	Army army1("Army 1");
	arena.insert_army(army1);
	vector<Instruction> prog1 ({
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

	for(int i=0; i<5; i++)
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

	for(int i=0; i<5; i++)
		arena.create_robot(army2.get_id(), prog2);
	while(true){
		arena.update();
		this_thread::sleep_for(std::chrono::milliseconds(200));
	}
}

