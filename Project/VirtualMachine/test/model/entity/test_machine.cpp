#include <vector>

#include <gtest/gtest.h>

#include <controller/classes/action.h>
#include <controller/classes/number.h>

#include <model/entity/machine.h>

using namespace std;

class TestMachine : public testing::Test {};

TEST_F(TestMachine, add_numberOperands_shouldCalculateAndReturnTheSumOfTwoNumberOperands) {
    const vector<Instruction> prog ({
        Instruction(Code::PUSH, new Number(2)),
        Instruction(Code::PUSH, new Number(3)),
        Instruction(Code::ADD, nullptr),
        Instruction(Code::END, nullptr)});
    Machine m (prog);
    m.execute();
    EXPECT_EQ(5, m.top()->get_atr(0));
}

TEST_F(TestMachine, subtract_numberOperands_shouldCalculateAndReturnTheDifferenceOfTwoNumberOperands) {
    const vector<Instruction> prog ({
        Instruction(Code::PUSH, new Number(2)),
        Instruction(Code::PUSH, new Number(3)),
        Instruction(Code::SUB, nullptr),
        Instruction(Code::END, nullptr)});
    Machine m (prog);
    m.execute();
    EXPECT_EQ(-1, m.top()->get_atr(0));
}

TEST_F(TestMachine, multiply_numberOperands_shouldCalculateAndReturnTheProductOfTwoNumberOperands) {
    const vector<Instruction> prog ({
        Instruction(Code::PUSH, new Number(2)),
        Instruction(Code::PUSH, new Number(3)),
        Instruction(Code::MUL, nullptr),
        Instruction(Code::END, nullptr)});
    Machine m (prog);
    m.execute();
    EXPECT_EQ(6, m.top()->get_atr(0));
}

TEST_F(TestMachine, divide_numberOperands_shouldCalculateAndReturnTheQuotientOfTwoNumberOperands) {
    const vector<Instruction> prog ({
        Instruction(Code::PUSH, new Number(6)),
        Instruction(Code::PUSH, new Number(2)),
        Instruction(Code::DIV, nullptr),
        Instruction(Code::END, nullptr)});
    Machine m (prog);
    m.execute();
    EXPECT_EQ(3, m.top()->get_atr(0));
}

