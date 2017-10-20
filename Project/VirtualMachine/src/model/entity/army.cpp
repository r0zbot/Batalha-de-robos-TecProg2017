#include <model/entity/army.h>
#include <util/config.h>

Army::Army(const string &name) :
        id(id_gen++),
        name(name){

}

Army::~Army() {
    for (auto const &e : this->soldiers) {
        delete e.second;
    }
    this->soldiers.clear();
}

bool Army::contains_soldier(const int id) const {
    return this->soldiers.find(id) != this->soldiers.end();
}

int Army::get_id() const {
    return this->id;
}

string Army::get_name() {
    return this->name;
}

EntityMove* Army::get_soldier(const int id) {
    return this->soldiers.at(id);
}

void Army::instert_soldier(EntityMove *entityMove) {
    entityMove->set_group_id(this->get_id());
    this->soldiers.emplace(entityMove->get_id(), entityMove);
}

void Army::remove_soldier(const int id) {
    this->soldiers.erase(id);
}

unsigned long Army::size() const {
    return this->soldiers.size();
}

void Army::update() {
    for (auto const &e : this->soldiers) {
        e.second->update(MACHINE_RUN_CYCLES);
    }
}
