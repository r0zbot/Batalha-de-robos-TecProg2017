#ifndef VIRTUALMACHINE_OPERAND_H
#define VIRTUALMACHINE_OPERAND_H

class Operand {

    public:
        virtual int get_atr(int i) const = 0;
};

#endif
