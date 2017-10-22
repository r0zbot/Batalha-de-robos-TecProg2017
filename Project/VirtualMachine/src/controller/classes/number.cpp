#include <controller/classes/number.h>

#include <util/log.h>

Number::Number(const int v) : v(v) {}

int Number::get_atr(const int i) const {
    if (i == 0) {
        return this->v;
    }
    Log::error("Invalid Operand (Number) parameter access: ATR " + to_string(i));
}
