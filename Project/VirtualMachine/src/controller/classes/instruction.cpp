#include <controller/classes/instruction.h>

Instruction::Instruction(const Code code, const int arg) {
    this->code = code;
    this->arg = arg;
}

int Instruction::get_arg() const {
    return this->arg;
}

Code Instruction::get_code() const {
    return this->code;
}
