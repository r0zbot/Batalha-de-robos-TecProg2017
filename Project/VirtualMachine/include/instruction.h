#ifndef VIRTUALMACHINE_INSTRUCTION_H
#define VIRTUALMACHINE_INSTRUCTION_H

#include "code.h"

class Instruction {

    private:
        Code code;

        int arg;

    public:
        Instruction(Code code, int arg);

        int get_arg() const;
        
        Code get_code() const;
};

#endif
