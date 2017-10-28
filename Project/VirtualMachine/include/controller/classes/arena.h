#ifndef VIRTUALMACHINE_ARENA_H
#define VIRTUALMACHINE_ARENA_H

#include <map>

#include <application/component/hex.h>

#include <controller/classes/system.h>

#include <model/entity/army.h>
#include <model/entity/machine.h>

using namespace std;

/**
 * @file arena.h
 * @class Arena
 *
 * @brief This class represents the Hexagonal Grid and the Game System Manager.
 *
 * The <b>Arena</b> class represents the environment where the game will
 * be executed. It's responsible for the entire game system requests and
 * for update all the game entities.
 */
class Arena {

    private:
        /**
         * Represents the Hexagonal Grid Environment.
         */
        unordered_set<Hex> ambient;

        /**
         * Stores all the armies currently actives in the game.
         */
        map<int, Army> armies;

        /**
         * Represents the amount of rounds executed so far in the game.
         */
        unsigned long long time;

        /**
         * @brief Validates the insertion of a game {@link #Entity}
         *        in a specific grid position.
         *
         * This method verifies if it is possible to insert a game {@link #Entity}
         * in a given grid position. If the position is within the <b>Arena</b>
         * limits and it's empty, it will return true, and false otherwise.
         *
         * @param [pos] The specified position to be checked.
         *
         * @param [e] The {@link #Entity} to be stored at the given position.
         *
         * @return True if possible to insert the {@link #Entity} at the
         *         given position, and false otherwise.
         */
        bool validate_insertion(const Hex &pos, EntityMove &e);

    public:
        /**
         * @brief Initialize the <b>Arena</b> and all the Hexagonal
         *        Grid Environment.
         */
        explicit Arena();

        /**
         * @brief Initialize a robot in the given {@link #Army},
         *        at the specified cell, and with the given
         *        instructions.
         *
         * @param [id] The {@link #Army} ID the robot will belong to.
         *
         * @param [pos] The initial position of the robot.
         *
         * @param [prog] The initial set of instructions present in the robot.
         *
         * @return The robot's ID if it's created with success, or -1 if it's
         *         impossible to create the robot.
         */
        int create_robot(int id, const Hex &pos, const Program &prog);

        /**
         * @brief Gets the amount of time passed in the current game.
         *
         * @return The amount of time passed in the current game.
         */
        unsigned long long elapsed_time() const;

        /**
         * @brief Finds and returns an {@link #EntityMove} with the given ID,
         *        if it's currently active in the game.
         *
         * @param [id] The ID of the {@link #EntityMove} that will be searched.
         *
         * @return A reference to the searched {@link #EntityMove}.
         */
        EntityMove& find_entity_move(int id);

        /**
         * @brief Finds and returns an {@link #Army} with the given ID,
         *        if it's currently active in the game.
         *
         * @param [id] The ID of the {@link #Army} that will be searched.
         *
         * @return A reference to the searched {@link #Army}.
         */
        Army& get_army(int id);

        /**
         * @brief Returns a reference to a specific Grid Cell, if it's
         *        within the <b>Arena</b> limits.
         *
         * @param [pos] The position to searched for.
         *
         * @return A reference to the specified Grid Cell.
         */
        const Hex& get_cell(const Hex &pos) const;

        /**
         * @brief Inserts an {@link #Army} in the current game.
         *
         * @param [army] The {@link #Army} to be inserted in the current game.
         */
        void insert_army(const Army &army);

        /**
         * @brief Prints a message in the <b>Arena</b>.
         *
         * @param [s] A message to be printed.
         */
        void print(const string &s);

        /**
         * @brief Prints the information of the given {@link #EntityMove}.
         *
         * @param [e] An {@link #EntityMove} whose attributes will be printed.
         */
        void print(const EntityMove &e);

        /**
         * @brief Prints a message associated with a given {@link #EntityMove}.
         *
         * @param [s] A message to be printed.
         *
         * @param [e] An {@link #EntityMove} associated to the message.
         */
        void print(const string &s, const EntityMove &e);

        /**
         * @brief Prints an {@link #Operand} associated with a given {@link #EntityMove}.
         *
         * @param [op] A {@link #Operand} whose values will be printed.
         *
         * @param [e] An {@link #EntityMove} associated to the {@link #Operand}.
         */
        void print(const Operand &op, const EntityMove &e);

        /**
         * @brief Removes an {@link #Army} and all the entities associated
         *        with it from the current game.
         *
         * @param [id] The ID of the {@link #Army} that will be removed.
         */
        void remove_army(int id);

        /**
         * @brief Executes an requisition for a melee attack in a
         *        specified position from the <b>Arena</b>.
         *
         * @param [e] The {@link #EntityMove} that requested the action.
         *
         * @param [pos] The position where the action will be performed.
         */
        void request_attack_melee(EntityMove &e, const Hex &pos);

        /**
         * @brief Executes an requisition for a short range attack in a
         *        specified position from the <b>Arena</b>.
         *
         * @param [e] The {@link #EntityMove} that requested the action.
         *
         * @param [pos] The position where the action will be performed.
         */
        void request_attack_short(EntityMove &e, const Hex &pos);

        /**
         * @brief Executes an requisition for a long range attack in a
         *        specified position from the <b>Arena</b>.
         *
         * @param [e] The {@link #EntityMove} that requested the action.
         *
         * @param [pos] The position where the action will be performed.
         */
        void request_attack_long(EntityMove &e, const Hex &pos);

        /**
         * @brief Executes an requisition for a collect action in a
         *        specified position from the <b>Arena</b>.
         *
         * @param [e] The {@link #EntityMove} that requested the action.
         *
         * @param [pos] The position where the action will be performed.
         */
        void request_collect(EntityMove &e, const Hex &pos);

        /**
         * @brief Executes an requisition for a deposit action in a
         *        specified position from the <b>Arena</b>.
         *
         * @param [e] The {@link #EntityMove} that requested the action.
         *
         * @param [pos] The position where the action will be performed.
         */
        void request_drop(EntityMove &e, const Hex &pos);

        /**
         * @brief Executes an requisition for a movement action in a
         *        specified position from the <b>Arena</b>.
         *
         * @param [e] The {@link #EntityMove} that requested the action.
         *
         * @param [pos] The position where the action will be performed.
         */
        void request_movement(EntityMove &e, const Hex &pos);

        /**
         * @brief Executes the logic behavior of all the game entities
         *        currently active in the <b>Arena</b>.
         */
        void update();
};

#endif
