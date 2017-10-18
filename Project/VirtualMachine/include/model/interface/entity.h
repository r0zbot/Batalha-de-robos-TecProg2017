#ifndef VIRTUALMACHINE_ENTITY_H
#define VIRTUALMACHINE_ENTITY_H

#include <application/component/hex.h>

/**
 * @file  entity.h
 * @class Entity
 *
 * @brief This class is the topmost Abstract Base Class for entities
 *        in the game.
 *
 * The <b>Entity</b> class is the most general interface for any
 * model object that represents an entity in the game. It provides
 * general functions for logic behavior.
 *
 * @attention Any other <b>Entity</b> interface <b>must</b> extends this class.
 */
class Entity {

    private:
        /**
         * Represents a simple ID generator for any
         * derived entity.
         */
        static int id_gen;

    protected:
        /**
         * Represents the entity's id, that is unique for every entity.
         */
        const int id;

        /**
         * Represents the entity's position in the {@link Arena}.
         */
        Hex pos;

    public:
        /**
         * @brief Constructs an <b>Entity</b> at the specified position.
         *
         * @param [pos] The position of the entity at the {@link Arena}.
         */
        explicit Entity(const Hex &pos);

        /**
         * @brief Overload of "equals" operator so it can compare two
         *        <b>Entity</b> objects.
         *
         * This method executes inner comparisons in both of the
         * entities's ID, and return true only if their IDs are equal.
         *
         * @param [e] The entity to be compared to the caller object.
         *
         * @return True if the entities have the same ID,
         *         false otherwise.
         */
        bool operator==(const Entity &e) const;

        /**
         * @brief Overload of "not equals" operator so it can compare two
         *        <b>Entity</b> objects.
         *
         * This method executes inner comparisons in both of the
         * entities's ID, and return true only if their IDs are not equal.
         *
         * @param [e] The entity to be compared to the caller object.
         *
         * @return True if the entities have different IDs,
         *         false if they are equal.
         */
        bool operator!=(const Entity &e) const;

        /**
         * @brief Gets the entity's id.
         *
         * @return The entity's id.
         */
        int get_id() const;

        /**
         * @brief Gets the entity's x coordinate, or column position.
         *
         * @return The entity's x coordinate.
         */
        int get_x() const;

        /**
         * @brief Gets the entity's y coordinate, or row position.
         *
         * @return The entity's y coordinate.
         */
        int get_y() const;

        /**
         * @brief Sets a new position to this entity.
         *
         * @param [pos] The {@link Hex} object representing the new
         *              position in the {@link Arena}.
         */
        void set_position(const Hex &pos);

        /**
         * @brief Executes the logic behavior of this entity for a
         *        specific amount of cycles.
         *
         * This method is an abstract method that any derived class must
         * implement with their logic behavior.
         *
         * @param [cycles] The amount of cycles the logic will execute.
         */
        virtual void update(int cycles) = 0;
};

#endif
