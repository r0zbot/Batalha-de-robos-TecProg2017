#ifndef VIRTUALMACHINE_VIEW_H
#define VIRTUALMACHINE_VIEW_H

#include <memory>

#include <concat.hpp>

#include <model/interface/entity.h>

using namespace std;

class View {

    private:
        shared_ptr<FILE> window;

    public:
        View();

        void load(const Entity &e) const;

        void render(const Entity &e) const;

        void unload() const;

        void update();
};

#endif
