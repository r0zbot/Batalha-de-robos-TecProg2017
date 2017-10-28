#include <gtest/gtest.h>

#include <controller/classes/number.h>

class TestNumber : public testing::Test {};

TEST_F(TestNumber, equalsOperator_withNumberOperands_shouldReturnTrueWithTheNumbersAreEqualAndFalseOtherwise) {
    ASSERT_TRUE(Number(4) == Number(4));
    ASSERT_TRUE(Number(1) == Number(1));
    ASSERT_TRUE(Number(2901) == Number(2901));

    ASSERT_FALSE(Number(4) == Number(3));
    ASSERT_FALSE(Number(1) == Number(2));
    ASSERT_FALSE(Number(2901) == Number(2801));
}

TEST_F(TestNumber, notEqualsOperator_withNumberOperands_shouldReturnTrueWithTheNumbersAreNotEqualAndFalseOtherwise) {
    ASSERT_TRUE(Number(3) != Number(4));
    ASSERT_TRUE(Number(2) != Number(1));
    ASSERT_TRUE(Number(1901) != Number(2901));

    ASSERT_FALSE(Number(4) != Number(4));
    ASSERT_FALSE(Number(1) != Number(1));
    ASSERT_FALSE(Number(2901) != Number(2901));
}

TEST_F(TestNumber, greaterThanOperator_withNumberOperands_shouldReturnTrueWithTheFirstNumberIsGreaterThanTheOtherAndFalseOtherwise) {
    ASSERT_TRUE(Number(5) > Number(4));
    ASSERT_TRUE(Number(2) > Number(1));
    ASSERT_TRUE(Number(2901) > Number(2900));

    ASSERT_FALSE(Number(3) > Number(4));
    ASSERT_FALSE(Number(1) > Number(1));
    ASSERT_FALSE(Number(2900) > Number(2901));
}

TEST_F(TestNumber, greaterEqualsOperator_withNumberOperands_shouldReturnTrueWithTheFirstNumberIsGreaterOrEqualsTheOtherAndFalseOtherwise) {
    ASSERT_TRUE(Number(5) >= Number(4));
    ASSERT_TRUE(Number(2) >= Number(2));
    ASSERT_TRUE(Number(2901) >= Number(2900));

    ASSERT_FALSE(Number(3) >= Number(4));
    ASSERT_FALSE(Number(1) >= Number(2));
    ASSERT_FALSE(Number(2900) >= Number(2901));
}

TEST_F(TestNumber, lowerThanOperator_withNumberOperands_shouldReturnTrueWithTheFirstNumberIsLowerThanTheOtherAndFalseOtherwise) {
    ASSERT_TRUE(Number(4) < Number(5));
    ASSERT_TRUE(Number(2) < Number(3));
    ASSERT_TRUE(Number(2900) < Number(2901));

    ASSERT_FALSE(Number(4) < Number(4));
    ASSERT_FALSE(Number(1) < Number(0));
    ASSERT_FALSE(Number(2900) < Number(1999));
}

TEST_F(TestNumber, lowerEqualsOperator_withNumberOperands_shouldReturnTrueWithTheFirstNumberIsLowerOrEqualsTheOtherAndFalseOtherwise) {
    ASSERT_TRUE(Number(4) <= Number(5));
    ASSERT_TRUE(Number(2) <= Number(2));
    ASSERT_TRUE(Number(2900) <= Number(2901));

    ASSERT_FALSE(Number(8) <= Number(4));
    ASSERT_FALSE(Number(1) <= Number(0));
    ASSERT_FALSE(Number(2900) <= Number(1999));
}

TEST_F(TestNumber, plusOperator_withNumberOperands_shouldReturnTheSumOfNumberOperands) {
    /// 9 + 10 + (-12) == 7
    ASSERT_EQ(Number(7), Number(9) + Number(10) + Number(-12));
}

TEST_F(TestNumber, minusOperator_withNumberOperands_shouldReturnTheDifferenceOfNumberOperands) {
    /// 10 - 10 - 0 == 0
    ASSERT_EQ(Number(0), Number(10) - Number(10) - Number(0));
}

TEST_F(TestNumber, productOperator_withNumberOperands_shouldReturnTheProductOfNumberOperands) {
    /// 10 * 10 * 0 == 0
    ASSERT_EQ(Number(0), Number(10) * Number(10) * Number(0));
}

TEST_F(TestNumber, divisionOperator_withNumberOperands_shouldReturnTheQuotientOfNumberOperands) {
    /// 10 / (10 / 10) == 10
    ASSERT_EQ(Number(10), Number(10) / (Number(10) / Number(10)));
}

TEST_F(TestNumber, modulusOperator_withNumberOperands_shouldReturnTheModulusOfTheOperation) {
    /// 10 % (10 / 10) == 0
    ASSERT_EQ(Number(0), Number(10) % (Number(10) / Number(10)));
}

TEST_F(TestNumber, diversesOperations_withNumberOperands_shouldReturnTheCorrectResultForTheCalculus) {
    /// ((10 * 2) / 1 + 0) % 50 == 20
    ASSERT_EQ(Number(20), ((Number(10) * Number(2)) / Number(1) + Number(0)) % Number(50));
}

TEST_F(TestNumber, plusAssignmentOperator_withNumberOperand_shouldAddAValueToTheNumberItself) {
    Number n (5);
    n += Number(15);
    ASSERT_EQ(Number(20), n);

    n += Number(-15);
    ASSERT_EQ(Number(5), n);

    n += Number(99);
    ASSERT_EQ(Number(104), n);
}

TEST_F(TestNumber, minusAssignmentOperator_withNumberOperand_shouldSubtractAValueToTheNumberItself) {
    Number n (5);
    n -= Number(15);
    ASSERT_EQ(Number(-10), n);

    n -= Number(-10);
    ASSERT_EQ(Number(0), n);

    n -= Number(50);
    ASSERT_EQ(Number(-50), n);
}

TEST_F(TestNumber, productAssignmentOperator_withNumberOperand_shouldMultiplyAValueToTheNumberItself) {
    Number n (5);
    n *= Number(15);
    ASSERT_EQ(Number(75), n);

    n *= Number(0);
    ASSERT_EQ(Number(0), n);

    n *= Number(15);
    ASSERT_EQ(Number(0), n);
}

TEST_F(TestNumber, divisionAssignmentOperator_withNumberOperand_shouldDivideAValueToTheNumberItself) {
    Number n (20);
    n /= Number(5);
    ASSERT_EQ(Number(4), n);

    n /= Number(2);
    ASSERT_EQ(Number(2), n);

    n /= Number(1);
    ASSERT_EQ(Number(2), n);
}

TEST_F(TestNumber, modulusAssignmentOperator_withNumberOperand_shouldStoreTheModulusOfTheOperationToTheNumberItself) {
    Number n (20);
    n %= Number(5);
    ASSERT_EQ(Number(0), n);
}

TEST_F(TestNumber, postfixIncrementOperator_withNumberOperand_shouldIncrementNumberValueByOneWithPostfixFeature) {
    Number n (20);
    ASSERT_EQ(Number(20), n++);
    ASSERT_EQ(Number(21), n);
}

TEST_F(TestNumber, prefixIncrementOperator_withNumberOperand_shouldIncrementNumberValueByOneWithPrefixFeature) {
    Number n (20);
    ASSERT_EQ(Number(21), ++n);
}

TEST_F(TestNumber, postfixDecrementOperator_withNumberOperand_shouldDecrementNumberValueByOneWithPostfixFeature) {
    Number n (20);
    ASSERT_EQ(Number(20), n--);
    ASSERT_EQ(Number(19), n);
}

TEST_F(TestNumber, prefixDecrementOperator_withNumberOperand_shouldDecrementNumberValueByOneWithPrefixFeature) {
    Number n (20);
    ASSERT_EQ(Number(19), --n);
}

TEST_F(TestNumber, getAttribute_withValidAttributeIndex_shouldReturnTheSpecifiedAttribute) {
    Number n (20);
    ASSERT_EQ(Number(20), Number(n.get_atr(0)));
    ASSERT_EQ(Number(20), Number(n.get_value()));
}

TEST_F(TestNumber, info_withNumberOperand_shouldReturnTheStringRepresentationOfNumberOperand) {
    ASSERT_EQ("Type = Number; Value = 20", Number(20).info());
}
