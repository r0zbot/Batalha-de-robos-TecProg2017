#ifndef VIRTUALMACHINE_ARMY_H
#define VIRTUALMACHINE_ARMY_H

#include <config.h>
#include <machine.h>
#include <map>
#include <robot.h>

using namespace std;
//TODO better documentation
class Army{
    private:
        int id;
        map<int, Robot> robots;
        string name;

    public:
        explicit Army(int id, string name);
            void add_robot(int id, Robot &robot);
        longlong robot_count();
        int get_id();
        string get_name() const;
        Robot& get_robot(int id) const;

        void update();
};

#endif
