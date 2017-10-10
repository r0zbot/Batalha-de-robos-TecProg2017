#include <army.h>

Army::Army(string name){
    this->name = name;
}

void Army::add_machine(int id, Machine &machine) {
    this->machines.insert({id, machine});
}

Machine &Army::get_machine(int id) {
    return this->machines.at(id);
}

string Army::get_name() {
    return this->name;
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

