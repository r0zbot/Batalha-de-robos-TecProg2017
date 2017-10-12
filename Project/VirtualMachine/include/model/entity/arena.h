#ifndef VIRTUALMACHINE_ARENA_H
#define VIRTUALMACHINE_ARENA_H

#include <vector>

#include <controller/classes/machine.h>

#include <model/entity/army.h>

#include <util/config.h>
#include <controller/classes/system.h>

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
        longlong time = 0;

        int arena_space[ARENA_HEIGHT][ARENA_WIDTH];
        vector<Army> armies;

    public:
        explicit Arena();


        Army &get_army(int id);
        Army &get_robots_army(Robot &robot);
        longlong get_elapsed_time();
        int insert_army(string name);
        int create_robot(Army &army, int posX, int posY, Program prog);
        void print(const string &s);
        void print(const string &s, Robot &robot);
        void print(int n, Robot &robot);
        void remove_army(int id);
        void request_attack_melee(Robot &robot, Direction direction);
        void request_attack_short(Robot &robot, Direction direction);
        void request_attack_long(Robot &robot, Direction direction);
        void request_collect(Robot &robot, Direction direction);
        void request_drop(Robot &robot, Direction direction);
        void request_movement(Robot &robot, Direction direction);
        void update();

};

#endif
