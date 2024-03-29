/**
 * @file  system.h
 * @brief This file stores enum classes that hold codes
 *        for operations realized in the system.
 */

#ifndef VIRTUALMACHINE_SYSCALL_H
#define VIRTUALMACHINE_SYSCALL_H

/**
 * @enum  Direction
 * @brief The <b>Direction</b> is a base enum that defines
 *        the six possible directions of movement in a
 *        pointy-topped hexagonal grid.
 */
enum Direction {
    NE  = 0, ///< Represents the direction Northeast
    NW  = 1, ///< Represents the direction Northwest
    EA  = 2, ///< Represents the direction East
    WE  = 3, ///< Represents the direction West
    SE  = 4, ///< Represents the direction Southeast
    SW  = 5, ///< Represents the direction Southwest
    CE  = 6  ///< Represents the center/current cell
};

/**
 * @enum  SystemCode
 * @brief The <b>SystemCode</b> is a strongly typed enum that
 *        defines operations codes for general actions.
 */
enum SystemCode {
    MOVE     = 1, ///< Represents the movement action
    COLLECT  = 2, ///< Represents the pick/grab action
    DROP     = 3, ///< Represents the deposit action
    ATKMELEE = 4, ///< Represents the melee attack action
    ATKSHORT = 5, ///< Represents the short attack action
    ATKLONG  = 6, ///< Represents the long attack action
    SEE      = 7  ///< Represents the see action
};

#endif
