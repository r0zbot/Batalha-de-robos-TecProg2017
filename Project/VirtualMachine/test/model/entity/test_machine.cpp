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

TEST_F(TestMachine, push_actionOperand_shouldPushActionOperandToMachineStack) {
    const vector<Instruction> prog ({
        Instruction(Code::PUSH, new Action(SystemCode::ATKLONG, Direction::NW)),
        Instruction(Code::END, nullptr)});
    Machine m (prog);
    m.execute();
    EXPECT_EQ(SystemCode::ATKLONG, m.top()->get_atr(0));
    EXPECT_EQ(Direction::NW, m.top()->get_atr(1));
}

TEST_F(TestMachine, push_hexOperand_shouldPushHexOperandToMachineStack) {
    const vector<Instruction> prog ({
        Instruction(Code::PUSH, new Hex(0, 0, 2)),
        Instruction(Code::END, nullptr)});
    Machine m (prog);
    m.execute();
    EXPECT_EQ(Terrain::NONE, m.top()->get_atr(0));
    EXPECT_EQ(0, m.top()->get_atr(1));
    EXPECT_EQ(-1, m.top()->get_atr(2));
    EXPECT_EQ(2, m.top()->get_atr(3));
}

TEST_F(TestMachine, atr_validOperand_shouldPushOperandAttributeToMachineStack) {
    const vector<Instruction> prog ({
        Instruction(Code::PUSH, new Action(SystemCode::ATKLONG, Direction::NW)),
        Instruction(Code::ATR, new Number(1)),
        Instruction(Code::END, nullptr)});
    Machine m (prog);
    m.execute();
    EXPECT_EQ(Direction::NW, m.top()->get_atr(0));

    const vector<Instruction> prog2 ({
        Instruction(Code::PUSH, new Hex(0, 0, 5)),
        Instruction(Code::ATR, new Number(3)),
        Instruction(Code::END, nullptr)});
    Machine m2 (prog2);
    m2.execute();
    EXPECT_EQ(5, m2.top()->get_atr(0));
}