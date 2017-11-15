#include <view/view.h>

View::View() : window (popen("./apres", "w")) {
    if (!this->window) {
        throw runtime_error("Window Program not found");
    }
}

void View::load(const Entity &e) const {
    fputs(("rob " + e.get_image_path() + "\n").c_str(), this->window.get());
}

void View::render(const Entity &e) const {
    fputs(concat(e.get_id(), " ",
                 e.get_x(),  " ",
                 e.get_y()).c_str(), this->window.get());
}

void View::unload() const {
    fputs("fim", this->window.get());
}

void View::update() {
    fflush(this->window.get());
}
