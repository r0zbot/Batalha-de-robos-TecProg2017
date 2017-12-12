#ifndef VIRTUALMACHINE_CODE_H
#define VIRTUALMACHINE_CODE_H

/**
 * @file code.h
 * @enum Code
 *
 * @brief The <b>Code</b> is a strongly typed enum that defines {@link #Instruction} codes.
 *
 * The <b>Code</b> enum class contains the option codes for instructions
 * implemented in the <b>Machine</b>.
 */
enum class Code {
    ADD,  ///< Pops both topmost elements from the stack and pushes its sum

    ALC,  ///< Allocates a specific amount of space in the current frame scope

    ATR,  ///< Pops the topmost element from the stack and pushes its specified attribute

    CALL, ///< Call a specific function

    DIV,  ///< Pops both topmost elements from the stack and pushes its quotient

    DUP,  ///< Duplicates the topmost element of the stack

    EQ,   ///< Verify if both topmost elements are equal and pushes the result

    END,  ///< Stops the execution of the <b>Machine</b>

    FRE,  ///< Frees a specific amount of space in the current frame scope

    GE,   ///< Execute a greater/equal condition in both topmost elements and pushes the result

    GT,   ///< Execute a greater condition in both topmost elements and pushes the result

    JIF,  ///< Jump if the topmost element of the stack is false

    JIT,  ///< Jump if the topmost element of the stack is false

    JMP,  ///< Execute a unconditional jump to another instruction

    LE,   ///< Execute a lower/equal condition in both topmost elements and pushes the result

    LT,   ///< Execute a lower condition in both topmost elements and pushes the result

    MATR, ///< Pushes the specified atribute

    MUL,  ///< Pops both topmost elements from the stack and pushes its product

    NE,   ///< Execute a not equal condition in both topmost elements and pushes the result

    NOP,  ///< No operation

    POP,  ///< Pops the topmost element of the stack

    PRN,  ///< Pops and prints the topmost element of the stack

    PUSH, ///< Pushes an element to the top of the stack

    RCE,  ///< Pushes the specified subprogram local variable to the main stack

    RCL,  ///< Pushes the specified global variable to the main stack

    RET,  ///< Stops the current subprocess and return to the last function activated

    SEE,  ///< Pushes the cell at the specified direction

    STL,  ///< Stores the topmost value of the stack as a local variable in the current subroutine active

    STO,  ///< Stores the topmost value of the stack as a global variable

    SUB,  ///< Pops both topmost elements from the stack and pushes its subtraction

    SYS,  ///< Executes a system call, which pops the arguments for the selected call from the stack.
};

#endif
