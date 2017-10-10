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

Army & Arena::get_army(int id) {
    return this->armies.at(id);
}

longlong Arena::get_elapsed_time() {
    return this->time*(ARENA_SLEEP_TIME);
}

int Arena::insert_army(const string name) {
    int id = this->armies.size();
    this->armies.insert(this->armies.begin()+this->armies.size(), Army(id, name));
    return id;
}

int Arena::create_robot(Army &army, int posX, int posY, Program prog) {
    if(this->arena_space[posX][posY] != -1){
        Log::error(concat("There's already a robot in position [",posX,",",posY,"]."));
        return -1;
    }
    int id = (int)(army.robot_count());
    this->arena_space[posX][posY] = id;
    army.insert_robot(Robot(id, posX, posY, prog));
    return id;
}

void Arena::system(int op, int arg) {
    //TODO: implementar
}

void Arena::remove_army(int id) {
    this->armies.erase(this->armies.begin()+id);
}

void Arena::update() {
    for(auto &army : this->armies){
        army.update();
    }
    this->time++;
}
