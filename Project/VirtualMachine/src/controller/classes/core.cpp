#include <controller/classes/core.h>

Core::Core(const Arena &arena, const unsigned int sleep_time)
        : arena(arena),
          sleep_time(sleep_time) {}

string Core::get_bin_path() {
#ifdef linux
    char result[ PATH_MAX ];
    ssize_t count = readlink( "/proc/self/exe", result, PATH_MAX );
    string output = string( result, (count > 0) ? count : 0 );
    return output.substr(0, output.find_last_of('/'));
#endif

#ifdef _WIN32
    char result[ MAX_PATH ];
    string output = string( result, GetModuleFileName( NULL, result, MAX_PATH ) );
    return output.substr(0, output.find_last_of('\\'));
#endif
    return "Can't calculate path!";
}

string Core::get_view_path() {
#ifdef linux
    return concat("\'", Core::get_bin_path(), "/../../View/game_view.py", "\'");
#endif

#ifdef _WIN32
    return concat(Core::get_bin_path(), "\\..\\..\\View\\game_view.py");
#endif
    return "Can't calculate path!";
}

string Core::get_soldier_image_path(const int army_id) {
#ifdef linux
    return concat(Core::get_bin_path(), "/../../View/properties/soldier/soldier_", army_id % 5, ".png");
#endif

#ifdef _WIN32
    return concat(Core::get_bin_path(), "\\..\\..\\View\\properties\\soldier\\soldier_", army_id % 5, ".png");
#endif
    return "Can't calculate path!";
}

void Core::on_load() {
    this->arena.load(this->view);
}

void Core::on_render() {
    this->arena.render(this->view);
    this->view.update();
}

void Core::on_unload() {
    this->view.unload();
}

void Core::on_update() {
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
    this->on_load();
    //TODO: detect when user closes the pygame window
    while (true) {
        this->on_update();
        this->on_render();
        this->sleep();
    }
    this->on_unload();
}
