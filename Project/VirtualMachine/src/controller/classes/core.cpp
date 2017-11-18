#include <controller/classes/core.h>

Core::Core(const Arena &arena)
        : arena(arena) {}

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
    this->arena.update(this->view);
}

void Core::sleep() const {
#ifdef LINUX
    usleep(game_sleep_time * 1000);   // usleep takes sleep time in us (1 millionth of a second)
#endif

#ifdef WINDOWS
    Sleep(game_sleep_time);
#endif
}

void Core::start() {
    this->onLoad();
    for (int i = 0; i < 20; i++) {
        this->onUpdate();
        this->onRender();
        this->sleep();
    }
    this->onUnload();
}
