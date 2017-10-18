#include <model/interface/entity.h>

Entity::Entity(const Hex &pos) : id(id_gen++), pos(pos) {}

bool Entity::operator!=(const Entity &e) const {
    return !(*this == e);
}

bool Entity::operator==(const Entity &e) const {
    return this->id == e.id;
}

int Entity::get_id() const {
    return this->id;
}

int Entity::get_x() const {
    return this->pos.get_col();
}

int Entity::get_y() const {
    return this->pos.get_row();
}

void Entity::set_position(const Hex &pos) {
    this->pos = pos;
}
