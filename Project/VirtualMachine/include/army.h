#ifndef VIRTUALMACHINE_ARMY_H
#define VIRTUALMACHINE_ARMY_H

class Army{
    private:
        map<int, Machine> machine;

    public:
        Machine& get_machine(int id);
};

#endif
