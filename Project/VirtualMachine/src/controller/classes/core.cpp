#include <controller/classes/core.h>
#include <controller/classes/number.h>

Core::Core() {
    //TODO: Creates arena and its entities.

    Army a1 ("Army 1");
    Army a2 ("Army 1");

    this->arena.insert_army(a1);
    this->arena.insert_army(a2);

    const vector<Instruction> prog ({
        Instruction(Code::PUSH, make_shared<Number>(9)),
        Instruction(Code::END,  nullptr)});

    for (int i = 0; i < 5; i++) {
        this->arena.create_robot(a1.get_id(), prog);
        this->arena.create_robot(a2.get_id(), prog);
    }
}

void Core::onLoad() {
    this->arena.load(this->view);
}

void Core::onRender() {
    this->arena.render(this->view);
    this->view.update();
}

void Core::onUnload() {
    this->view.unload();
}

void Core::onUpdate() {
    this->arena.update();
}

void Core::start() {
    this->onLoad();
    for (int i = 0; i < 5; i++) {
        this->onUpdate();
        this->onRender();
    }
    this->onUnload();
}
