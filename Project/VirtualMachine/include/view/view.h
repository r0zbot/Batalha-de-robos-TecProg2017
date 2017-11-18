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

        void load(int height, int width) const;

        void load(const Hex &hex) const;

        void load(const Entity &e) const;

        void render(const Entity &e) const;

        void unload();

        void update();
};

#endif
