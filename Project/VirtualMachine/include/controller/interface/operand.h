#ifndef VIRTUALMACHINE_OPERAND_H
#define VIRTUALMACHINE_OPERAND_H

#include <string>

using namespace std;

class Operand {

    public:
        virtual int get_atr(int i) const = 0;

//        virtual string& prn() const = 0;
};

#endif
