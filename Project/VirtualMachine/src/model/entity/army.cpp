#include <model/entity/army.h>

Army::Army(const vector<EntityMove*> &soldiers) : id(id_gen++) {
    for (auto const &e : soldiers) {
        e->set_group_id(this->id);
        this->soldiers.emplace(e->get_id(), e);
    }
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

EntityMove* Army::get_soldier(const int id) {
    return this->soldiers.at(id);
}

void Army::remove_soldier(const int id) {
    this->soldiers.erase(id);
}

unsigned long Army::size() const {
    return this->soldiers.size();
}

void Army::update() {
    for (auto const &e : this->soldiers) {
        e.second->update(50);
    }
}
