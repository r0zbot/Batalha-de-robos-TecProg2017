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
    //TODO: detect when user closes the pygame window
    while (true) {
        this->onUpdate();
        this->onRender();
        this->sleep();
    }
    this->onUnload();
}

string Core::getBinPath() {
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

string Core::getViewPath(){
#ifdef linux
    return concat("\'", Core::getBinPath(), "/../../View/game_view.py", "\'");
#endif

#ifdef _WIN32
    return concat(Core::getBinPath(), "\\..\\..\\View\\game_view.py");
#endif
    return "Can't calculate path!";
}

string Core::getSoldierImagePath(int armyId){
#ifdef linux
    return concat("\'", Core::getBinPath(), "/../../View/properties/soldier/soldier_", armyId, ".png'");
#endif

#ifdef _WIN32
    return concat(Core::getBinPath(), "\\..\\..\\View\\properties\\soldier\\soldier_", armyId, ".png");
#endif
    return "Can't calculate path!";
}