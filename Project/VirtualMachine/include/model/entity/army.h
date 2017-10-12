#ifndef VIRTUALMACHINE_ARMY_H
#define VIRTUALMACHINE_ARMY_H

#include <map>

#include <controller/classes/machine.h>

#include <model/entity/robot.h>

#include <util/config.h>

using namespace std;
//TODO better documentation
class Army{
    private:
        int id;
        map<int, Robot> robots;
        string name;

    public:
        explicit Army(int id, string name);
        void insert_robot(Robot robot);
        int get_id();
        string get_name() const;
        Robot& get_robot(int id);
        longlong robot_count();

        void update();
};

#endif