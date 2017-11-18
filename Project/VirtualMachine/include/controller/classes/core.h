#ifndef VIRTUALMACHINE_CORE_H
#define VIRTUALMACHINE_CORE_H

#ifdef linux
#include <unistd.h>
#include <limits.h>
#endif

#ifdef _WIN32
#include <windows.h>
#endif

#include <memory>

#include <controller/classes/arena.h>

#include <view/view.h>

using namespace std;

class Core {

    private:
        Arena arena;

        const unsigned int sleep_time;

        View view;

    public:
        Core(const Arena &arena, unsigned int sleep_time);

        static string getBinPath();

        static string getViewPath();

        static string getSoldierImagePath(int armyId);

        void onLoad();

        void onRender();

        void onUnload();

        void onUpdate();

        void sleep() const;

        void start();
};

#endif
