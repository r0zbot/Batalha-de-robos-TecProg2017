#include <view/view.h>

View::View() : window (popen("python3 apres.py", "w"), pclose) {
    if (!this->window) {
        throw runtime_error("Window Program not found");
    }
}

void View::load(const Entity &e) const {
    fputs(concat("rob ",
                 e.get_image_path(), " ",
                 e.get_x(), " ",
                 e.get_y(), "\n").c_str(), this->window.get());
}

void View::render(const Entity &e) const {
    fputs(concat(e.get_id(), " ",
                 e.get_x(),  " ",
                 e.get_y(), "\n").c_str(), this->window.get());
}

void View::unload() {
    fputs("fim", this->window.get());
    this->update();
}

void View::update() {
    fflush(this->window.get());
}
