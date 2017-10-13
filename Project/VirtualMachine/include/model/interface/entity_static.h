#ifndef VIRTUALMACHINE_ENTITY_STATIC_H
#define VIRTUALMACHINE_ENTITY_STATIC_H

#include <model/interface/entity.h>
#include <model/interface/entity_move.h>

class EntityStatic : public Entity {

    public:
        explicit EntityStatic(const Hex &pos);

        virtual void affect(const EntityMove &e) = 0;
};

#endif
