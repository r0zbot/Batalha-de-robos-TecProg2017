#ifndef VIRTUALMACHINE_ARMY_H
#define VIRTUALMACHINE_ARMY_H

#include <map>

#include <model/interface/entity_move.h>

using namespace std;

class Army {

    private:
        static int id_gen;

        const int id;
        map<int, EntityMove*> soldiers;

    public:
        explicit Army(const vector<EntityMove*> &soldiers);

        ~Army();

        int get_id() const;

        unsigned long size() const;

        bool contains_soldier(int id) const;

        EntityMove* get_soldier(int id);

        void remove_soldier(int id);

        void update();
};

#endif
