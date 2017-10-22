#ifndef VIRTUALMACHINE_ACTION_H
#define VIRTUALMACHINE_ACTION_H

#include <controller/classes/system.h>

#include <controller/interface/operand.h>

class Action : public Operand {

    private:
        SystemCode code;
        Direction direction;

    public:
        Action(SystemCode code, Direction direction);

        int get_atr(int i) const override;

        SystemCode get_code() const;

        Direction get_direction() const;
};

#endif
