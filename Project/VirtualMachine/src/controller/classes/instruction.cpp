#include <controller/classes/instruction.h>

//template class Instruction<int>;

Instruction::Instruction(const Code code, int arg) {
    this->code = code;
    this->arg = arg;
}

int Instruction::get_arg() const {
    return this->arg;
}

Code Instruction::get_code() const {
    return this->code;
}
