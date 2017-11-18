#ifndef VIRTUALMACHINE_CONFIG_H
#define VIRTUALMACHINE_CONFIG_H

/**
 * @file config.h
 *
 * @brief Configuration for global parameters for the project.
 *
 * This file sets global values for settings used throughout the project.
 */

//TODO: Redefine this variables here.

#define LOGGING_LEVEL DEBUG ///< The currently Logging Level being used in the system.

#define MACHINE_EXECUTION_STACK_SIZE 600  ///< The execution stack size in a {@link #Machine}.
#define MACHINE_MEMORY_SIZE          200  ///< The memory size in a {@link #Machine}.

#define MAX_CRYSTALS_PER_ROBOT 100 ///< Max amount of crystals that a robot can carry.

/// These properties below are set in main.cpp, which is generated by the manager/builder

extern int lastRobotPos; //TODO: remove this after implementing army bases

extern int availableCrystals;     ///< The amount of crystals available to be spread through all the cells
extern int maxCrystalsPerCell;    ///< The maximum amount of crystals a single cell can hold
extern int game_sleep_time;             ///< The system sleep time in milliseconds

extern int machineInstructionsPerCycle;    ///< Number of cycles that a {@link #Machine} can execute in a single operation.

extern int robotMeleeAttack;      ///< Damage inflicted by a melee attack.
extern int robotShortAttack;      ///< Damage inflicted by a short range attack.
extern int robotLongAttack;       ///< Damage inflicted by a long range attack.

extern unsigned int robotHealth;  ///< Initial health capacity of robots

extern double robotFuel;          ///< Amount of fuel an {@link #EntityMove} can hold
extern double robotMovFuelUsage;  ///< Amount of fuel an {@link #EntityMove} uses to move to the next cell
extern double robotInstFuelUsage; ///< Quantity of fuel used during the execution of one instruction.

#endif
