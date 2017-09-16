//Move this file to /VirtualMachine/src so this can work on production

#include "../include/code.h"
#include "../include/instruction.h"
#include "../include/machine.h"

Instruction prog[] = {
	Instruction(Code::PUSH, 1)
	,Instruction(Code::DUP, 0)
	,Instruction(Code::STO, 0)
	,Instruction(Code::STO, 1)
	,Instruction(Code::PUSH, 10)
	,Instruction(Code::STO, 2)
	,Instruction(Code::RCL, 0)
	,Instruction(Code::RCL, 1)
	,Instruction(Code::DUP, 0)
	,Instruction(Code::STO, 0)
	,Instruction(Code::ADD, 0)
	,Instruction(Code::DUP, 0)
	,Instruction(Code::STO, 1)
	,Instruction(Code::PRN, 0)
	,Instruction(Code::RCL, 2)
	,Instruction(Code::PUSH, 1)
	,Instruction(Code::SUB, 0)
	,Instruction(Code::DUP, 0)
	,Instruction(Code::STO, 2)
	,Instruction(Code::PUSH, 0)
	,Instruction(Code::EQ, 0)
	,Instruction(Code::JIF, 6)
	,Instruction(Code::END, 0)
};

int main() {
	Machine m (prog);
	m.execute();
	return 0;
}
