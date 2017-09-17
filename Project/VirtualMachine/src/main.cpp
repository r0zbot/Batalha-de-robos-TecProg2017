// Move this file to /VirtualMachine/src so this can work on production

#include "../include/code.h"
#include "../include/instruction.h"
#include "../include/machine.h"

Instruction prog[] = {
	Instruction(Code::PUSH, 3)
	,Instruction(Code::PUSH, 5)
	,Instruction(Code::PUSH, 7)
	,Instruction(Code::PUSH, 9)
	,Instruction(Code::CALL, 7)
	,Instruction(Code::PRN, 0)
	,Instruction(Code::END, 0)
	,Instruction(Code::PUSH, 11)
	,Instruction(Code::PUSH, 13)
	,Instruction(Code::PUSH, 15)
	,Instruction(Code::ALC, 4)
	,Instruction(Code::STL, 2)
	,Instruction(Code::STL, 3)
	,Instruction(Code::STL, 4)
	,Instruction(Code::PRN, 0)
	,Instruction(Code::RCE, 3)
	,Instruction(Code::PRN, 0)
	,Instruction(Code::RCE, 2)
	,Instruction(Code::PRN, 0)
	,Instruction(Code::CALL, 21)
	,Instruction(Code::RET, 0)
	,Instruction(Code::PUSH, 95)
	,Instruction(Code::PUSH, 39)
	,Instruction(Code::ALC, 10)
	,Instruction(Code::STL, 6)
	,Instruction(Code::STL, 5)
	,Instruction(Code::RCE, 6)
	,Instruction(Code::RCE, 5)
	,Instruction(Code::PRN, 0)
	,Instruction(Code::PRN, 0)
	,Instruction(Code::RET, 0)
};

int main() {
	Machine m (prog);
	m.execute();
	return 0;
}
