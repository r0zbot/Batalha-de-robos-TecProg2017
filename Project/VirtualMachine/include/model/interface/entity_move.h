#ifndef VIRTUALMACHINE_ENTITY_MOVE_H
#define VIRTUALMACHINE_ENTITY_MOVE_H

#include <model/interface/entity.h>

class EntityMove : public Entity {

    public:
        explicit EntityMove(const Hex &pos);
        virtual void move() = 0;
};

#endif
