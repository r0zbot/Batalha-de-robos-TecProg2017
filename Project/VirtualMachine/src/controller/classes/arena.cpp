#include <iostream>

#include <concat.hpp>

#include <controller/classes/arena.h>

#include <util/config.h>
#include <util/log.h>

Arena::Arena() {
    // Initialize the Arena Grid with random contents
    for (int i = 0; i < ARENA_WIDTH; i++) {
        for (int j = 0; j < ARENA_HEIGHT; j++) {
            this->ambient.emplace(
                    Hex(i, j, -1, -1,
                        rand() % MAX_CRYSTALS_PER_CELL,
                        static_cast<Terrain>(rand() % 3)));
        }
    }
}


int Arena::create_robot(const int id, const Hex &pos, Program &prog) {
    auto it = this->ambient.find(pos);
    if (it == this->ambient.end()) {
        Log::error(concat("The position [",pos.get_row(),",",pos.get_col(),"] is outside the play area"));
        return -1;
    }
    else if(it->get_occup() != -1){
        Log::error(concat("There's already a robot in position [",pos.get_row(),",",pos.get_col(),"]."));
        return -1;
    }

    auto *machine = new Machine(prog, pos);
    this->armies.at(id).insert_soldier(machine);
    //the set stores a const Hex, so we need a non-const copy
    Hex newCell = *it;
    //Update the copy
    newCell.set_occup(machine->get_id());
    //Remove the old one and add the updated one back to the set
    this->ambient.erase(newCell);
    this->ambient.insert(newCell);
    return machine->get_id();
}

unsigned long long Arena::elapsed_time() const {
    return this->time * ARENA_SLEEP_TIME;
}

Army& Arena::get_army(int id) {
    return this->armies.at(id);
}

Hex& Arena::get_cell(const Hex &pos) const {
    Hex cell = *this->ambient.find(pos);
    return cell;
}

void Arena::insert_army(const Army &army) {
    this->armies.emplace(army.get_id(), army);
}

void Arena::print(const string &s) {
    cout << "\nArena: " << s << '\n';
}

void Arena::print(const EntityMove &e) {
    cout << "\nRobot: " << e.get_id() << '\n';
    if (e.get_group_id() != -1) {
        cout << "Army: " << this->armies.at(e.get_group_id()).get_name() << '\n';
    }
    else {
        cout << "Army: None" << '\n';
    }
}

void Arena::print(const string &s, const EntityMove &e) {
    this->print(e);
    cout << "Message: " << s << '\n';
}

void Arena::print(const Operand &op, const EntityMove &e) {
    this->print(e);
    cout << "Operand " << op.prn() << '\n';
}

void Arena::remove_army(const int id) {
    this->armies.erase(id);
}

void Arena::request_attack_melee(EntityMove &e, const Hex &pos){
    this->find_entity_move(this->ambient.find(pos)->get_occup()).take_damage(ATTACK_LONG_DAMAGE);
}

void Arena::request_attack_short(EntityMove &e, const Hex &pos) {
    //TODO Implement Hex ranged-neighbors
}

void Arena::request_attack_long(EntityMove &e, const Hex &pos) {
    //TODO Implement Hex ranged-neighbors
}

void Arena::request_collect(EntityMove &e, const Hex &pos) {
    if (Log::LOGGING_LEVEL == Log::DEBUG) {
        this->print(concat("Robot ", e.get_id(), " collecting from [", pos.get_row(), ", ", pos.get_col(), "]"));
    }
    if (this->validate_insertion(pos, e)) {
        auto newPosIt = this->ambient.find(pos);
        Hex newPosHex = *newPosIt;
        if (newPosHex.remove_crystal()) {
            if (e.insert_crystal()) {
                this->print(concat("Robot ", e.get_id(), " now has ", e.get_crystals(), " crystals."));
                this->ambient.erase(newPosIt);
                this->ambient.insert(newPosHex);
            }
        }
    }
}

void Arena::request_drop(EntityMove &e, const Hex &pos) {
    if (Log::LOGGING_LEVEL == Log::DEBUG) {
        this->print(concat("Robot ", e.get_id(), " dropping in [", pos.get_row(), ", ", pos.get_col(), "]"));
    }
    if(this->validate_insertion(pos, e)){
        auto newPosIt = this->ambient.find(pos);
        Hex newPosHex = *newPosIt;
        if(e.remove_crystal()){
            if(newPosHex.insert_crystal()) {
                this->print(concat("Robot ", e.get_id(), " now has ", e.get_crystals(), " crystals."));
                this->ambient.erase(newPosIt);
                this->ambient.insert(newPosHex);
            }
            else {
                //Forgets about it and gives the crystals back to the Entity.
                e.insert_crystal();
            }
        }
    }
}

void Arena::request_movement(EntityMove &e, const Hex &pos) {
    if (Log::LOGGING_LEVEL == Log::DEBUG) {
        this->print(concat("Robot ", e.get_id(), " moving to [", pos.get_row(), ", ", pos.get_col(), "]"));
    }
    if (this->validate_insertion(pos, e)) {
        auto oldPosIt = this->ambient.find(Hex(e.get_x(), e.get_y()));
        auto newPosIt = this->ambient.find(pos);
        Hex oldPosHex = *oldPosIt;
        Hex newPosHex = *newPosIt;
        oldPosHex.set_occup(-1);
        newPosHex.set_occup(e.get_id());
        e.set_position(newPosHex);
        this->ambient.erase(oldPosIt);
        this->ambient.insert(oldPosHex);
        this->ambient.erase(newPosIt);
        this->ambient.insert(newPosHex);
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

EntityMove& Arena::find_entity_move(int id) {
    for(auto army : this->armies){
        if(army.second.contains_soldier(id)){
            return *army.second.get_soldier(id);
        }
    }
    Log::error(concat("Robot: ",id, " is not part of any army!"));
}
