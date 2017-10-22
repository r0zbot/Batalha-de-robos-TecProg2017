/**
 * @file  system.h
 * @brief This file stores enum classes that hold codes
 *        for operations realized in the system.
 */

#ifndef VIRTUALMACHINE_SYSTEM_H
#define VIRTUALMACHINE_SYSTEM_H

/**
 * @enum  Direction
 * @brief The <b>Direction</b> is a base enum that defines
 *        the six possible directions of movement in a
 *        flat-topped hexagonal grid.
 */
enum Direction {
    NE = 0, ///< Represents the direction Northeast
    N  = 1, ///< Represents the direction North
    NW = 2, ///< Represents the direction Northwest
    SE = 3, ///< Represents the direction Southeast
    S  = 4, ///< Represents the direction South
    SW = 5  ///< Represents the direction Southwest
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
    ATKLONG  = 6,  ///< Represents the long attack action
    SEE      = 7
};

#endif
