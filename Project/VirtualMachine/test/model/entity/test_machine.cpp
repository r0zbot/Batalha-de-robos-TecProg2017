#include <vector>

#include <gtest/gtest.h>

#include <controller/classes/action.h>
#include <controller/classes/number.h>

#include <model/entity/machine.h>

using namespace std;

class TestMachine : public testing::Test {};

TEST_F(TestMachine, push_numberOperand_shouldPushNumberOperandToMachineStack) {
    const vector<Instruction> prog ({
        Instruction(Code::PUSH, new Number(9)),
        Instruction(Code::END,  nullptr)});
    Machine m (prog);
    m.execute();

    auto top = dynamic_cast<Number*>(m.top());
    assert(top);
    ASSERT_EQ(9, top->get_value());
}

TEST_F(TestMachine, push_actionOperand_shouldPushActionOperandToMachineStack) {
    const vector<Instruction> prog ({
        Instruction(Code::PUSH, new Action(SystemCode::ATKLONG, Direction::NW)),
        Instruction(Code::END,  nullptr)});
    Machine m (prog);
    m.execute();

    auto top = dynamic_cast<Action*>(m.top());
    assert(top);
    ASSERT_EQ(SystemCode::ATKLONG, top->get_code());
    ASSERT_EQ(Direction::NW, top->get_direction());
}

TEST_F(TestMachine, push_hexOperand_shouldPushHexOperandToMachineStack) {
    const vector<Instruction> prog ({
        Instruction(Code::PUSH, new Hex(0, 0, 2)),
        Instruction(Code::END,  nullptr)});
    Machine m (prog);
    m.execute();

    auto top = dynamic_cast<Hex*>(m.top());
    assert(top);
    ASSERT_EQ(0,  top->get_col());
    ASSERT_EQ(0,  top->get_row());
    ASSERT_EQ(2,  top->get_base());
    ASSERT_EQ(-1, top->get_occup());
    ASSERT_EQ(Terrain::NONE, top->get_terrain());
}

TEST_F(TestMachine, add_numberOperands_shouldCalculateAndReturnTheSumOfTwoNumberOperands) {
    const vector<Instruction> prog ({
        Instruction(Code::PUSH, new Number(2)),
        Instruction(Code::PUSH, new Number(3)),
        Instruction(Code::ADD,  nullptr),
        Instruction(Code::END,  nullptr)});
    Machine m (prog);
    m.execute();

    auto top = dynamic_cast<Number*>(m.top());
    assert(top);
    ASSERT_EQ(5, top->get_value());
}

TEST_F(TestMachine, subtract_numberOperands_shouldCalculateAndReturnTheDifferenceOfTwoNumberOperands) {
    const vector<Instruction> prog ({
        Instruction(Code::PUSH, new Number(2)),
        Instruction(Code::PUSH, new Number(3)),
        Instruction(Code::SUB,  nullptr),
        Instruction(Code::END,  nullptr)});
    Machine m (prog);
    m.execute();

    auto top = dynamic_cast<Number*>(m.top());
    assert(top);
    ASSERT_EQ(-1, top->get_value());
}

TEST_F(TestMachine, multiply_numberOperands_shouldCalculateAndReturnTheProductOfTwoNumberOperands) {
    const vector<Instruction> prog ({
        Instruction(Code::PUSH, new Number(2)),
        Instruction(Code::PUSH, new Number(3)),
        Instruction(Code::MUL,  nullptr),
        Instruction(Code::END,  nullptr)});
    Machine m (prog);
    m.execute();

    auto top = dynamic_cast<Number*>(m.top());
    assert(top);
    ASSERT_EQ(6, top->get_value());
}

TEST_F(TestMachine, divide_numberOperands_shouldCalculateAndReturnTheQuotientOfTwoNumberOperands) {
    const vector<Instruction> prog ({
        Instruction(Code::PUSH, new Number(6)),
        Instruction(Code::PUSH, new Number(2)),
        Instruction(Code::DIV,  nullptr),
        Instruction(Code::END,  nullptr)});
    Machine m (prog);
    m.execute();

    auto top = dynamic_cast<Number*>(m.top());
    assert(top);
    ASSERT_EQ(3, top->get_value());
}

TEST_F(TestMachine, duplicate_numberOperands_shouldDuplicateTheTopmostElementOfTheStack) {
    const vector<Instruction> prog ({
        Instruction(Code::PUSH, new Number(6)),
        Instruction(Code::DUP,  nullptr),
        Instruction(Code::END,  nullptr)});
    Machine m (prog);
    m.execute();

    auto top = dynamic_cast<Number*>(m.top());
    assert(top);
    ASSERT_EQ(6, top->get_value());
}

TEST_F(TestMachine, duplicate_actionOperands_shouldDuplicateTheTopmostElementOfTheStack) {
    const vector<Instruction> prog ({
        Instruction(Code::PUSH, new Action(SystemCode::COLLECT, Direction::NW)),
        Instruction(Code::DUP,  nullptr),
        Instruction(Code::END,  nullptr)});
    Machine m (prog);
    m.execute();

    auto top = dynamic_cast<Action*>(m.top());
    assert(top);
    ASSERT_EQ(SystemCode::COLLECT, top->get_code());
    ASSERT_EQ(Direction::NW, top->get_direction());
}

TEST_F(TestMachine, duplicate_hexOperand_shouldDuplicateTheTopmostElementOfTheStack) {
    const vector<Instruction> prog ({
        Instruction(Code::PUSH, new Hex(0, 0)),
        Instruction(Code::DUP,  nullptr),
        Instruction(Code::END,  nullptr)});
    Machine m (prog);
    m.execute();

    auto top = dynamic_cast<Hex*>(m.top());
    assert(top);
    ASSERT_EQ(0,  top->get_col());
    ASSERT_EQ(0,  top->get_row());
    ASSERT_EQ(-1, top->get_base());
    ASSERT_EQ(-1, top->get_occup());
    ASSERT_EQ(Terrain::NONE, top->get_terrain());
}

TEST_F(TestMachine, atr_actionOperand_shouldPushActionOperandAttributeToMachineStack) {
    const vector<Instruction> prog ({
        Instruction(Code::PUSH, new Action(SystemCode::ATKLONG, Direction::NW)),
        Instruction(Code::ATR,  new Number(1)),
        Instruction(Code::END,  nullptr)});
    Machine m (prog);
    m.execute();
    ASSERT_EQ(Direction::NW, m.top()->get_atr(0));
}

TEST_F(TestMachine, atr_hexOperand_shouldPushHexOperandAttributeToMachineStack) {
    const vector<Instruction> prog ({
        Instruction(Code::PUSH, new Hex(0, 0, 5)),
        Instruction(Code::ATR,  new Number(3)),
        Instruction(Code::END,  nullptr)});
    Machine m (prog);
    m.execute();
    ASSERT_EQ(5, m.top()->get_atr(0));
}
