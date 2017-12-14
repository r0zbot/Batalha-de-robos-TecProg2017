#include <iostream>

#include <concat.hpp>

#include <controller/classes/arena.h>

#include <util/config.h>
#include <util/log.h>
#include <controller/classes/core.h>



int Arena::create_robot(const int id, const Program &prog){
    //put this robot in the army's base
    for (auto &cell : this->ambient) {
        if (cell.get_base() == id  &&
            cell.get_occup() == -1 &&
            cell.get_terrain() != Terrain::ROCK) {
                this->create_robot(id, cell, prog);
                return 0;
        }
    }
    // If all the bases are occupied:
    // Get any base cell
    Hex base_cell(0, 0);
    for (auto &cell : this->ambient) {
        if (cell.get_base() == id) {
            base_cell = cell;
        }
    }

    // Try to put it in a range from that cell as close as possible
    // outside of enemy bases
    for (int i = 0; i < this->get_height() || i < this->get_width(); ++i) {
        for (auto &cell : base_cell.range(i)) {
            if (cell.get_col() >= 0 && cell.get_col() < this->get_width()) {
                if (cell.get_row() >= 0 && cell.get_row() < this->get_height()) {
                    auto current_cell = this->ambient.find(cell);
                    if (current_cell->get_base() == -1  &&
                            current_cell->get_occup() == -1 &&
                            current_cell->get_terrain() != Terrain::ROCK) {
                        this->create_robot(id, cell, prog);
                        return 0;
                    }
                }
            }
        }
    }
    Log::warn("Can't put new robot. Arena is full!");
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

    EntityMovePtr soldier = make_shared<Machine>(prog, pos, Core::get_soldier_image_path(id));
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

void Arena::die(EntityMove &e) {
    auto cell = this->ambient.find(Hex(e.get_row(), e.get_col()));
    Hex new_cell = *cell;
    new_cell.set_occup(-1);
    e.set_position(Hex(-1, -1));
    this->ambient.erase(cell);
    this->ambient.insert(new_cell);
    this->print("I died =(", e);
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

void Arena::generate_crystals(int crystals) {
    while(crystals > 0){
        auto cell = this->ambient.find(Hex(rand() % this->get_height(), rand() % this->get_width()));
        Hex aux_cell = *cell;
        int crystalsToAdd = min(crystals, min((int)Config::max_crystals_per_cell - aux_cell.get_crystals(), rand() % 5 ));
        crystals -= crystalsToAdd;
        aux_cell.set_crystals(aux_cell.get_crystals() + crystalsToAdd);
        this->ambient.erase(cell);
        this->ambient.insert(aux_cell);
    }
}

Army& Arena::get_army(const int id) {
    return this->armies.at(id);
}

const Hex& Arena::get_cell(const Hex &pos) const {
    if (pos.get_col() >= 0 && pos.get_col() < this->get_width() && pos.get_row() >= 0 && pos.get_row() < this->get_height()){
        return *this->ambient.find(pos);
    }
    else{
        return * new Hex(-1, -1, -1, -1, 0, Terrain::ROCK);
    }
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
            this->ambient.emplace(Hex(i, j, -1, -1, 0, static_cast<Terrain>(terrain[i][j])));
        }
    }
    this->generate_crystals(Config::available_crystals);
}

void Arena::insert_army(const Army &army) {
    auto center_base = this->ambient.find(Hex(this->current_center_row, this->current_center_col));
    Hex aux_center = *center_base;
    aux_center.set_base(army.get_id());
    this->ambient.erase(center_base);
    this->ambient.insert(aux_center);

    for (auto &cell : center_base->range(1)) {
        if (cell.get_col() >= 0 && cell.get_col() < this->get_width()) {
            if (cell.get_row() >= 0 && cell.get_row() < this->get_height()) {
                auto newCell = this->ambient.find(cell);
                Hex newPosCell = *newCell;
                newPosCell.set_base(army.get_id());
                newPosCell.set_crystals(0);
                this->ambient.erase(newCell);
                this->ambient.insert(newPosCell);
            }
        }
    }

    this->armies.emplace(army.get_id(), army);

    if (this->current_center_col + 4 > this->get_width()) {
        this->current_center_col = 1;
        this->current_center_row = this->get_height() - 2;
    }
    else {
        this->current_center_col += 4;
    }
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
        cout << "(" << this->armies.at(e.get_group_id()).get_name() << ") says:\n";
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
    cout << "\t" << op.info() << '\n';
}

void Arena::remove_army(const int id) {
    this->armies.erase(id);
}

void Arena::render(const View &view) {
    while(this->updated_cells.size() > 0){
        view.load(this->updated_cells.front());
        this->updated_cells.pop();
    }
    for (auto &army : this->armies) {
        army.second.render(view);
    }
}

bool Arena::request_attack_melee(EntityMove &e, const Hex &pos) {
    if (pos.get_col() >= 0 && pos.get_col() < this->get_width() && pos.get_row() >= 0 && pos.get_row() < this->get_height()){
        if(this->ambient.find(pos)->get_occup() != -1){
            this->find_entity_move(this->ambient.find(pos)->get_occup()).take_damage(e.get_dmg_melee());
            this->print(concat("Attacking robot at [", pos.get_row(), ",", pos.get_col() ,"]"), e);
            return true;
        }
        else{
            //this->print(concat("Attacking nothing at [", pos.get_row(), ",", pos.get_col() ,"]"), e);
        }
    }
    else{
        //this->print(concat("Attacking out of bounds at [", pos.get_row(), ",", pos.get_col() ,"]"), e);
    }
    return false;
}

bool Arena::request_attack_short(EntityMove &e, const Hex &pos) {
    //TODO Implement Hex ranged-neighbors
    return false;
}

bool Arena::request_attack_long(EntityMove &e, const Hex &pos) {
    //TODO Implement Hex ranged-neighbors
    return false;
}

bool Arena::request_collect(EntityMove &e, const Hex &pos) {
    if (Log::LOGGING_LEVEL == Log::DEBUG) {
        this->print(concat("Robot ", e.get_id(), " trying to collect from [", pos.get_row(), ", ", pos.get_col(), "]..."));
    }
    if (this->validate_position(pos, e)) {
        auto newPosIt = this->ambient.find(pos);
        Hex newPosHex = *newPosIt;
        if (newPosHex.remove_crystal()) {
            if (e.insert_crystal()) {
                this->print(concat("Robot ", e.get_id(), " now has ", e.get_crystals(), " crystals."));
                this->ambient.erase(newPosIt);
                this->ambient.insert(newPosHex);
                this->updated_cells.push(newPosHex);
                return true;
            }
        }
    }
    return false;
}

bool Arena::request_drop(EntityMove &e, const Hex &pos) {
    if (Log::LOGGING_LEVEL == Log::DEBUG) {
        this->print(concat("Robot ", e.get_id(), " dropping in [", pos.get_row(), ", ", pos.get_col(), "]"));
    }
    if (this->validate_position(pos, e)) {
        auto newPosIt = this->ambient.find(pos);
        Hex newPosHex = *newPosIt;
        if (e.remove_crystal()) {
            if (newPosHex.insert_crystal()) {
                this->print(concat("Robot ", e.get_id(), " now has ", e.get_crystals(), " crystals."));
                this->ambient.erase(newPosIt);
                this->ambient.insert(newPosHex);
                this->updated_cells.push(newPosHex);
                return true;
            }
            else {
                //Forgets about it and gives the crystals back to the Entity.
                e.insert_crystal();
            }
        }
    }
    return false;
}

bool Arena::request_movement(EntityMove &e, const Hex &pos) {
    if (Log::LOGGING_LEVEL == Log::DEBUG) {
        this->print(concat("Robot ", e.get_id(), " moving to [", pos.get_row(), ", ", pos.get_col(), "]"));
    }
    if (this->validate_insertion(pos, e)) {
        if(e.use_fuel(Config::machine_mov_fuel_usage)){
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
            return true;
        }
        else{
            this->print(concat("Stuck at [", e.get_col(), ", ", e.get_row(), "]. Out of fuel!"), e);
        }
    }
    return false;
}

void Arena::update(const View &view) {
    for (auto &army : this->armies) {
        army.second.update();
    }
    ++this->time;
}

bool Arena::validate_insertion(const Hex &pos, EntityMove &e) {
    auto it = this->ambient.find(pos);
    if (!this->validate_position(pos, e)) {
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

bool Arena::validate_position(const Hex &pos, EntityMove &e) {
    auto it = this->ambient.find(pos);
    if (it == this->ambient.end()) {
        this->print(concat("The position [", pos.get_row(), ",", pos.get_col(), "] is outside the play area"), e);
        return false;
    }
    return true;
}