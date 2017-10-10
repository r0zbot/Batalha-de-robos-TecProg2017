#ifndef VIRTUALMACHINE_ROBOT_H
#define VIRTUALMACHINE_ROBOT_H

#include <controller/classes/machine.h>

#include <model/interface/entity.h>

class Robot: public Entity{
    private:
        Machine machine;
    public:
        Robot(int id, int posX, int posY, Program prog);
        void replace_machine(Program prog);
        void update() override;
};

#endif
