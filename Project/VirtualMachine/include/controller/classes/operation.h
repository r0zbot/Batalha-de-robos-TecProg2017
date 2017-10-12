/**
 * @file operation.h
 * @brief This file stores enum classes that represents codes
 *        for operations realized in the system.
 */

#ifndef VIRTUALMACHINE_OPERATION_H
#define VIRTUALMACHINE_OPERATION_H

/**
 * @enum Action
 * @brief The <b>Action</b> is a strongly typed enum that
 *        defines operations codes for general actions.
 */
enum class Action {
    ATCK, ///< Represents the attack action
    DEPT, ///< Represents the deposit action
    MOVE, ///< Represents the movement action
    PICK  ///< Represents the pick/grab action
};

/**
 * @enum Direction
 * @brief The <b>Direction</b> is a basic enum that
 *        defines the six possible directions of movement
 *        in a flat-topped hexagonal grid.
 */
enum Direction {
    N_EAST = 0, ///< Represents the direction Northeast
    NORTH  = 1, ///< Represents the direction North
    N_WEST = 2, ///< Represents the direction Northwest
    S_EAST = 3, ///< Represents the direction Southeast
    SOUTH  = 4, ///< Represents the direction South
    S_WEST = 5  ///< Represents the direction Southwest
};

#endif
