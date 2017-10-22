//#include <vector>
//
//#include <gtest/gtest.h>
//
//#include <model/entity/army.h>
//#include <model/entity/machine.h>
//
//using namespace std;
//
//class TestArmy : public testing::Test {
//
//    public:
//        vector<EntityMove*> soldiersA;
//        vector<EntityMove*> soldiersB;
//
//        TestArmy() {
//            for (int i = 0; i < 10; i++) {
//                this->soldiersA.push_back(new Machine({Instruction(Code::PUSH, 1)}, Hex(0, i)));
//                this->soldiersA.push_back(new Machine({Instruction(Code::PUSH, 1)}, Hex(8, i)));
//            }
//        }
//};
//
//TEST_F(TestArmy, createArmy_defaultData_shouldGenerateArmiesWithDifferentsIds) {
//    Army a (this->soldiersA);
//    Army b (this->soldiersB);
//    EXPECT_NE(a.get_id(), b.get_id());
//}
//
//TEST_F(TestArmy, createArmy_defaultData_shouldEmplaceSoldierWithArmyId) {
//    Army a (this->soldiersA);
//    Army b (this->soldiersB);
//    for (auto const &e : this->soldiersA) {
//        EXPECT_EQ(a.get_id(), a.get_soldier(e->get_id())->get_group_id());
//    }
//    for (auto const &e : this->soldiersB) {
//        EXPECT_EQ(b.get_id(), b.get_soldier(e->get_id())->get_group_id());
//    }
//}
//
//TEST_F(TestArmy, size_defaultData_shouldGenerateArmiesWithTheSameSizeAsTheInput) {
//    Army a (this->soldiersA);
//    Army b (this->soldiersB);
//    EXPECT_EQ(this->soldiersA.size(), a.size());
//    EXPECT_EQ(this->soldiersB.size(), b.size());
//}
//
//TEST_F(TestArmy, containsSoldier_validSoldierId_shouldReturnTrue) {
//    Army a (this->soldiersA);
//    for (auto const &e : this->soldiersA) {
//        EXPECT_TRUE(a.contains_soldier(e->get_id()));
//    }
//}
//
//TEST_F(TestArmy, containsSoldier_invalidSoldierId_shouldReturnFalse) {
//    Army b (this->soldiersB);
//    for (auto const &e : this->soldiersA) {
//        EXPECT_FALSE(b.contains_soldier(e->get_id()));
//    }
//}
//
//TEST_F(TestArmy, getSoldier_validSoldierId_shouldReturnReferenceToSearchedSoldier) {
//    Army a (this->soldiersA);
//    for (auto const &e : this->soldiersA) {
//        EXPECT_EQ(e, a.get_soldier(e->get_id()));
//    }
//}
//
//TEST_F(TestArmy, removeSoldier_validSoldierId_shouldRemoveSoldierFromArmy) {
//    Army a (this->soldiersA);
//    EXPECT_EQ(this->soldiersA.size(), a.size());
//
//    a.remove_soldier(this->soldiersA[2]->get_id());
//    EXPECT_EQ(this->soldiersA.size() - 1, a.size());
//    EXPECT_FALSE(a.contains_soldier(this->soldiersA[2]->get_id()));
//}
