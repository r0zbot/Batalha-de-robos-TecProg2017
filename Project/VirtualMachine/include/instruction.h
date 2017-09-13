#ifndef VIRTUALMACHINE_INSTRUCTION_H
#define VIRTUALMACHINE_INSTRUCTION_H


#include "code.h"


class Instruction {

    private:
        Code code;
        
        int arg;

    public:
        Instruction(const Code code, const int arg);
        
        const Code get_code() const;

        const int get_arg() const;
};


#endif