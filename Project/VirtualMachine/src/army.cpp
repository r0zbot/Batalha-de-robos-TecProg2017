#include <army.h>

Army::Army(const int id, const string name){
    this->id = id;
    this->name = name;
}

void Army::add_robot(const int id, Robot &robot) {
    this->robots.insert({id, robot});
}

int Army::get_id() {
    return this->id;
}

Robot &Army::get_robot(const int id) const {
    return this->robots.at(id);
}

string Army::get_name() const{
    return this->name;
}

longlong Army::robot_count() {
    return this->robots.size();
}

void Army::update() {
    for(auto &robot : this->robots){
        robot.second.update();
    }
}

