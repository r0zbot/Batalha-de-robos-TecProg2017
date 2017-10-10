//
// Created by Daniel on 10/10/2017.
//

#ifndef VIRTUALMACHINE_ROBOT_H
#define VIRTUALMACHINE_ROBOT_H

#include <machine.h>
#include <entity.h>

class Robot: public Entity{
    private:
        Machine machine;
    public:
        Robot(int id, int posX, int posY, Program prog);
        void replace_machine(Program prog);
        void update() override;
};

#endif //VIRTUALMACHINE_ROBOT_H
