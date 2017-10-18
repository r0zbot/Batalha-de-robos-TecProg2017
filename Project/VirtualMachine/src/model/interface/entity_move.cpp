#include <algorithm>

#include <model/interface/entity_move.h>

EntityMove::EntityMove(
        const Hex &pos,
        const double fuel_capacity,
        const unsigned int hp_capacity)
    : crystals(0),
      fuel(fuel_capacity),
      fuel_capacity(fuel_capacity),
      group_id(-1),
      hp(hp_capacity),
      hp_capacity(hp_capacity),
      Entity(pos) {}

void EntityMove::clear_crystals() {
    this->crystals = 0;
}

int EntityMove::get_crystals() const {
    return this->crystals;
}

double EntityMove::get_fuel() const {
    return this->fuel;
}

int EntityMove::get_group_id() const {
    return this->group_id;
}

int EntityMove::get_hp() const {
    return this->hp;
}

void EntityMove::heal(const unsigned int amount) {
    this->hp = min(this->hp + amount, this->hp_capacity);
}

void EntityMove::insert_crystals(const unsigned int amount) {
    this->crystals += amount;
}

void EntityMove::refuel(const double amount) {
    if (amount > 0) {
        this->fuel = min(this->fuel + amount, this->fuel_capacity);
    }
}

void EntityMove::set_group_id(const int group_id) {
    this->group_id = group_id;
}

bool EntityMove::use_fuel(const double amount) {
    if (amount > 0 && this->fuel >= amount) {
        this->fuel -= amount;
        return true;
    }
    return false;
}
