#ifndef VIRTUALMACHINE_CORE_H
#define VIRTUALMACHINE_CORE_H

#include <memory>

#include <controller/classes/arena.h>

#include <view/view.h>

using namespace std;

class Core {

    private:
        Arena arena;

        View view;

    public:
        Core();

        void onLoad();

        void onRender();

        void onUnload();

        void onUpdate();

        void start();
};

#endif
