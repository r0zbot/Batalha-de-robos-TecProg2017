#ifndef VIRTUALMACHINE_NUMBER_H
#define VIRTUALMACHINE_NUMBER_H

#include <controller/interface/operand.h>

/**
 * @file number.h
 * @class Number
 *
 * @brief The <b>Number</b> class represents a simple number {@link #Operand}.
 */
class Number : public Operand {

    private:
        /**
         * Represents the number value.
         */
        const int v;

    public:
        /**
         * @brief Constructs a <b>Number</b> object with the
         *        specified value.
         *
         * @param [v] The <b>Number</b> value.
         */
        explicit Number(int v);

        /**
         * @brief Return the specified <b>Operand</b> attribute.
         *
         * @param [i] The attribute position.
         *
         * @return The attribute at the specified position.
         */
        int get_atr(int i) const override;

        /**
         * @brief Returns a string representation of the object.
         *
         * @return A string representation of the object.
         */
        string prn() const override;
};

#endif
