#ifndef VIRTUALMACHINE_CONFIG_H
#define VIRTUALMACHINE_CONFIG_H

/**
 * @file config.h
 *
 * @brief Configuration for global parameters for the project.
 *
 * This file sets global values for settings used throughout the project.
 * Centralization is a good thing in this case, as it makes making
 * configuration changes a lot easier.
 */

//TODO: Redefine this variables here.

#define LOGGING_LEVEL DEBUG ///< The currently Logging Level being used in the system.

#define ARENA_HEIGHT     100 ///< The {@link #Arena} max height.
#define ARENA_WIDTH      100 ///< The {@link #Arena} max width.
#define ARENA_SLEEP_TIME 300 ///< The system sleep time in milliseconds

#define ATTACK_MELEE_DAMAGE 15 ///< Damage inflicted by a melle attack.
#define ATTACK_SHORT_DAMAGE 10 ///< Damage inflicted by a short range attack.
#define ATTACK_LONG_DAMAGE  20 ///< Damage inflicted by a long range attack.

#define FUEL_PER_INSTRUCTION         0.01 ///< Quantity of fuel used during the execution of one instruction.
#define MACHINES_PER_ARMY            100  ///< Max amount of {@link #Machine} per {@link #Army}.
#define MACHINE_EXECUTION_STACK_SIZE 600  ///< The execution stack size in a {@link #Machine}.
#define MACHINE_MEMORY_SIZE          200  ///< The memory size in a {@link #Machine}.
#define MACHINE_RUN_CYCLES           50   ///< Number of cycles that a {@link #Machine} can execute in a single operation.

#define MAX_ARMY_AMOUNT        10  ///< Max amount of {@link #Army} per game.
#define MAX_CRYSTALS_PER_CELL  20  ///< Max amount of crystals per grid cell.
#define MAX_CRYSTALS_PER_ROBOT 100 ///< Max amount of crystals that a robot can carry.

#endif
