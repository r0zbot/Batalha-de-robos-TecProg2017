#ifndef VIRTUALMACHINE_ARENA_H
#define VIRTUALMACHINE_ARENA_H

#include <map>

#include <application/component/hex.h>

#include <controller/classes/system.h>

#include <model/entity/army.h>

#define SLEEP_TIME 300

using namespace std;

class Arena {

    private:
        unsigned long long time;

        map<int, Army> armies;
        unordered_set<Hex> ambient;

    public:
        explicit Arena();

        unsigned long long elapsed_time() const;

        void insert_army(const Army &army);

        void remove_army(int id);

        void request_attack_melee(const EntityMove &e, const Hex &pos);
        void request_attack_short(const EntityMove &e, const Hex &pos);
        void request_attack_long(const EntityMove &e, const Hex &pos);
        void request_collect(const EntityMove &e, const Hex &pos);
        void request_drop(const EntityMove &e, const Hex &pos);
        void request_movement(const EntityMove &e, const Hex &pos);

        void update();
};

#endif
