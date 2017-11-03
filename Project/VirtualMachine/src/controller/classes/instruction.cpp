#include <controller/classes/instruction.h>

Instruction::Instruction(const Code code, const OperandPtr &arg)
        : code(code),
          arg(arg) {}

OperandPtr Instruction::get_arg() const {
    return this->arg;
}

Code Instruction::get_code() const {
    return this->code;
}
