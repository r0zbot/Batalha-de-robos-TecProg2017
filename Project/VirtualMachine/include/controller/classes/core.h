#ifndef VIRTUALMACHINE_CORE_H
#define VIRTUALMACHINE_CORE_H

#include <memory>

#include <controller/classes/arena.h>

using namespace std;

class Core {

    private:
        Arena arena;

        shared_ptr<FILE> view;

    public:
        Core();

        void onLoad();

        void onRender();

        void onUpdate();
};

#endif
