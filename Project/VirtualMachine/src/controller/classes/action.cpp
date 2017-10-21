#include <controller/classes/action.h>

#include <util/log.h>

Action::Action(const SystemCode type, const Direction direction)
        : type(type),
          direction(direction) {}

int Action::get_atr(const int i) const {
    if (i == 0) {
        return this->type;
    }
    if (i == 1) {
        return this->direction;
    }
    Log::error("Invalid Operand (Action) parameter access: ATR " + to_string(i));
}
