#include <controller/classes/core.h>

Core::Core() {
    //TODO: Creates arena and its entities.
}

void Core::onLoad() {
    this->arena.load(this->view);
}

void Core::onRender() {
    this->arena.render(this->view);
}

void Core::onUnload() {
    this->view.unload();
}

void Core::onUpdate() {
    this->arena.update();
}

void Core::start() {
    for (int i = 0; i < 10; i++) {
        this->onUpdate();
    }
    this->onUnload();
}
