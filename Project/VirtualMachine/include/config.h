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

//TODO documentar melhor
#define LOGGING_LEVEL DEBUG

#define ARENA_HEIGHT 300
#define ARENA_SLEEP_TIME 100 //In milliseconds
#define ARENA_WIDTH 300
#define MACHINE_EXECUTION_STACK_SIZE 600
#define MACHINE_MEMORY_SIZE 200
#define MACHINE_RUN_CYCLES 50 // Número de ciclos que a maquina pode executar de uma só vez
#define MACHINES_AMOUNT 100

typedef unsigned long long int longlong;
#endif
