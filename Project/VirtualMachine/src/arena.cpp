#include <arena.h>
#include <log.h>
#include <concat.hpp>
#include <stdio.h>
Arena::Arena() {

}

void Arena::create_machine(Army &army, Program &prog) {
    Machine machine(prog);
    army.add_robot(this->machine_id_index++, machine);
}

longlong Arena::get_elapsed_time() {
    return this->time*(ARENA_SLEEP_TIME);
}

int Arena::insert_army(const string name) {
    int id = this->armies.size();
    this->armies.insert(this->armies.begin()+this->armies.size(), Army(id, name));
    return id;
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
