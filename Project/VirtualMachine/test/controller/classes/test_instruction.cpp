//#include <gtest/gtest.h>
//
//#include <application/component/hex.h>
//
//#include <controller/classes/action.h>
//#include <controller/classes/instruction.h>
//#include <controller/classes/number.h>
//
//class TestInstruction : public testing::Test {};
//
//TEST_F(TestInstruction, createInstruction_withNumberOperand_shouldCreateInstructionWithNumberOperand) {
//    Instruction i (Code::PUSH, make_shared<Number>(2));
//    ASSERT_EQ(Code::PUSH, i.get_code());
//    ASSERT_EQ(2, i.get_arg()->get_atr(0));
//}
//
//TEST_F(TestInstruction, createInstruction_withActionOperand_shouldCreateInstructionWithActionOperand) {
//    Instruction i (Code::PUSH, make_shared<Action>(SystemCode::COLLECT, Direction::NW));
//    ASSERT_EQ(Code::PUSH, i.get_code());
//    ASSERT_EQ(SystemCode::COLLECT, i.get_arg()->get_atr(0));
//    ASSERT_EQ(Direction::NW, i.get_arg()->get_atr(1));
//
//    i = Instruction(Code::RCE, make_shared<Action>(SystemCode::ATKLONG, Direction::NW));
//    ASSERT_EQ(Code::RCE, i.get_code());
//    ASSERT_EQ(SystemCode::ATKLONG, i.get_arg()->get_atr(0));
//    ASSERT_EQ(Direction::NW, i.get_arg()->get_atr(1));
//}
//
//TEST_F(TestInstruction, createInstruction_withHexOperand_shouldCreateInstructionWithHexOperand) {
//    Instruction i (Code::PUSH, make_shared<Hex>(0, 0));
//    ASSERT_EQ(Code::PUSH, i.get_code());
//    ASSERT_EQ(0, i.get_arg()->get_atr(0));
//    ASSERT_EQ(0, i.get_arg()->get_atr(1));
//    ASSERT_EQ(-1, i.get_arg()->get_atr(2));
//    ASSERT_EQ(-1, i.get_arg()->get_atr(3));
//
//    i = Instruction(Code::PUSH, make_shared<Hex>(0, 0, 2, 5, 10, Terrain::STREET));
//    ASSERT_EQ(Code::PUSH, i.get_code());
//    ASSERT_EQ(Terrain::STREET, i.get_arg()->get_atr(0));
//    ASSERT_EQ(10, i.get_arg()->get_atr(1));
//    ASSERT_EQ(5, i.get_arg()->get_atr(2));
//    ASSERT_EQ(2, i.get_arg()->get_atr(3));
//}
