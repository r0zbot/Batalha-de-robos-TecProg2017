#ifndef VIRTUALMACHINE_ARENA_H
#define VIRTUALMACHINE_ARENA_H

#include <map>

#include <application/component/hex.h>

#include <controller/classes/system.h>

#include <model/entity/army.h>
#include <model/entity/machine.h>

using namespace std;

class Arena {

    private:
        unsigned long long time;

        map<int, Army> armies;
        unordered_set<Hex> ambient;

        bool validate_insertion(Hex pos, EntityMove &e);


    public:
        explicit Arena();

        unsigned long long elapsed_time() const;

        Army &get_army(int id);

        int create_robot(Army &army, Hex pos, Program prog);

        EntityMove& find_entity_move(int id);

        void insert_army(const Army &army);

        void print(const string &s);
        void print(const string &s, EntityMove &e);
        void print(int n, EntityMove &e);

        void remove_army(int id);

        void request_attack_melee(EntityMove &e, const Hex &pos);
        void request_attack_short(EntityMove &e, const Hex &pos);
        void request_attack_long(EntityMove &e, const Hex &pos);
        void request_collect(EntityMove &e, const Hex &pos);
        void request_drop(EntityMove &e, const Hex &pos);
        void request_movement(EntityMove &e, const Hex &pos);

        void update();
};

#endif
