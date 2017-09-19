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

Instruction fat[] = {
		{Code::PUSH, 8},  // 0
		{Code::CALL, 4},  // 1
		{Code::PRN,  0},  // 2
		{Code::END,  0},  // 3

		// FAT
		{Code::ALC,  1},  // 4
		{Code::DUP,  0},  // 5
		{Code::STL,  1},  // 6 n
		{Code::PUSH, 1},  // 7
		{Code::EQ,   0},  // 8 n == 1 ?
		{Code::JIF, 13},  // 9
		{Code::PUSH, 1},  // 10
		{Code::FRE,  1},  // 11
		{Code::RET,  0},  // 12
		{Code::RCE,  1},  // 13 n
		{Code::PUSH, 1},  // 14
		{Code::SUB,  0},  // 15 n-1
		{Code::CALL, 4},  // 16 fat(n-1)
		{Code::RCE,  1},  // 17 n
		{Code::MUL,  0},  // 18 n * fat(n-1)
		{Code::FRE,  1},  // 19
		{Code::RET,  0}   // 20
};

int main() {
	Machine m (fat);
	m.execute();
	return 0;
}
