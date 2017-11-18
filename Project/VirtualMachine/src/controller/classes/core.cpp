#include <controller/classes/core.h>

Core::Core(const Arena &arena, const unsigned int sleep_time)
        : arena(arena),
          sleep_time(sleep_time) {}

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
#ifdef linux
    usleep(this->sleep_time * 1000);
#endif

#ifdef _WIN32
    Sleep(this->sleep_time);
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
