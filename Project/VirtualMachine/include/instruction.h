#ifndef VIRTUALMACHINE_INSTRUCTION_H
#define VIRTUALMACHINE_INSTRUCTION_H


#include "code.h"


class Instruction {

    private:
        int arg;

        Code code;

    public:
        Instruction(const Code code, const int arg);

        const int get_arg() const;
        
        const Code get_code() const;
};


#endif
