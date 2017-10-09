#ifndef VIRTUALMACHINE_ARMY_H
#define VIRTUALMACHINE_ARMY_H

#include <config.h>
#include <machine.h>
#include <map>

using namespace std;
typedef map<int, Machine>::iterator MachineIterator;

class Army{
    private:
        map<int, Machine> machines;

    public:
        Army();
        void add_machine(int id, Machine &machine);
        longlong machine_count();
        Machine& get_machine(int id);
        MachineIterator machine_iterator_begin();
        MachineIterator machine_iterator_end();
};

#endif
