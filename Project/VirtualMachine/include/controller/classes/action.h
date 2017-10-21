#ifndef VIRTUALMACHINE_ACTION_H
#define VIRTUALMACHINE_ACTION_H

#include <controller/classes/system.h>

#include <controller/interface/operand.h>

class Action : public Operand {

    private:
        SystemCode type;
        Direction direction;

    public:
        Action(SystemCode type, Direction direction);

        int get_atr(int i) const override;
};

#endif
