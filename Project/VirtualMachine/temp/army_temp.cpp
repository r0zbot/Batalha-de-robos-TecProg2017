Army_Temp::Army_Temp(const vector<shared_ptr<EntityMove>> &soldiers) : id(id_gen++) {
    for (auto const &e : soldiers) {
        this->soldiers.emplace(e->get_id(), e);
    }
}

bool Army_Temp::contains_soldier(const int id) const {
    return this->soldiers.find(id) != this->soldiers.end();
}

int Army_Temp::get_id() const {
    return this->id;
}

shared_ptr<EntityMove> Army_Temp::get_soldier(const int id) {
    return this->soldiers.at(id);
}

void Army_Temp::remove_soldier(const int id) {
    this->soldiers.erase(id);
}

unsigned long Army_Temp::size() const {
    return this->soldiers.size();
}

void Army_Temp::update() {
    for (auto const &e : this->soldiers) {
        e.second->update(50);
    }
}

