#ifndef VIRTUALMACHINE_CODE_H
#define VIRTUALMACHINE_CODE_H


enum class Code {
    PUSH,
    POP,
    DUP,
    ADD,
    SUB,
    MUL,
    DIV,
    JMP,
    JIT,
    JIF,
    CALL,
    RET,
    STL, 
    RCE, 
    EQ,
    GT,
    GE,
    LT,
    LE,
    NE,
    STO,
    RCL,
    END,
    PRN
};


#endif