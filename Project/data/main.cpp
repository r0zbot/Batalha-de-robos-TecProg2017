// Move this file to /VirtualMachine/src so this can work on production

#include <vector>

#include <controller/classes/code.h>
#include <controller/classes/action.h>
#include <controller/classes/number.h>
#include <controller/classes/instruction.h>

#include <model/entity/machine.h>
#include <util/globals.h>
#include <thread>

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

