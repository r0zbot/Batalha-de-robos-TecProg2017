#include <iostream>

#include <concat.hpp>

#include <controller/classes/arena.h>

#include <util/config.h>
#include <util/log.h>

int Arena::create_robot(const int id, const Program &prog){
    //TODO: put this robot in the army's base
    return this->create_robot(id, Hex(0, this->last_pos++), prog);
}

int Arena::create_robot(const int id, const Hex &pos, const Program &prog) {
    auto it = this->ambient.find(pos);
    if (it == this->ambient.end()) {
        Log::error(concat("The position [", pos.get_row(), ",", pos.get_col(), "] is outside the play area"));
        return -1;
    }
    else if (it->get_occup() != -1) {
        Log::error(concat("There's already a robot in position [", pos.get_row(), ",", pos.get_col(), "]."));
        return -1;
    }

    EntityMovePtr soldier = make_shared<Machine>(prog, pos, "../../View/properties/soldier/soldier_" + to_string(id) + ".png");
    this->armies.at(id).insert_soldier(soldier);

    // The set stores a const Hex, so we need a non-const copy
    Hex newCell = *it;
    // Update the copy
    newCell.set_occup(soldier->get_id());

    // Remove the old one and add the updated one back to the set
    this->ambient.erase(newCell);
    this->ambient.insert(newCell);

    return soldier->get_id();
}

unsigned long long Arena::elapsed_time() const {
    return this->time;
}

EntityMove& Arena::find_entity_move(const int id) {
    for (auto &army : this->armies) {
        if (army.second.contains_soldier(id)) {
            return *army.second.get_soldier(id);
        }
    }
    Log::warn(concat("Robot: ", id, " is not part of any army!"));
}

Army& Arena::get_army(const int id) {
    return this->armies.at(id);
}

const Hex& Arena::get_cell(const Hex &pos) const {
    return *this->ambient.find(pos);
}

int Arena::get_height() const {
    return this->height;
}

int Arena::get_width() const {
    return this->width;
}

void Arena::import_terrain(const vector<vector<int>> &terrain) {
    this->height = (int) terrain.size();
    this->width  = (int) terrain[0].size();
    for (int i = 0; i < this->height; i++) {
        for (int j = 0; j < this->width; j++) {
            this->ambient.emplace(Hex(i, j, -1, -1, -1, static_cast<Terrain>(terrain[i][j])));
        }
    }
}

void Arena::insert_army(const Army &army) {
    this->armies.emplace(army.get_id(), army);
}

void Arena::load(const View &view) const {
    view.load(this->height, this->width);
    for (auto const &cell : this->ambient) {
        view.load(cell);
    }
    for (auto const &army : this->armies) {
        army.second.load(view);
    }
}

void Arena::print(const string &s) {
    cout << "Arena: " << s << '\n';
}

void Arena::print(const EntityMove &e) {
    cout << "Robot " << e.get_id() << ' ';
    if (e.get_group_id() != -1) {
        cout << "[" << this->armies.at(e.get_group_id()).get_name() << "]:\n";
    }
    else {
        cout << "[Orphan]:\n";
    }
}

void Arena::print(const string &s, const EntityMove &e) {
    this->print(e);
    cout << "\t" << s << '\n';
}

void Arena::print(const Operand &op, const EntityMove &e) {
    this->print(e);
    cout << "\tOperand " << op.info() << '\n';
}

void Arena::remove_army(const int id) {
    this->armies.erase(id);
}

void Arena::render(const View &view) {
    for (auto &army : this->armies) {
        army.second.render(view);
    }
}

void Arena::request_attack_melee(EntityMove &e, const Hex &pos) {
    this->find_entity_move(this->ambient.find(pos)->get_occup()).take_damage(e.get_dmg_melee());
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
    if (this->validate_insertion(pos, e)) {
        auto newPosIt = this->ambient.find(pos);
        Hex newPosHex = *newPosIt;
        if (e.remove_crystal()) {
            if (newPosHex.insert_crystal()) {
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
        auto oldPosIt = this->ambient.find(Hex(e.get_row(), e.get_col()));
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

void Arena::update(const View &view) {
    for (auto &army : this->armies) {
        army.second.update();
    }
    ++this->time;
}

bool Arena::validate_insertion(const Hex &pos, EntityMove &e) {
    auto it = this->ambient.find(pos);
    if (it == this->ambient.end()) {
        this->print(concat("The position [", pos.get_row(), ",", pos.get_col(), "] is outside the play area"), e);
        return false;
    }
    else if (it->get_occup() != -1) {
        this->print(concat("There's already a robot in position [", pos.get_row(), ",", pos.get_col(), "]."), e);
        return false;
    }
    else if (it->get_terrain() == Terrain::ROCK){
        this->print(concat("Can't go to [", pos.get_row(), ",", pos.get_col(), "]. There is a rock there!"), e);
        return false;
    }
    return true;
}
