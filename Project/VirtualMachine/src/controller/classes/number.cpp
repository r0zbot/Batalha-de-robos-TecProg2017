#include <controller/classes/number.h>

#include <util/log.h>
#include <concat.hpp>

Number::Number(const int value) : value(value) {}

bool Number::operator==(const Number &number) const {
    return this->value == number.value;
}

bool Number::operator!=(const Number &number) const {
    return !(*this == number);
}

bool Number::operator>(const Number &number) const {
    return this->value > number.value;
}

bool Number::operator>=(const Number &number) const {
    return this->value >= number.value;
}

bool Number::operator<(const Number &number) const {
    return this->value < number.value;
}

bool Number::operator<=(const Number &number) const {
    return this->value <= number.value;
}

Number Number::operator+(const Number &number) const {
    return Number(this->value + number.value);
}

Number Number::operator-(const Number &number) const {
    return Number(this->value - number.value);
}

Number Number::operator*(const Number &number) const {
    return Number(this->value * number.value);
}

Number Number::operator/(const Number &number) const {
    return Number(this->value / number.value);
}

Number Number::operator%(const Number &number) const {
    return Number(this->value % number.value);
}

Number& Number::operator+=(const Number &number) {
    this->value += number.value;
    return *this;
}

Number& Number::operator-=(const Number &number) {
    this->value -= number.value;
    return *this;
}

Number& Number::operator*=(const Number &number) {
    this->value *= number.value;
    return *this;
}

Number& Number::operator/=(const Number &number) {
    this->value /= number.value;
    return *this;
}

Number& Number::operator%=(const Number &number) {
    this->value %= number.value;
    return *this;
}

Number& Number::operator++() {
    ++this->value;
    return *this;
}

Number Number::operator++(int) {
    ++this->value;
    return Number(this->value - 1);
}

Number& Number::operator--() {
    --this->value;
    return *this;
}

Number Number::operator--(int) {
    --this->value;
    return Number(this->value + 1);
}

int Number::get_atr(const int i) const {
    if (i == 0) {
        return this->value;
    }
    Log::error("Invalid Operand (Number) parameter access: ATR " + to_string(i));
}

int Number::get_value() const {
    return this->value;
}

string Number::info() const {
    return concat("Number: ", this->value);
}
