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
        Operand *arg;

    public:
        /**
         * @brief Constructs a <b>Instruction</b> with the specified
         *        option code and the instruction argument.
         *
         * @param [code] The instruction option code.
         * @param [arg]  The instruction argument.
         */
        Instruction(Code code, Operand *arg);

        /**
         * @brief Copies the argument's attributes to this <b>Instruction</b> object.
         *
         * @param [i] The object that will be assigned to the function caller.
         *
         * @return A pointer to the new value of the function caller.
         */
        Instruction& operator=(const Instruction &i);

        /**
         * @brief Gets the instruction argument.
         *
         * @return The instruction argument.
         */
        Operand& get_arg() const;

        /**
         * @brief Gets the instruction option code.
         *
         * @return The instruction option code.
         */
        Code get_code() const;
};

#endif
