#include <army.h>

Army::Army(){

}

void Army::add_machine(int id, Machine &machine) {
    //this->machines[id] = machine; TODO: O que esta errado aqui? isso nao compila
    //Reference https://stackoverflow.com/questions/26409558/ambiguous-map-insert-in-boost
}

Machine &Army::get_machine(int id) {
    return this->machines.at(id);
}

longlong Army::machine_count() {
    return this->machines.size();
}

MachineIterator Army::machine_iterator_begin() {
    return this->machines.begin();
}

MachineIterator Army::machine_iterator_end() {
    return this->machines.end();
}

