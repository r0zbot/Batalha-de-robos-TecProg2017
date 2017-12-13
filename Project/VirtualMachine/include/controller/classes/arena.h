#ifndef VIRTUALMACHINE_ARENA_H
#define VIRTUALMACHINE_ARENA_H

#include <map>

#include <application/component/hex.h>

#include <controller/classes/syscall.h>

#include <model/entity/army.h>
#include <model/entity/machine.h>

#include <view/view.h>
#include <queue>

using namespace std;

/**
 * @file  arena.h
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

        queue<Hex> updated_cells;

        /**
         * Represents this <b>Arena</b> height, or number of rows in the grid.
         */
        int height;

        /**
         * Represents this <b>Arena</b> width, or number of columns in the grid.
         */
        int width;

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

        /**
         * @brief Validates the given position
         *
         * This method verifies if the current position is valid.
         * If the position is within the <b>Arena</b>
         * limits, it will return true, and false otherwise.
         *
         * @param [pos] The specified position to be checked.
         *
         * @param [e] The {@link #Entity} to be stored at the given position.
         *
         * @return True if the given position is valid, and false otherwise.
         */
        bool validate_position(const Hex &pos, EntityMove &e);

        int current_center_row = 1;
        int current_center_col = 1;

    public:
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

        int create_robot(int id, const Program &prog);

        void die(EntityMove &e);

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
         * @brief Randomly place crystals throughout the arena.
         *
         * @param [crystals] The number of total crystals to generate
         */
        void generate_crystals(int crystals);

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
         * @brief Gets this <b>Arena</b> height, or number of rows in the grid.
         *
         * @return This <b>Arena</b> height, or number of rows in the grid.
         */
        int get_height() const;

        /**
        * @brief Gets this <b>Arena</b> width, or number of columns in the grid.
        *
        * @return Tthis <b>Arena</b> width, or number of columns in the grid..
        */
        int get_width() const;

        /**
         * @brief Imports terrain from a 2D vector
         *
         * @param [terrain] A 2D vector containing integers which represent
         *        each type of terrain available.
         */
        void import_terrain(const vector<vector<int>> &terrainn);

        /**
         * @brief Inserts an {@link #Army} in the current game.
         *
         * @param [army] The {@link #Army} to be inserted in the current game.
         */
        void insert_army(const Army &army);

        /**
         * @brief Loads the <b>Arena</b> system in a @{link #View}.
         *
         * This methods initializes and loads this <b>Arena</b> system and all
         * current activated {@link #Entity} in the game into a {@link #View}.
         *
         * @param [view] The {@link #View} where this <b>Arena</b> will be loaded.
         */
        void load(const View &view) const;

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
         * @brief Renders the <b>Arena</b> system in a @{link #View}.
         *
         * This methods renders this <b>Arena</b> system and all current
         * activated {@link #Entity} in the game into a {@link #View}.
         *
         * @param [view] The {@link #View} that will show this <b>Arena</b>.
         */
        void render(const View &view);

        /**
         * @brief Executes an requisition for a melee attack in a
         *        specified position from the <b>Arena</b>.
         *
         * @param [e] The {@link #EntityMove} that requested the action.
         *
         * @param [pos] The position where the action will be performed.
         *
         * @return A boolean indicating whether it was successfull or not.
         */
        bool request_attack_melee(EntityMove &e, const Hex &pos);

        /**
         * @brief Executes an requisition for a short range attack in a
         *        specified position from the <b>Arena</b>.
         *
         * @param [e] The {@link #EntityMove} that requested the action.
         *
         * @param [pos] The position where the action will be performed.
         *
         * @return A boolean indicating whether it was successfull or not.
         */
        bool request_attack_short(EntityMove &e, const Hex &pos);

        /**
         * @brief Executes an requisition for a long range attack in a
         *        specified position from the <b>Arena</b>.
         *
         * @param [e] The {@link #EntityMove} that requested the action.
         *
         * @param [pos] The position where the action will be performed.
         *
         * @return A boolean indicating whether it was successfull or not.
         */
        bool request_attack_long(EntityMove &e, const Hex &pos);

        /**
         * @brief Executes an requisition for a collect action in a
         *        specified position from the <b>Arena</b>.
         *
         * @param [e] The {@link #EntityMove} that requested the action.
         *
         * @param [pos] The position where the action will be performed.
         *
         * @return A boolean indicating whether it was successfull or not.
         */
        bool request_collect(EntityMove &e, const Hex &pos);

        /**
         * @brief Executes an requisition for a deposit action in a
         *        specified position from the <b>Arena</b>.
         *
         * @param [e] The {@link #EntityMove} that requested the action.
         *
         * @param [pos] The position where the action will be performed.
         *
         * @return A boolean indicating whether it was successfull or not.
         */
        bool request_drop(EntityMove &e, const Hex &pos);

        /**
         * @brief Executes an requisition for a movement action in a
         *        specified position from the <b>Arena</b>.
         *
         * @param [e] The {@link #EntityMove} that requested the action.
         *
         * @param [pos] The position where the action will be performed.
         *
         * @return A boolean indicating whether it was successfull or not.
         */
        bool request_movement(EntityMove &e, const Hex &pos);

        /**
         * @brief Executes the logic behavior of all the game entities
         *        currently active in the <b>Arena</b>.
         */
        void update(const View &view);
};

#endif
