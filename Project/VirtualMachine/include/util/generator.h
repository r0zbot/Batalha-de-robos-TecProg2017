/**
 * This file just initializes static variables
 * for entity classes. It MUST NOT be included in
 * any party of the project.
 */

#ifndef VIRTUALMACHINE_GENERATOR_H
#define VIRTUALMACHINE_GENERATOR_H

#include <model/entity/army.h>

#include <util/config.h>

int Entity::id_gen;
int Army::id_gen;

unsigned int Config::available_crystals         = 120;

unsigned int Config::machine_inventory_size           = 100;
unsigned int Config::machine_instructions_cycle = 50;
unsigned int Config::machine_health             = 100;
unsigned int Config::machine_melee_attack       = 20;
unsigned int Config::machine_short_attack       = 10;
unsigned int Config::machine_long_attack        = 10;

double Config::machine_fuel                     = 100;
double Config::machine_mov_fuel_usage           = 10;
double Config::machine_inst_fuel_usage          = 0.01;

unsigned int Config::max_crystals_per_cell      = 20;

#endif
