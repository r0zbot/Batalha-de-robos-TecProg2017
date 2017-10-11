#include <model/interface/entity.h>

Entity::Entity(int id, int posX, int posY) {
    this->id = id;
    this->posX = posX;
    this->posY = posY;
}

int Entity::get_id() const {
    return this->id;
}

int Entity::get_parent_id() const {
    return this->parentId;
}

int Entity::get_posX() const {
    return this->posX;
}

int Entity::get_posY() const {
    return this->posY;
}

int Entity::set_posX(const int x) {
    this->posX = x;
}

int Entity::set_posY(const int y) {
    this->posY = y;
}
