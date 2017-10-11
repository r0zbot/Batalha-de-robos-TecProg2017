#include <model/entity/robot.h>

#include <util/config.h>

Robot::Robot(const int id,const int posX,const int posY, Program prog)
    : Entity(id, posX, posY), machine(prog, this) {

}

void Robot::clear_crystals() {
    this->crystals = 0;
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
