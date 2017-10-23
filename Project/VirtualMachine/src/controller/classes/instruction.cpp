#include <controller/classes/instruction.h>
#include <controller/classes/number.h>

Instruction::Instruction(const Code code, Operand *arg) : code(code), arg(arg) {}

Instruction::Instruction(const Code code, int number) : code(code), arg(new Number(number)) {}

Instruction& Instruction::operator=(const Instruction &i) = default;

Operand& Instruction::get_arg() const {
    return *this->arg;
}

Code Instruction::get_code() const {
    return this->code;
}
