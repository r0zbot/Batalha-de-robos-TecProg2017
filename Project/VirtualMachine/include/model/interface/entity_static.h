#ifndef VIRTUALMACHINE_ENTITY_STATIC_H
#define VIRTUALMACHINE_ENTITY_STATIC_H

#include <model/interface/entity_move.h>

/**
 * @file  entity_static.h
 * @class EntityStatic
 *
 * @brief This class represents a general interface for game
 *        entities that are static.
 *
 * The <b>EntityStatic</b> class is the most general interface for any
 * model object that represents an {@link Entity} that is part of the
 * {@link #Arena} environment. It provides general functions and
 * attributes for this kind of {@link Entity}.
 */
class EntityStatic : public Entity {

    public:
        /**
         * @brief Constructs an {@link #Entity} that is part of the {@link #Arena}
         *        system at the specified position of the grid.
         *
         * @param [pos] The position of the {@link Entity} at the {@link Arena}.
         */
        explicit EntityStatic(const Hex &pos);

        /**
         * @brief Executes the entity's environment logic behavior.
         *
         * This method is an abstract method that any derived class must
         * implement with their environment logic behavior.
         */
        virtual void affect(const EntityMove &e) = 0;
};

#endif
