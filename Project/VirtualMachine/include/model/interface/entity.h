#ifndef VIRTUALMACHINE_ENTITY_H
#define VIRTUALMACHINE_ENTITY_H

#include <application/component/hex.h>

class Entity {

    private:
        static int id_gen;

        const int id;
        Hex pos;

    public:
        explicit Entity(const Hex &pos);

        virtual void update(int cycles) = 0;

        int get_id() const;
        int get_x() const;
        int get_y() const;

        void set_position(const Hex &pos);
};

#endif
