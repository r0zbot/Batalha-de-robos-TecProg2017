#include <concat.hpp>

#include <model/entity/arena.h>

#include <util/log.h>

Arena::Arena() {
    for(int i=0; i<ARENA_HEIGHT; i++){
        for (int j=0; j<ARENA_WIDTH; j++){
            arena_space[i][j]=-1;
        }
    }
}

int Arena::create_robot(Army &army, int posX, int posY, Program prog) {
    if(this->arena_space[posX][posY] != -1){
        Log::error(concat("There's already a robot in position [",posX,",",posY,"]."));
        return -1;
    }
    int id = (int)(army.robot_count());
    this->arena_space[posX][posY] = id;
    army.insert_robot(Robot(id, posX, posY, prog));
    //The machine's parent (its robot) needs to be set manually because
    // a copy is made when storing in the army.
    army.get_robot(id).get_machine().set_parent(&army.get_robot(id));
    return id;
}

Army & Arena::get_army(int id) {
    return this->armies.at(id);
}

longlong Arena::get_elapsed_time() {
    return this->time*(ARENA_SLEEP_TIME);
}

Army &Arena::get_robots_army(Robot &robot) {
    for(auto &army : this->armies){
        if(army.contains_robot(robot)){
            return army;
        }
    }
    Log::error("Robot is not in any army!");
}

int Arena::insert_army(const string name) {
    int id = this->armies.size();
    this->armies.insert(this->armies.begin()+this->armies.size(), Army(id, name));
    return id;
}

void Arena::print(const string &s) {
    printf("Arena: %s",s.c_str());
}

void Arena::print(const string &s, Robot &robot) {
    printf("Robot %i (Army %s): %s\n", robot.get_id(), get_robots_army(robot).get_name().c_str(), s.c_str());
}

void Arena::print(const int n, Robot &robot) {
    this->print(to_string(n), robot);
}

void Arena::remove_army(int id) {
    this->armies.erase(this->armies.begin()+id);
}

void Arena::request_attack_melee(Robot &robot, Direction direction){
    this->print(concat("Attack Melee ",(int)direction), robot);
    //TODO
}

void Arena::request_attack_short(Robot &robot, Direction direction) {
    this->print(concat("Attack Short ",(int)direction), robot);
    //TODO
}

void Arena::request_attack_long(Robot &robot, Direction direction) {
    this->print(concat("Attack Long ",(int)direction), robot);
    //TODO
}

void Arena::request_collect(Robot &robot, Direction direction) {
    this->print(concat("Collect ",(int)direction), robot);
    //TODO
}

void Arena::request_drop(Robot &robot, Direction direction) {
    this->print(concat("Drop ",(int)direction), robot);
    //TODO
}

void Arena::request_movement(Robot &robot, Direction direction) {
    this->print(concat("Move ",(int)direction), robot);
    //TODO
}

void Arena::update() {
    for(auto &army : this->armies) {
        army.update();
    }
    ++this->time;
}
