#include <gtest/gtest.h>

#include <application/component/hex.h>

#include <controller/classes/action.h>
#include <controller/classes/instruction.h>
#include <controller/classes/number.h>

class TestInstruction : public testing::Test {};

TEST_F(TestInstruction, createInstruction_withNumberOperand_shouldCreateInstructionWithNumberOperand) {
    Instruction i (Code::PUSH, new Number(2));
    EXPECT_EQ(Code::PUSH, i.get_code());
    EXPECT_EQ(2, i.get_arg().get_atr(0));
}

TEST_F(TestInstruction, createInstruction_withActionOperand_shouldCreateInstructionWithActionOperand) {
    Instruction i (Code::PUSH, new Action(SystemCode::COLLECT, Direction::N));
    EXPECT_EQ(Code::PUSH, i.get_code());
    EXPECT_EQ(SystemCode::COLLECT, i.get_arg().get_atr(0));
    EXPECT_EQ(Direction::N, i.get_arg().get_atr(1));

    i = Instruction(Code::RCE, new Action(SystemCode::ATKLONG, Direction::NW));
    EXPECT_EQ(Code::RCE, i.get_code());
    EXPECT_EQ(SystemCode::ATKLONG, i.get_arg().get_atr(0));
    EXPECT_EQ(Direction::NW, i.get_arg().get_atr(1));
}

TEST_F(TestInstruction, createInstruction_withHexOperand_shouldCreateInstructionWithHexOperand) {
    Instruction i (Code::PUSH, new Hex(0, 0));
    EXPECT_EQ(Code::PUSH, i.get_code());
    EXPECT_EQ(Terrain::NONE, i.get_arg().get_atr(0));
    EXPECT_EQ(0, i.get_arg().get_atr(1));
    EXPECT_EQ(-1, i.get_arg().get_atr(2));
    EXPECT_EQ(-1, i.get_arg().get_atr(3));

    i = Instruction(Code::PUSH, new Hex(0, 0, 2, 5, 10, Terrain::STREET));
    EXPECT_EQ(Code::PUSH, i.get_code());
    EXPECT_EQ(Terrain::STREET, i.get_arg().get_atr(0));
    EXPECT_EQ(10, i.get_arg().get_atr(1));
    EXPECT_EQ(5, i.get_arg().get_atr(2));
    EXPECT_EQ(2, i.get_arg().get_atr(3));
}
