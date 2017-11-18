#ifndef VIRTUALMACHINE_ENTITY_MOVE_H
#define VIRTUALMACHINE_ENTITY_MOVE_H

#include <controller/classes/instruction.h>

#include <model/interface/entity.h>
#include <util/config.h>

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
         * Represents the damage inflicted by melee attacks.
         */
        const unsigned int dmg_melee_atk;

        /**
         * Represents the damage inflicted by short range attacks.
         */
        const unsigned int dmg_short_atk;

        /**
         * Represents the damage inflicted by long range attacks.
         */
        const unsigned int dmg_long_atk;

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

        /**
         * Represents the maximum amount of collectables
         * the {@link Entity} can carry.
         */
        const unsigned int inventory_size;

    public:
        /**
         * @brief Constructs an {@link Entity} that moves at the specified position
         *        of the {@link Arena}.
         *
         * @param [pos]            The position of the {@link Entity} at the {@link Arena}.
         *
         * @param [image_path]     The path to this {@link #Entity} sprite.
         *
         * @param [fuel_capacity]  The maximum amount of fuel this {@link Entity}
         *                         can carry. It's 100 by default.
         *
         * @param [inventory_size] The maximum amount of collectables
         *                         this {@link Entity} can carry.
         *
         * @param [hp_capacity]    The maximum amount of healthy points this
         *                         {@link Entity} can have. It's 100 by default.
         *
         * @param [dmg_melee_atk]  The damage inflicted by this {@link Entity}
         *                         during a melee attack.
         *
         * @param [dmg_short_atk]  The damage inflicted by this {@link Entity}
         *                         during a short range attack.
         *
         * @param [dmg_long_atk]   The damage inflicted by this {@link Entity}
         *                         during a long range attack.
         */
        explicit EntityMove(const Hex &pos,
                            const string &image_path,
                            double fuel_capacity        = 100,
                            unsigned int inventory_size = 100,
                            unsigned int hp_capacity    = 100,
                            unsigned int dmg_melee_atk  = 20,
                            unsigned int dmg_short_atk  = 10,
                            unsigned int dmg_long_atk   = 10);

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
         * @brief Gets the damage this {@link Entity} inflicts
         *        during melee attacks.
         *
         * @return The damage this {@link Entity} inflicts
         *         during melee attacks.
         */
        unsigned int get_dmg_melee() const;

        /**
         * @brief Gets the damage this {@link Entity} inflicts
         *        during melee attacks.
         *
         * @return The damage this {@link Entity} inflicts
         *         during melee attacks.
         */
        unsigned int get_dmg_short() const;

        /**
         * @brief Gets the damage this {@link Entity} inflicts
         *        during short range attacks.
         *
         * @return The damage this {@link Entity} inflicts
         *         during long range attacks.
         */
        unsigned int get_dmg_long() const;

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
         * @param [quantity] The quantity of fuel to be used.
         *
         * @return True if possible to realize some action with
         *         the current quantity of fuel, false otherwise.
         */
        bool use_fuel(double quantity);
};

typedef shared_ptr<EntityMove> EntityMovePtr;

#endif
