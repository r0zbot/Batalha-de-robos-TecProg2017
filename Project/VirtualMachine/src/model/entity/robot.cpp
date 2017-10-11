#include <model/entity/robot.h>

#include <util/config.h>

Robot::Robot(int id, int posX, int posY, Program prog)
    : Entity(id, posX, posY), machine(prog, this) {
}

void Robot::replace_machine(const Program prog) {
    this->machine = Machine(prog, this);
}

void Robot::update() {
    this->machine.run(MACHINE_RUN_CYCLES);
}
