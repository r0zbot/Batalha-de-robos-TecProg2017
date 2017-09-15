//Move this file to /VirtualMachine/src so this can work on production

#include "../include/code.h"
#include "../include/instruction.h"
#include "../include/machine.h"

Instruction prog[] = {
	Instruction(Code::PUSH, 43)
	,Instruction(Code::PUSH, 42)
	,Instruction(Code::DUP, 0)
	,Instruction(Code::STL, 0)
	,Instruction(Code::PRN, 0)
	,Instruction(Code::RET, 0)
	,Instruction(Code::CALL, 1)
	,Instruction(Code::PRN, 0)
	,Instruction(Code::END, 0)
};

int main() {
	Machine m (prog);
	m.execute();
	return 0;
}
