#include <arena.h>
#include <log.h>
#include <concat.hpp>
#include <stdio.h>
Arena::Arena() {

}

void Arena::create_machine(Army &army, Program &prog) {
    Machine machine(prog);
    army.add_machine(this->machine_id_index++, machine);
}

longlong Arena::get_elapsed_time() {
    return this->time*(ARENA_SLEEP_TIME);
}

void Arena::insert_army(Army &army) {
    this->armies[armies_size++] = &army;
    //this->armies.insert(this->armies.begin()+this->armies.size(), army);
}

void Arena::remove_army(int id) {
    //this->armies.erase(this->armies.begin()+id);
}

void Arena::update() {
    for(int i=0; i<this->armies_size; i++){
        Army *army = this->armies[i];
        Log::debug(concat(army->get_name(),":"));

        auto it = army->machine_iterator_begin();
        auto itEnd = army->machine_iterator_end();
        for(;  it != itEnd; it++){
            it->second.run(MACHINE_RUN_CYCLES);
            Log::debug(concat("Running machine ",it->first," for ",MACHINE_RUN_CYCLES," cycles"));
        }
    }
    this->time++;
}
