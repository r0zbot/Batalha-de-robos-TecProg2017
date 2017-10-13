#ifndef VIRTUALMACHINE_ROBOT_H
#define VIRTUALMACHINE_ROBOT_H

#include <controller/classes/machine.h>

#include <model/interface/entity.h>

class Army;

class Robot: public Entity {
    private:
        Machine machine;
        int crystals = 0;
        int hp = 100;
        int hpCapacity = 100;

        double fuel = 100.0;
        double fuelCapacity = 100.0;
    public:
        Robot(int id, int posX, int posY, Program prog);
        void clear_crystals();
        int get_crystals();
        int get_hp();
        double get_fuel();
        Machine &get_machine();
        void heal(unsigned int amount);
        void insert_crystals(unsigned int amount);
        void refuel(double amount);
        void replace_machine(Program prog);
        void update() override;
        bool use_fuel(double amount);
};
#endif