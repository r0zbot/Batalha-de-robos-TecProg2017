#ifndef VIRTUALMACHINE_ENTITY_MOVE_H
#define VIRTUALMACHINE_ENTITY_MOVE_H

#include <controller/classes/instruction.h>

#include <model/interface/entity.h>

typedef const vector<Instruction> Program;

/**
 * @file  entity_move.h
 * @class EntityMove
 *
 * @brief This class represents a general interface for game
 *        entities that move.
 *
 * The <b>EntityMove</b> class is the most general interface for any
 * model object that represents an {@link Entity} that implements
 * logical movement behavior. It provides general functions and
 * attributes for this kind of {@link Entity}.
 */
class EntityMove : public Entity {

    protected:
        /**
         * Stores the amount of crystal the
         * {@link Entity} is holding.
         */
        int crystals;

        /**
         * Stores the amount of fuel the {@link Entity} carries.
         */
        double fuel;

        /**
         * Represents the maximum amount of fuel the
         * {@link Entity} can carry.
         */
        const double fuel_capacity;

        /**
         * Stores the group's ID of this entity, or -1 if
         * this {@link Entity} does not belong to any group.
         */
        int group_id;

        /**
         * Stores the entity's healthy points.
         */
        int hp;

        /**
         * Represents the maximum amount of healthy points
         * the {@link Entity} can have.
         */
        const unsigned int hp_capacity;

    public:
        /**
         * @brief Constructs an {@link Entity} that moves at the specified position
         *        of the {@link Arena}.
         *
         * @param [pos] The position of the {@link Entity} at the {@link Arena}.
         *
         * @param [fuel_capacity] The maximum amount of fuel this {@link Entity}
         *                        can carry. It's 100.0 by default.
         *
         * @param [hp_capacity] The maximum amount of healthy points this
         *                      {@link Entity} can have. It's 100 by default.
         */
        explicit EntityMove(const Hex &pos,
                            double fuel_capacity = 100.0,
                            unsigned int hp_capacity = 100);

        /**
         * @brief Sets the amount of crystal this {@link Entity}
         *        is carrying to zero.
         */
        void clear_crystals();

        /**
         * @brief Gets the amount of crystals this {@link Entity}
         *        is carrying.
         *
         * @return The amount of crystals this {@link Entity} holds.
         */
        int get_crystals() const;

        /**
         * @brief Gets the quantity of fuel this {@link Entity} has.
         *
         * @return The quantity of fuel this {@link Entity} has.
         */
        double get_fuel() const;

        /**
         * @brief Gets the entity's group ID.
         *
         * If this {@link Entity} does not belong to a group, it
         * will return -1.
         *
         * @return The entity's group ID.
         */
        int get_group_id() const;

        /**
         * @brief Gets the entity's healthy points.
         *
         * @return The entity's healthy points.
         */
        int get_hp() const;

        /**
         * @brief Heals a specific amount of healthy points.
         *
         * @param [amount] The quantity that must be healed.
         */
        void heal(unsigned int amount);

        /**
         * @brief Adds a crystal to the current amount this entity is carrying.
         *
         * @return True if it was possible to add the crystal to this entity,
         *         false otherwise.
         */
        bool insert_crystal();

        /**
         * @brief Executes the entity's movement logic behavior.
         *
         * This method is an abstract method that any derived class must
         * implement with their movement logic behavior.
         */
        virtual void move() = 0;

        /**
         * @brief Supply this {@link Entity} with a specific amount
         *        of fuel.
         *
         * @param [amount] The amount that will be refueled.
         */
        void refuel(double amount);

        /**
         * @brief Removes a crystal of from the current amount this entity is carrying.
         *
         * @return True if it was possible to remove the crystal,
         *         false otherwise.
         */
        bool remove_crystal();

        /**
         * @brief Sets the entity's group ID.
         *
         * @param [group_id] The entity's new group ID.
         */
        void set_group_id(int group_id);

        /**
         * @brief Modifies the entity's set of instructions.
         *
         * This method is an abstract method that any derived class must
         * implement.
         */
        virtual void set_program(const Program &program) = 0;

        /**
         * @brief Removes from the {@link #Entity} healthy points
         *        the amount of damaged suffered.
         *
         * @param [damage] The damaged suffered by some action.
         */
        void take_damage(int damage);

        /**
         * @brief Try to use a specific quantity of fuel to a
         *        general action.
         *
         * @param [amount] The quantity of fuel that will be used.
         *
         * @return True if possible to realize some action with
         *         the fuel provided, false otherwise.
         */
        bool use_fuel(double amount);
};

typedef shared_ptr<EntityMove> EntityMovePtr;

#endif
