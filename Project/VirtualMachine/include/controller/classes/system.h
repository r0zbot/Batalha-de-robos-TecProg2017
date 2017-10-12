//
// Created by Daniel on 12/10/2017.
//

#ifndef VIRTUALMACHINE_SYSTEM_H
#define VIRTUALMACHINE_SYSTEM_H

enum class SystemCode {
    MOVE = 1,
    COLLECT = 2,
    DROP = 3,
    ATTACKMELEE = 4,
    ATTACKSHORT = 5,
    ATTACKLONG = 6,
};

enum class Direction{
    NE = 1, NW = 2, E = 3, W = 4, SE = 5, SW = 6
};

#endif //VIRTUALMACHINE_SYSTEM_H
