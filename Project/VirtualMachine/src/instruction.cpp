#include "../include/instruction.h"

Instruction::Instruction(const Code code, const int arg) {
    this->code = code;
    this->arg = arg;
}

const int Instruction::get_arg() const {
    return this->arg;
}

const Code Instruction::get_code() const {
    return this->code;
}
