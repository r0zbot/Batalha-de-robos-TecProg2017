// Move this file to /VirtualMachine/src so this can work on production

#include <vector>

#include <controller/classes/code.h>
#include <controller/classes/action.h>
#include <controller/classes/number.h>
#include <controller/classes/instruction.h>

#include <model/entity/machine.h>
#include <util/globals.h>
#include <util/sleep.h>

using namespace std;

//Global variables and settings
Arena arena;
int lastRobotPos = 0;
int availableCrystals = 120;
unsigned int robotHealth = 100;
int arenaSleepTime = 1000;
double robotFuel = 100;
int robotMeleeAttack = 20;
int maxCrystalsPerCell = 20;
double robotMovFuelUsage = 1.5;
int machineInstructionsPerCycle = 50;
double robotInstFuelUsage = 0.01;

int main() {
    int terrain[10][20] = {
        {3, 1, 2, 2, 0, 0, 4, 2, 0, 1, 3, 3, 4, 4, 3, 2, 3, 0, 0, 0}, 
        {1, 4, 1, 2, 2, 2, 2, 4, 1, 4, 4, 4, 2, 0, 2, 4, 4, 2, 3, 2}, 
        {4, 0, 1, 4, 1, 0, 3, 1, 3, 2, 0, 2, 4, 1, 3, 0, 2, 2, 1, 3}, 
        {4, 0, 3, 1, 4, 1, 4, 2, 1, 0, 2, 2, 1, 1, 2, 0, 0, 4, 4, 1}, 
        {4, 2, 2, 2, 0, 3, 0, 1, 2, 1, 1, 1, 2, 0, 4, 4, 0, 2, 0, 0}, 
        {2, 0, 1, 0, 3, 4, 2, 4, 0, 0, 4, 0, 1, 3, 0, 0, 2, 2, 3, 0}, 
        {3, 4, 2, 0, 0, 3, 1, 4, 4, 3, 4, 1, 3, 4, 2, 3, 2, 0, 4, 1}, 
        {1, 2, 2, 1, 4, 1, 2, 4, 1, 2, 3, 3, 0, 0, 1, 0, 0, 4, 3, 1}, 
        {2, 0, 0, 1, 4, 4, 1, 4, 1, 3, 0, 2, 3, 2, 2, 3, 3, 0, 1, 1}, 
        {1, 0, 1, 4, 0, 1, 2, 1, 4, 3, 3, 4, 0, 4, 0, 0, 0, 3, 0, 3}, 
    }
	arena.import_terrain(terrain);

	Army army1("Army 1");
	arena.insert_army(army1);

	Army army2("Army 2");
	arena.insert_army(army2);
	while(true){
		arena.update();
		arena_sleep(arenaSleepTime);
	}
}

