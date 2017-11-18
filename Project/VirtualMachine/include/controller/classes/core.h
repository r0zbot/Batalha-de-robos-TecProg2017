#ifndef VIRTUALMACHINE_CORE_H
#define VIRTUALMACHINE_CORE_H

#ifdef LINUX
#include <unistd.h>
#endif

#ifdef WINDOWS
#include <windows.h>
#endif

#include <memory>

#include <controller/classes/arena.h>

#include <view/view.h>

using namespace std;

class Core {

    private:
        Arena arena;

        View view;

    public:
        explicit Core(const Arena &arena);

        void onLoad();

        void onRender();

        void onUnload();

        void onUpdate();

        void sleep() const;

        void start();
};

#endif
