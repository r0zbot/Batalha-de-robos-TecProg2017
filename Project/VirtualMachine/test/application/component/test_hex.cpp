#include <unordered_map>

#include <gtest/gtest.h>

#include <application/component/hex.h>

using namespace std;

class TestHex : public ::testing::Test {};

TEST_F(TestHex, hashFunction_validData_shouldGenerateDifferentHashCodesForDifferentHexObjects) {
    unordered_map<Hex, int> map;

    Hex hex  (0, 0);
    Hex hex1 (0, 1);
    Hex hex2 (1, 0);

    map[hex]  = 0;
    map[hex1] = 1;
    map[hex2] = 2;
    ASSERT_EQ(3, map.size());
    ASSERT_EQ(0, map[hex]);
    ASSERT_EQ(1, map[hex1]);
    ASSERT_EQ(2, map[hex2]);

    map.erase(hex1);
    ASSERT_EQ(2, map.size());
    ASSERT_EQ(map.find(hex1), map.end());

    map[hex] = 3;
    ASSERT_EQ(2, map.size());
    ASSERT_EQ(3, map[hex]);
}

TEST_F(TestHex, neighbor_evenRowHex_shouldReturnCorrectNeighborAtSpecifiedDirection) {
    Hex origin (0, 0);

    ASSERT_EQ(-1, origin.neighbor(Direction::NE).get_row());
    ASSERT_EQ(0,  origin.neighbor(Direction::NE).get_col());

    ASSERT_EQ(-1, origin.neighbor(Direction::NW).get_row());
    ASSERT_EQ(-1, origin.neighbor(Direction::NW).get_col());

    ASSERT_EQ(0,  origin.neighbor(Direction::EA).get_row());
    ASSERT_EQ(1,  origin.neighbor(Direction::EA).get_col());

    ASSERT_EQ(0,  origin.neighbor(Direction::WE).get_row());
    ASSERT_EQ(-1, origin.neighbor(Direction::WE).get_col());

    ASSERT_EQ(1,  origin.neighbor(Direction::SE).get_row());
    ASSERT_EQ(0,  origin.neighbor(Direction::SE).get_col());

    ASSERT_EQ(1,  origin.neighbor(Direction::SW).get_row());
    ASSERT_EQ(-1, origin.neighbor(Direction::SW).get_col());
}

TEST_F(TestHex, neighbor_oddRowHex_shouldReturnCorrectNeighborAtSpecifiedDirection) {
    Hex point (3, 2);

    ASSERT_EQ(2, point.neighbor(Direction::NE).get_row());
    ASSERT_EQ(3, point.neighbor(Direction::NE).get_col());

    ASSERT_EQ(2, point.neighbor(Direction::NW).get_row());
    ASSERT_EQ(2, point.neighbor(Direction::NW).get_col());

    ASSERT_EQ(3, point.neighbor(Direction::EA).get_row());
    ASSERT_EQ(3, point.neighbor(Direction::EA).get_col());

    ASSERT_EQ(3, point.neighbor(Direction::WE).get_row());
    ASSERT_EQ(1, point.neighbor(Direction::WE).get_col());

    ASSERT_EQ(4, point.neighbor(Direction::SE).get_row());
    ASSERT_EQ(3, point.neighbor(Direction::SE).get_col());

    ASSERT_EQ(4, point.neighbor(Direction::SW).get_row());
    ASSERT_EQ(2, point.neighbor(Direction::SW).get_col());
}

TEST_F(TestHex, equalsOperator_equalAndNotEqualInput_shouldReturnTrueWhenEqualsAndFalseOtherwise) {
    Hex a (0, 0);
    Hex b (0, 0);
    Hex c (1, 0);
    ASSERT_TRUE (a == a);
    ASSERT_TRUE (a == b);
    ASSERT_TRUE (b == a);
    ASSERT_FALSE(a == c);
    ASSERT_FALSE(b == c);
    ASSERT_FALSE(c == a);
    ASSERT_FALSE(c == b);
}

TEST_F(TestHex, notEqualsOperator_equalAndNotEqualInput_shouldReturnTrueWhenNotEqualsAndFalseOtherwise) {
    Hex a (0, 0);
    Hex b (0, 0);
    Hex c (1, 0);
    ASSERT_FALSE(a != a);
    ASSERT_FALSE(a != b);
    ASSERT_FALSE(b != a);
    ASSERT_TRUE (a != c);
    ASSERT_TRUE (b != c);
    ASSERT_TRUE (c != a);
    ASSERT_TRUE (c != b);
}

TEST_F(TestHex, toCube_offsetInput_shouldConvertOffsetCoordinatesToCubeCoordinates) {
    const vector<int> cube = Hex(2, 1).to_cube();
    ASSERT_EQ(0,  cube[0]);
    ASSERT_EQ(-2, cube[1]);
    ASSERT_EQ(2,  cube[2]);

    const vector<int> origin = Hex(0, 0).to_cube();
    ASSERT_EQ(0, origin[0]);
    ASSERT_EQ(0, origin[1]);
    ASSERT_EQ(0, origin[2]);
}

TEST_F(TestHex, toOffset_cubeInput_shouldConvertCubeCoordinatesToOffsetCoordinates) {
    Hex origin = Hex::to_offset(0, 0);
    ASSERT_EQ(0, origin.get_col());
    ASSERT_EQ(0, origin.get_row());

    Hex hex = Hex::to_offset(2, 0);
    ASSERT_EQ(2, hex.get_col());
    ASSERT_EQ(0, hex.get_row());
}

TEST_F(TestHex, range_randomPoint_shouldReturnAllHexWhitinSpecifiedRange) {
    Hex center (3, 3);
    const unordered_set<Hex> response = center.range(2);
    ASSERT_EQ(18, response.size());
    ASSERT_EQ(1, response.count(Hex (5, 4)));
    ASSERT_EQ(1, response.count(Hex (5, 2)));
    ASSERT_EQ(1, response.count(Hex (2, 3)));
    ASSERT_EQ(1, response.count(Hex (2, 4)));
    ASSERT_EQ(1, response.count(Hex (3, 4)));
    ASSERT_EQ(1, response.count(Hex (4, 3)));
    ASSERT_EQ(1, response.count(Hex (3, 2)));
    ASSERT_EQ(1, response.count(Hex (2, 2)));
    ASSERT_EQ(1, response.count(Hex (1, 3)));
    ASSERT_EQ(1, response.count(Hex (1, 4)));
    ASSERT_EQ(1, response.count(Hex (2, 5)));
    ASSERT_EQ(1, response.count(Hex (3, 5)));
    ASSERT_EQ(1, response.count(Hex (4, 5)));
    ASSERT_EQ(1, response.count(Hex (4, 4)));
    ASSERT_EQ(1, response.count(Hex (5, 3)));
    ASSERT_EQ(1, response.count(Hex (4, 2)));
    ASSERT_EQ(1, response.count(Hex (3, 1)));
    ASSERT_EQ(1, response.count(Hex (1, 2)));
}
