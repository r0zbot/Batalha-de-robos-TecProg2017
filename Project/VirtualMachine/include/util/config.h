#ifndef VIRTUALMACHINE_CONFIG_H
#define VIRTUALMACHINE_CONFIG_H

/**
 * @file config.h
 *
 * @brief Configuration for global parameters for the project.
 *
 * This file sets global values for settings used throughout the project.
 *
 */

//TODO better documentation
#define LOGGING_LEVEL DEBUG


//TODO Redefine this variables here!!!
//Centralization is a good thing in this case, as it makes making configuration changes a lot easier.
#define ARENA_HEIGHT 10
#define ARENA_WIDTH 10
#define ARENA_SLEEP_TIME 300 //In milliseconds
#define ATTACK_MELEE_DAMAGE 15
#define ATTACK_SHORT_DAMAGE 10
#define ATTACK_LONG_DAMAGE 20
#define FUEL_PER_INSTRUCTION 0.01
#define MACHINES_PER_ARMY 100
#define MACHINE_EXECUTION_STACK_SIZE 600
#define MACHINE_MEMORY_SIZE 200
#define MACHINE_RUN_CYCLES 100 // Número de ciclos que cada maquina pode executar de uma só vez
#define MAX_ARMY_AMOUNT 10
#define MAX_CRYSTALS_PER_CELL 20
#define MAX_CRYSTALS_PER_ROBOT 100

#endif
