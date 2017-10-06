#ifndef VIRTUALMACHINE_ARENA_H
#define VIRTUALMACHINE_ARENA_H

#include "config.h"
#include "machine.h"
#include <map>

using namespace std;

class Arena{
    private:
        map<int, Machine> machine;
        int arena_space[ARENA_HEIGHT][ARENA_WIDTH];
};

#endif
