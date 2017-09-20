// Move this file to /VirtualMachine/src so this can work on production

#include "../include/code.h"
#include "../include/instruction.h"
#include "../include/machine.h"

Instruction prog[] = {
	Instruction(Code::PUSH, 8)
	,Instruction(Code::CALL, 4)
	,Instruction(Code::PRN, 0)
	,Instruction(Code::END, 0)
	,Instruction(Code::ALC, 1)
	,Instruction(Code::DUP, 0)
	,Instruction(Code::STL, 1)
	,Instruction(Code::PUSH, 1)
	,Instruction(Code::EQ, 0)
	,Instruction(Code::JIF, 13)
	,Instruction(Code::PUSH, 1)
	,Instruction(Code::FRE, 1)
	,Instruction(Code::RET, 0)
	,Instruction(Code::RCE, 1)
	,Instruction(Code::PUSH, 1)
	,Instruction(Code::SUB, 0)
	,Instruction(Code::CALL, 4)
	,Instruction(Code::RCE, 1)
	,Instruction(Code::MUL, 0)
	,Instruction(Code::FRE, 1)
	,Instruction(Code::RET, 0)
};

int main() {
	Machine m (prog);
	m.execute();
	return 0;
}
