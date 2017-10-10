#ifndef VIRTUALMACHINE_ARMY_H
#define VIRTUALMACHINE_ARMY_H

#include <config.h>
#include <machine.h>
#include <map>

using namespace std;
typedef map<int, Machine>::iterator MachineIterator;
//TODO better documentation
class Army{
    private:
        map<int, Machine> machines;
        string name;

    public:
        explicit Army(string name);
        void add_machine(int id, Machine &machine);
        longlong machine_count();
        string get_name();
        Machine& get_machine(int id);
        MachineIterator machine_iterator_begin();
        MachineIterator machine_iterator_end();
};

#endif
