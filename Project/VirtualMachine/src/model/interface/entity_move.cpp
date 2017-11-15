#include <algorithm>

#include <model/interface/entity_move.h>
#include <util/config.h>

EntityMove::EntityMove(
        const Hex &pos,
        const string &image_path,
        const double fuel_capacity,
        const unsigned int hp_capacity)
    : crystals(0),
      fuel(fuel_capacity),
      fuel_capacity(fuel_capacity),
      group_id(-1),
      hp(hp_capacity),
      hp_capacity(hp_capacity),
      Entity(pos, image_path) {}

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

bool EntityMove::insert_crystal() {
    if (this->crystals < MAX_CRYSTALS_PER_ROBOT) {
        ++this->crystals;
        return true;
    }
    else {
        return false;
    }
}

void EntityMove::refuel(const double amount) {
    if (amount > 0) {
        this->fuel = min(this->fuel + amount, this->fuel_capacity);
    }
}

bool EntityMove::remove_crystal() {
    if (this->crystals > 0) {
        --this->crystals;
        return true;
    }
    else {
        return false;
    }
}

void EntityMove::set_group_id(const int group_id) {
    this->group_id = group_id;
}

void EntityMove::take_damage(const int damage) {
    this->hp = max(0, this->hp - damage);
    //TODO die if 0?
}

bool EntityMove::use_fuel(const double amount) {
    if (amount > 0 && this->fuel >= amount) {
        this->fuel -= amount;
        return true;
    }
    else {
        return false;
    }
}
