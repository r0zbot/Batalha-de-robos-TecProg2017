#include <view/view.h>
#include <controller/classes/core.h>

View::View() : window (popen(concat("python ", Core::getViewPath()).c_str(), "w"), pclose) {
    if (!this->window) {
        throw runtime_error("View Program not found");
    }
}

void View::load(const int height, const int width) const {
    fputs(concat("arena ",
                 height, " ",
                 width,  "\n").c_str(), this->window.get());
}

void View::load(const Hex &hex) const {
    fputs(concat("cell ",
                 hex.get_row(), " ",
                 hex.get_col(), " ",
                 static_cast<int>(hex.get_terrain()), " ",
                 hex.get_base()," ",
                 hex.get_crystals(), "\n").c_str(), this->window.get());
}

void View::load(const Entity &e) const {
    fputs(concat("entity ",
                 e.get_id(),  " ",
                 e.get_row(), " ",
                 e.get_col(), " ",
                 e.get_image_path(), "\n").c_str(), this->window.get());
}

void View::render(const Entity &e) const {
    fputs(concat(e.get_id(),  " ",
                 e.get_row(), " ",
                 e.get_col(), "\n").c_str(), this->window.get());
}

void View::unload() {
    fputs("quit", this->window.get());
    this->update();
}

void View::update() {
    fflush(this->window.get());
}
