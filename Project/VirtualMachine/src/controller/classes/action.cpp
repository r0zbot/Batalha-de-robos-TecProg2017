#include <controller/classes/action.h>

#include <util/log.h>

Action::Action(const SystemCode code, const Direction direction)
        : code(code),
          direction(direction) {}

int Action::get_atr(const int i) const {
    if (i == 0) {
        return this->code;
    }
    if (i == 1) {
        return this->direction;
    }
    Log::error("Invalid Operand (Action) parameter access: ATR " + to_string(i));
}

SystemCode Action::get_code() const {
    return this->code;
}

Direction Action::get_direction() const {
    return this->direction;
}
