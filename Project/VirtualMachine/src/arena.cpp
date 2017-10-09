#include <arena.h>

Arena::Arena() {
    //TODO init arena?
}

void Arena::create_machine(Army &army, Program &prog) {
    Machine machine(prog);
    army.add_machine(this->machine_id_index++, machine);
}

longlong Arena::get_elapsed_time() {
    return this->time*(ARENA_SLEEP_TIME);
}

void Arena::update() {
    for(auto& army : this->armies){
        MachineIterator it = army.second.machine_iterator_begin();
        MachineIterator itEnd = army.second.machine_iterator_end();
        for(;  it != itEnd; ++it){
            it->second.run(MACHINE_RUN_CYCLES);
        }
    }
    _sleep(ARENA_SLEEP_TIME);
    this->time++;
}
