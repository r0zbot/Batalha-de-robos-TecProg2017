#ifndef VIRTUALMACHINE_INSTRUCTION_H
#define VIRTUALMACHINE_INSTRUCTION_H

#include <code.h>

/**
 * The <b>Instruction</b> class represents an instruction object with an
 * option code from the <b>Code</b> enum class, representing a function,
 * and the instruction argument.
 */
class Instruction {

    private:
        /** The instruction option code, representing a function.*/
        Code code;

        /** The instruction argument.*/
        int arg;

    public:
        /**
         * Constructs a <b>Instruction</b> with the specified
         * option code and the instruction argument.
         *
         * @param [code] The instruction option code.
         * @param [arg]  The instruction argument.
         */
        Instruction(Code code, int arg);

        /**
         * Returns the instruction argument.
         *
         * @return The instruction argument.
         */
        int get_arg() const;

        /**
         * Returns the instruction option code.
         *
         * @return The instruction option code.
         */
        Code get_code() const;
};

#endif
