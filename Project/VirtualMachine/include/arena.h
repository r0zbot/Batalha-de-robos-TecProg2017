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
        vector<Army> armies;
        int armies_size = 0;

    public:
        explicit Arena();


        Army & get_army(int id);
        longlong get_elapsed_time();
        int insert_army(string name);
        int create_robot(Army &army, int posX, int posY, Program prog);
        void remove_army(int id);
        void system(int op, int arg);
        void update();

};

#endif