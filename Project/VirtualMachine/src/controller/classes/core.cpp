#include <controller/classes/core.h>

Core::Core() {
    /// Creates armies and soldiers in the arena.
    this->view = popen("./apres", "w");
    if (this->view) {
        
    }
}

void Core::onLoad() {

}

