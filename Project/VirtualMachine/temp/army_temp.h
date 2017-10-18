#ifndef VIRTUALMACHINE_ARMY_H
#define VIRTUALMACHINE_ARMY_H

#include <map>
#include <memory>

#include <model/interface/entity_move.h>

using namespace std;

class Army_Temp {

    private:
        static int id_gen;

        const int id;
        map<int, shared_ptr<EntityMove>> soldiers; ///< Using smart pointers instead of raw pointers.

    public:
        explicit Army_Temp(const vector<shared_ptr<EntityMove>> &soldiers);

        int get_id() const;

        unsigned long size() const;

        bool contains_soldier(int id) const;

        shared_ptr<EntityMove> get_soldier(int id);

        void remove_soldier(int id);

        void update();
};

#endif
