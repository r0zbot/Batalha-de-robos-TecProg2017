#include <controller/classes/arena.h>
#include <util/config.h>
#include <concat.hpp>
#include <util/log.h>

Arena::Arena() {
    for(int i=0; i<ARENA_HEIGHT; i++){
        for(int j=0; j<ARENA_WIDTH; j++){
            //TODO: initalize using a terrain file, or at least initialize different terrain types
            this->ambient.emplace(Hex(i, j));
        }
    }
}


int Arena::create_robot(Army &army, Hex pos, Program prog) {
    unordered_set<Hex>::iterator it = this->ambient.find(pos);
    if(it == this->ambient.end()){
        Log::error(concat("The position [",pos.get_row(),",",pos.get_col(),"] is outside the play area"));
        return -1;
    }
    else if(it->get_occup() != -1){
        Log::error(concat("There's already a robot in position [",pos.get_row(),",",pos.get_col(),"]."));
        return -1;
    }

    auto *machine = new Machine(prog, pos);
    army.instert_soldier(machine);
    //it returns a const Hex, so we need a non-const copy
    Hex newCell = *it;
    //Update the copy
    newCell.set_occup(machine->get_id());
    //Remove it and add it back to the set
    this->ambient.erase(it);
    this->ambient.insert(newCell);
    return machine->get_id();
}

Army & Arena::get_army(int id) {
    return this->armies.at(id);
}

unsigned long long Arena::elapsed_time() const {
    return this->time * ARENA_SLEEP_TIME;
}

void Arena::insert_army(const Army &army) {
    this->armies.emplace(army.get_id(), army);
}

void Arena::print(const string &s) {
    printf("Arena: %s",s.c_str());
}

void Arena::print(const string &s, EntityMove &robot) {
    printf("Robot %i (Army %s): %s\n", robot.get_id(), this->get_army(robot.get_group_id()).get_name().c_str(), s.c_str());
}

void Arena::print(const int n, EntityMove &robot) {
    this->print(to_string(n), robot);
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
