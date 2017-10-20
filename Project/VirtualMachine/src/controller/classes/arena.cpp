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
    auto it = this->ambient.find(pos);
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
    //the iterator returns a const Hex, so we need a non-const copy
    Hex newCell = *it;
    //Update the copy
    newCell.set_occup(machine->get_id());
    //Remove it and add it back to the set
    this->ambient.erase(it);
    this->ambient.insert(newCell);
    //it->set_occup(machine->get_id());
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

void Arena::print(const string &s, EntityMove &e) {
    printf("Robot %i (Army %s): %s\n", e.get_id(), this->get_army(e.get_group_id()).get_name().c_str(), s.c_str());
}

void Arena::print(const int n, EntityMove &e) {
    this->print(to_string(n), e);
}

void Arena::remove_army(const int id) {
    this->armies.erase(id);
}

void Arena::request_attack_melee(EntityMove &e, const Hex &pos){

}

void Arena::request_attack_short(EntityMove &e, const Hex &pos) {

}

void Arena::request_attack_long(EntityMove &e, const Hex &pos) {

}

void Arena::request_collect(EntityMove &e, const Hex &pos) {

}

void Arena::request_drop(EntityMove &e, const Hex &pos) {

}

void Arena::request_movement(EntityMove &e, const Hex &pos) {
    if(this->validate_insertion(pos, e)){
        //the iterator returns a const Hex, so we need a non-const copy
        //Hex newCell = *it;
        //Update the copy
        //newCell.set_occup(machine->get_id());
        //Remove it and add it back to the set
        //this->ambient.erase(it);
        //this->ambient.insert(newCell);
        //TODO vou fazer isso em breve, mas sinta se a vontade
    }
}

void Arena::update() {
    for (auto &army : this->armies) {
        army.second.update();
    }
    ++this->time;
}

bool Arena::validate_insertion(Hex pos, EntityMove &e) {
    auto it = this->ambient.find(pos);
    if(it == this->ambient.end()){
        this->print(concat("The position [",pos.get_row(),",",pos.get_col(),"] is outside the play area"), e);
        return false;
    }
    else if(it->get_occup() != -1){
        this->print(concat("There's already a robot in position [",pos.get_row(),",",pos.get_col(),"]."), e);
        return false;
    }
    return true;
}

void Arena::replace_hex(const Hex hex) {
    this->ambient.erase(this->ambient.find(hex));
    this->ambient.insert(hex);
}
