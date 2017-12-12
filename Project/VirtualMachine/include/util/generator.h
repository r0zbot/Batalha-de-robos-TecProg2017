/**
 * This file just initializes static variables
 * for entity classes. It MUST NOT be included in
 * any party of the project.
 */

#ifndef VIRTUALMACHINE_GENERATOR_H
#define VIRTUALMACHINE_GENERATOR_H

#include <model/entity/army.h>

#include <util/config.h>
#include <controller/classes/arena.h>

int Entity::id_gen;
int Army::id_gen;


/// These defaults should NEVER be used!
unsigned int Config::available_crystals         = 0;

unsigned int Config::machine_inventory_size     = 100; //Except for this one
unsigned int Config::machine_instructions_cycle = 0;
unsigned int Config::machine_health             = 0;
unsigned int Config::machine_melee_attack       = 0;
unsigned int Config::machine_short_attack       = 0;
unsigned int Config::machine_long_attack        = 0;

double Config::machine_fuel                     = -1;
double Config::machine_mov_fuel_usage           = -1;
double Config::machine_inst_fuel_usage          = -1;

unsigned int Config::max_crystals_per_cell      = 0;

Arena arena;
#endif
