#include <model/entity/robot.h>

#include <util/config.h>

Robot::Robot(const int id,const int posX,const int posY, Program prog)
    : Entity(id, posX, posY), machine(prog, this) {

}

void Robot::clear_crystals() {
    this->crystals = 0;
}

int Robot::get_crystals() {
    return this->crystals;
}

double Robot::get_fuel() {
    return this->fuel;
}

int Robot::get_hp() {
    return this->hp;
}

void Robot::heal(const unsigned int amount) {
    if(amount > this->hpCapacity){
        this->hp = this->hpCapacity;
    }
    else{
        this->hp = amount;
    }
}

void Robot::insert_crystals(const unsigned int amount) {
    this->crystals += amount;
}

void Robot::refuel(const double amount) {
    if(amount > this->fuelCapacity){
        this->fuel = this->fuelCapacity;
    }
    else{
        this->fuel += amount;
    }
}

void Robot::replace_machine(const Program prog) {
    this->machine = Machine(prog, this);
}

void Robot::update() {
    this->machine.run(MACHINE_RUN_CYCLES);
}

bool Robot::use_fuel(double amount) {
    if(this->fuel > 0 && this->fuel > amount){
        this->fuel -= amount;
        return true;
    }
    else{
        return false;
    }
}
