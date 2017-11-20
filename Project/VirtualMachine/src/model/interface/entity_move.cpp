#include <algorithm>

#include <model/interface/entity_move.h>
#include <util/config.h>
#include <util/globals.h>

EntityMove::EntityMove(
        const Hex &pos,
        const string &image_path,
        const double fuel_capacity,
        const unsigned int inventory_size,
        const unsigned int hp_capacity,
        const unsigned int dmg_melee_atk,
        const unsigned int dmg_short_atk,
        const unsigned int dmg_long_atk)
    : crystals(0),
      dmg_melee_atk(dmg_melee_atk),
      dmg_short_atk(dmg_short_atk),
      dmg_long_atk(dmg_long_atk),
      fuel(fuel_capacity),
      fuel_capacity(fuel_capacity),
      group_id(-1),
      hp(hp_capacity),
      hp_capacity(hp_capacity),
      inventory_size(inventory_size),
      Entity(pos, image_path) {}

void EntityMove::clear_crystals() {
    this->crystals = 0;
}

int EntityMove::get_crystals() const {
    return this->crystals;
}

unsigned int EntityMove::get_dmg_melee() const {
    return this->dmg_melee_atk;
}

unsigned int EntityMove::get_dmg_short() const {
    return this->dmg_short_atk;
}

unsigned int EntityMove::get_dmg_long() const {
    return this->dmg_long_atk;
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
    if (this->crystals < this->inventory_size) {
        ++this->crystals;
        return true;
    }
    return false;
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
    return false;
}

void EntityMove::set_group_id(const int group_id) {
    this->group_id = group_id;
}

void EntityMove::take_damage(const int damage) {
    this->hp = max(0, this->hp - damage);
    if(this->hp <= 0 ){
        arena.die(*this);
    }
}

bool EntityMove::use_fuel(const double quantity) {
    if (this->fuel >= quantity) {
        this->fuel -= quantity;
        return true;
    }
    return false;
}
