#ifndef VIRTUALMACHINE_INSTRUCTION_H
#define VIRTUALMACHINE_INSTRUCTION_H

#include <controller/classes/code.h>

#include <controller/interface/operand.h>

/**
 * @file  instruction.h
 * @class Instruction
 *
 * @brief This class represents functions to be executed by the {@link #Machine}.
 *
 * The <b>Instruction</b> class represents an instruction object
 * with an option/function code from the <b>Code</b> enum class
 * and the instruction argument.
 */
class Instruction {

    private:
        /** The instruction option code, representing a function.*/
        Code code;

        /** The instruction argument.*/
        OperandPtr arg;

    public:
        /**
         * @brief Constructs a <b>Instruction</b> with the specified
         *        option code and the instruction argument.
         *
         * @param [code] The instruction option code.
         * @param [arg]  The instruction argument.
         */
        Instruction(Code code, const OperandPtr &arg);

        /**
         * @brief Gets the instruction argument.
         *
         * @return The instruction argument.
         */
        OperandPtr get_arg() const;

        /**
         * @brief Gets the instruction option code.
         *
         * @return The instruction option code.
         */
        Code get_code() const;
};

#endif
