#include <controller/classes/arena.h>

Arena::Arena() {

}

unsigned long long Arena::elapsed_time() const {
    return this->time * SLEEP_TIME;
}

void Arena::insert_army(const Army &army) {
    this->armies.emplace(army.get_id(), army);
}

void Arena::remove_army(const int id) {
    this->armies.erase(id);
}

void Arena::request_attack_melee(const EntityMove &e, const Hex &pos){

}

void Arena::request_attack_short(const EntityMove &e, const Hex &pos) {

}

void Arena::request_attack_long(const EntityMove &e, const Hex &pos) {

}

void Arena::request_collect(const EntityMove &e, const Hex &pos) {

}

void Arena::request_drop(const EntityMove &e, const Hex &pos) {

}

void Arena::request_movement(const EntityMove &e, const Hex &pos) {

}

void Arena::update() {
    for (auto &army : this->armies) {
        army.second.update();
    }
    ++this->time;
}
