#include <vector>

#include <gtest/gtest.h>

#include <controller/classes/number.h>

#include <model/entity/army.h>
#include <model/entity/machine.h>

using namespace std;

class TestArmy : public testing::Test {

    public:
        vector<EntityMovePtr> soldiersA;
        vector<EntityMovePtr> soldiersB;

        TestArmy() {
            for (int i = 0; i < 10; i++) {
                this->soldiersA.push_back(
                        make_shared<Machine>(Program({Instruction(Code::PUSH, make_shared<Number>(1))}), Hex(0, i)));

                this->soldiersB.push_back(
                        make_shared<Machine>(Program({Instruction(Code::PUSH, make_shared<Number>(1))}), Hex(8, i)));
            }
        }
};

TEST_F(TestArmy, constructArmy_withValidName_shouldConstructArmyWithGivenNameAndDifferentIds) {
    Army a ("Army a");
    Army b ("Army b");

    ASSERT_EQ(0, a.get_id());
    ASSERT_EQ("Army a", a.get_name());

    ASSERT_EQ(1, b.get_id());
    ASSERT_EQ("Army b", b.get_name());
}

TEST_F(TestArmy, insertSoldier_defaultData_shouldEmplaceSoldierWithArmyId) {
    Army a ("Army a");
    Army b ("Army b");

    for (auto &e : this->soldiersA) {
        a.insert_soldier(e);
        ASSERT_EQ(a.get_id(), e->get_group_id());
        ASSERT_EQ(a.get_id(), a.get_soldier(e->get_id())->get_group_id());
    }
    for (auto &e : this->soldiersB) {
        b.insert_soldier(e);
        ASSERT_EQ(b.get_id(), e->get_group_id());
        ASSERT_EQ(b.get_id(), b.get_soldier(e->get_id())->get_group_id());
    }
}

TEST_F(TestArmy, size_defaultData_shouldGenerateArmiesWithTheSameSizeAsTheInput) {
    Army a ("Army a");
    Army b ("Army b");

    for (auto &e : this->soldiersA) {
        a.insert_soldier(e);
    }
    for (auto &e : this->soldiersB) {
        b.insert_soldier(e);
    }
    ASSERT_EQ(this->soldiersA.size(), a.size());
    ASSERT_EQ(this->soldiersB.size(), b.size());
}

TEST_F(TestArmy, getSoldier_validSoldierId_shouldReturnPointerToSearchedSoldier) {
    Army a ("Army a");

    for (auto &e : this->soldiersA) {
        a.insert_soldier(e);
    }
    for (auto const &e : this->soldiersA) {
        ASSERT_EQ(e, a.get_soldier(e->get_id()));
    }
}

TEST_F(TestArmy, getSoldier_invalidSoldierId_shouldReturnNullPointer) {
    Army a ("Army a");
    ASSERT_EQ(nullptr, a.get_soldier(0));
}

TEST_F(TestArmy, containsSoldier_invalidSoldierId_shouldReturnFalse) {
    Army b ("Army b");

    for (auto &e : this->soldiersB) {
        b.insert_soldier(e);
    }
    for (auto const &e : this->soldiersA) {
        ASSERT_FALSE(b.contains_soldier(e->get_id()));
    }
}

TEST_F(TestArmy, containsSoldier_validSoldierId_shouldReturnTrue) {
    Army a ("Army a");

    for (auto &e : this->soldiersA) {
        a.insert_soldier(e);
    }
    for (auto const &e : this->soldiersA) {
        ASSERT_TRUE(a.contains_soldier(e->get_id()));
    }
}

TEST_F(TestArmy, removeSoldier_validSoldierId_shouldRemoveSoldierFromArmy) {
    Army a ("Army a");

    for (auto &e : this->soldiersA) {
        a.insert_soldier(e);
    }
    ASSERT_EQ(this->soldiersA.size(), a.size());

    a.remove_soldier(this->soldiersA[2]->get_id());
    ASSERT_EQ(this->soldiersA.size() - 1, a.size());
    ASSERT_FALSE(a.contains_soldier(this->soldiersA[2]->get_id()));
}

TEST_F(TestArmy, removeSoldier_invalidSoldierId_shouldRemoveNothingFromArmy) {
    Army a ("Army a");

    for (auto &e : this->soldiersA) {
        a.insert_soldier(e);
    }
    ASSERT_EQ(this->soldiersA.size(), a.size());

    a.remove_soldier(this->soldiersB[2]->get_id());
    ASSERT_EQ(this->soldiersA.size(), a.size());
}
