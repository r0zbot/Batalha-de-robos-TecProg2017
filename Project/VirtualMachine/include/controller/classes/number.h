#ifndef VIRTUALMACHINE_NUMBER_H
#define VIRTUALMACHINE_NUMBER_H

#include <controller/interface/operand.h>

/**
 * @file  number.h
 * @class Number
 *
 * @brief The <b>Number</b> class represents a simple number {@link #Operand}.
 */
class Number : public Operand {

    private:
        /** Represents the number value. */
        int value;

    public:
        /**
         * @brief Constructs a <b>Number</b> object with the
         *        specified value.
         *
         * @param [value] The <b>Number</b> value.
         */
        explicit Number(int value);

        /**
         * @brief Overload of "equals" operator so it can compare two
         *        <b>Number</b> objects.
         *
         * This method executes inner comparisons in both of the
         * number's values, and return true only if their values are equal.
         *
         * @param [number] The number to be compared to the caller object.
         *
         * @return True if the numbers have the same value,
         *         false otherwise.
         */
        bool operator==(const Number &number) const;

        /**
         * @brief Overload of "not equals" operator so it can compare two
         *        <b>Number</b> objects.
         *
         * This method executes inner comparisons in both of the
         * numbers's values, and return true if their values are not equals.
         *
         * @param [number] The number to be compared to the caller object.
         *
         * @return True if the numbers have different values,
         *         false if they are equal.
         */
        bool operator!=(const Number &number) const;

        /**
         * @brief Overload of "greater" operator so it can compare two
         *        <b>Number</b> objects.
         *
         * This method executes inner comparisons in both of the
         * numbers's values, and return true if the value of the
         * function caller is greater than the given number value.
         *
         * @param [number] The number to be compared to the caller object.
         *
         * @return True if this number have greater value than the given
         *         number, false if it's not.
         */
        bool operator>(const Number &number) const;

        /**
         * @brief Overload of "greater equal" operator so it can compare two
         *        <b>Number</b> objects.
         *
         * This method executes inner comparisons in both of the
         * numbers's values, and return true if the value of the
         * function caller is greater or equal than the given number value.
         *
         * @param [number] The number to be compared to the caller object.
         *
         * @return True if this number have greater or equal value than the
         *         given number, false if it's not.
         */
        bool operator>=(const Number &number) const;

        /**
         * @brief Overload of "lower" operator so it can compare two
         *        <b>Number</b> objects.
         *
         * This method executes inner comparisons in both of the
         * numbers's values, and return true if the value of the
         * function caller is lower than the given number value.
         *
         * @param [number] The number to be compared to the caller object.
         *
         * @return True if this number have lower value than the given
         *         number, false if it's not.
         */
        bool operator<(const Number &number) const;

        /**
         * @brief Overload of "lower equal" operator so it can compare two
         *        <b>Number</b> objects.
         *
         * This method executes inner comparisons in both of the
         * numbers's values, and return true if the value of the
         * function caller is lower or equal than the given number value.
         *
         * @param [number] The number to be compared to the caller object.
         *
         * @return True if this number have lower or equal value than the
         *         given number, false if it's not.
         */
        bool operator<=(const Number &number) const;

        /**
         * @brief Overload of "plus" operator so it can add two
         *        <b>Number</b> objects.
         *
         * This method sums both of the number's values and return a
         * reference to a new <b>Number</b> object representing the
         * operation result.
         *
         * @param [number] The number to be summed with the caller object.
         *
         * @return A <b>Number</b> object representing the result of
         *         the sum operation.
         */
        Number operator+(const Number &number) const;

        /**
         * @brief Overload of "minus" operator so it can subtract two
         *        <b>Number</b> objects.
         *
         * This method subtracts both of the number's values and return a
         * reference to a new <b>Number</b> object representing the
         * operation result.
         *
         * @param [number] The number to be subtracted with the caller object.
         *
         * @return A <b>Number</b> object representing the result of
         *         the subtraction operation.
         */
        Number operator-(const Number &number) const;

        /**
         * @brief Overload of "product" operator so it can multiply two
         *        <b>Number</b> objects.
         *
         * This method multiplies both of the number's values and return a
         * reference to a new <b>Number</b> object representing the
         * operation result.
         *
         * @param [number] The number to be multiplied to the caller object.
         *
         * @return A <b>Number</b> object representing the result of
         *         the product operation.
         */
        Number operator*(const Number &number) const;

        /**
         * @brief Overload of "division" operator so it can divide two
         *        <b>Number</b> objects.
         *
         * This method divides both of the number's values and return a
         * reference to a new <b>Number</b> object representing the
         * operation result.
         *
         * @param [number] The number to divide the caller object.
         *
         * @return A <b>Number</b> object representing the result of
         *         the quotient operation.
         */
        Number operator/(const Number &number) const;

        /**
         * @brief Overload of "modulus" operator so it can execute a
         *        modulus operation in two <b>Number</b> objects.
         *
         * This method divides both of the number's values and return a
         * reference to a new <b>Number</b> object representing the
         * division reminder of the quotient operation.
         *
         * @param [number] The number to divide the caller object.
         *
         * @return A <b>Number</b> object representing the division reminder
         *         of the quotient operation.
         */
        Number operator%(const Number &number) const;

        /**
         * @brief Overload of "plus/assignment" operator so it can add two
         *        <b>Number</b> objects.
         *
         * This method sums both of the number's values and return a
         * reference to a new <b>Number</b> object representing the
         * operation result.
         *
         * @param [number] The number to be summed to the caller object.
         *
         * @return A reference to the new <b>Number</b> object representing
         *         the result of the sum operation.
         */
        Number& operator+=(const Number &number);

        /**
         * @brief Overload of "minus/assignment" operator so it can subtract
         *        two <b>Number</b> objects.
         *
         * This method subtracts both of the number's values and return a
         * reference to a new <b>Number</b> object representing the
         * operation result.
         *
         * @param [number] The number to be subtracted from the caller object.
         *
         * @return A reference to the new <b>Number</b> object representing
         *         the result of the difference operation.
         */
        Number& operator-=(const Number &number);

        /**
         * @brief Overload of "product/assignment" operator so it can
         *        multiply two <b>Number</b> objects.
         *
         * This method multiplies both of the number's values and return a
         * reference to a new <b>Number</b> object representing the
         * operation result.
         *
         * @param [number] The number to be multiplied to the caller object.
         *
         * @return A reference to the new <b>Number</b> object representing
         *         the result of the product operation.
         */
        Number& operator*=(const Number &number);

        /**
         * @brief Overload of "division/assignment" operator so it can
         *        divide two <b>Number</b> objects.
         *
         * This method divides both of the number's values and return a
         * reference to a new <b>Number</b> object representing the
         * operation result.
         *
         * @param [number] The number to divide the caller object.
         *
         * @return A reference to the new <b>Number</b> object representing
         *         the result of the quotient operation.
         */
        Number& operator/=(const Number &number);

        /**
         * @brief Overload of "modulus/assignment" operator so it can execute
         *        a modulus operation in two <b>Number</b> objects.
         *
         * This method divides both of the number's values and return a
         * reference to a new <b>Number</b> object representing the
         * division reminder of the quotient operation.
         *
         * @param [number] The number to divide the caller object.
         *
         * @return A reference to the new <b>Number</b> object representing
         *         the division reminder of the quotient operation.
         */
        Number& operator%=(const Number &number);

        /**
         * @brief Overload of prefix increment operator, so it increments
         *        by one the <b>Number</b> value.
         *
         * @return A reference to the new <b>Number</b> value.
         */
        Number& operator++();

        /**
         * @brief Overload of postfix increment operator, so it increments
         *        by one the <b>Number</b> value.
         *
         * @return A reference to the new <b>Number</b> value.
         */
        Number operator++(int);

        /**
         * @brief Overload of prefix decrement operator, so it decrements
         *        by one the <b>Number</b> value.
         *
         * @return A reference to the new <b>Number</b> value.
         */
        Number& operator--();

        /**
         * @brief Overload of postfix decrement operator, so it decrements
         *        by one the <b>Number</b> value.
         *
         * @return A reference to the new <b>Number</b> value.
         */
        Number operator--(int);

        /**
         * @brief Return the specified <b>Operand</b> attribute.
         *
         * @param [i] The attribute position.
         *
         * @return The attribute at the specified position.
         */
        int get_atr(int i) const override;

        /**
         * @brief Gets the <b>Number</b> value.
         *
         * @return The <b>Number</b> value.
         */
        int get_value() const;

        /**
         * @brief Returns a string representation of the object.
         *
         * @return A string representation of the object.
         */
        string info() const override;
};

#endif
