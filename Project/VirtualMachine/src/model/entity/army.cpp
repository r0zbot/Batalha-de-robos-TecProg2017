#include <concat.hpp>

#include <model/entity/army.h>

#include <util/log.h>

Army::Army(const int id, const string name){
    this->id = id;
    this->name = name;
}

//TODO: quando/se robos tiverem IDs globais, substituir por id para ser mais rapido
bool Army::contains_robot(Robot &robot) {
    for (auto &currentRobot : this->robots)
        if (&robot == &currentRobot.second)
            return true;
    return false;
}

void Army::insert_robot(Robot robot) {
    this->robots.insert({robot.get_id(), robot});
}

int Army::get_id() {
    return this->id;
}

Robot &Army::get_robot(const int id) {
    return this->robots.at(id);
}

string Army::get_name() {
    return this->name;
}

longlong Army::robot_count() {
    return this->robots.size();
}

void Army::update() {
    //Log::debug(concat("Updating army ",this->name));
    for(auto &robot : this->robots){
        //Log::debug(concat("Robot ",robot.first));
        robot.second.update();
    }
}
