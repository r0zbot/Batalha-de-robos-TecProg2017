#include <model/entity/army.h>

#include <util/config.h>

Army::Army(const string &name)
        : id(id_gen++),
          name(name){}

bool Army::contains_soldier(const int id) const {
    return this->soldiers.count(id) != 0;
}

int Army::get_id() const {
    return this->id;
}

string Army::get_name() const {
    return this->name;
}

EntityMovePtr Army::get_soldier(const int id) {
    auto itr = this->soldiers.find(id);
    if (itr != this->soldiers.end()) {
        return itr->second;
    }
    return nullptr;
}

void Army::insert_soldier(EntityMovePtr &soldier) {
    soldier.get()->set_group_id(this->get_id());
    this->soldiers.emplace(soldier.get()->get_id(), soldier);
}

void Army::load(const View &view) {
    for (auto const &e : this->soldiers) {
        view.load(*e.second);
    }
}

void Army::remove_soldier(const int id) {
    if (this->contains_soldier(id)) {
        this->soldiers.erase(id);
    }
}

void Army::render(const View &view) {
    for (auto const &e : this->soldiers) {
        view.render(*e.second);
    }
}

unsigned long Army::size() const {
    return this->soldiers.size();
}

void Army::update() {
    for (auto const &e : this->soldiers) {
        e.second->update(MACHINE_RUN_CYCLES);
    }
}
