#ifndef VIRTUALMACHINE_NUMBER_H
#define VIRTUALMACHINE_NUMBER_H

#include <controller/interface/operand.h>

class Number : public Operand {

    private:
        const int v;

    public:
        explicit Number(int v);

        int get_atr(int i) const override;

        /**
         * @brief Returns a string representation of the object.
         *
         * @return A string representation of the object.
         */
        string prn() const override;
};

#endif
