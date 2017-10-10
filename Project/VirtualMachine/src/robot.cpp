#include <robot.h>
#include <config.h>

Robot::Robot(int id, int posX, int posY, Program prog)
    : Entity(id, posX, posY), machine(prog){

}

void Robot::replace_machine(const Program prog) {
    this->machine = Machine(prog);
}

void Robot::update() {
    this->machine.run(MACHINE_RUN_CYCLES);
}
