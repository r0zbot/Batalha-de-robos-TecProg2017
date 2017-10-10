#ifndef VIRTUALMACHINE_ARENA_H
#define VIRTUALMACHINE_ARENA_H

#include <config.h>
#include <machine.h>
#include <army.h>
#include <vector>


using namespace std;

/**
 * @file  arena.h
 * @class Arena
 *
 * @brief The arena is responsible for managing armies, machines,
 *        and their position.
 */


class Arena{
    //TODO better documentation
    private:
        int machine_id_index = 0;
        longlong time = 0;

        int arena_space[ARENA_HEIGHT][ARENA_WIDTH];
        Army *armies[MAX_ARMY_AMOUNT];
        int armies_size = 0;

    public:
        explicit Arena();

        /**
         * @brief Creates a new machine on the board and assigns it to an army.
         *
         * @param [army] The army the new machine will be assigned to.
         * @param [prog] The code the machine should run.
         */
        void create_machine(Army &army, Program &prog);
        longlong get_elapsed_time();
        void insert_army(Army &army);
        void remove_army(int id);
        void update();

};

#endif