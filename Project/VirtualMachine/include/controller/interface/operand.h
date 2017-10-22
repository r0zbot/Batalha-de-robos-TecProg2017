#ifndef VIRTUALMACHINE_OPERAND_H
#define VIRTUALMACHINE_OPERAND_H

#include <string>

using namespace std;

/**
 * @file  operand.h
 * @class Operand
 *
 * @brief This class is the topmost Abstract Base Class for operand objects.
 *
 * The <b>Operand</b> class is the most general interface for any logical object
 * that represents an operand in the game controller. It provides general functions
 * for the operand identification.
 *
 * @attention Any other <b>Operand</b> interface <b>must</b> extends this class.
 */
class Operand {

    public:
        /**
         * @brief Return the specified <b>Operand</b> attribute.
         *
         * @param [i] The attribute position.
         *
         * @return THe attribute at the speficied position.
         */
        virtual int get_atr(int i) const = 0;

        /**
         * @brief Returns a string representation of the object.
         *
         * @return A string representation of the object.
         */
        virtual string prn() const = 0;
};

#endif
