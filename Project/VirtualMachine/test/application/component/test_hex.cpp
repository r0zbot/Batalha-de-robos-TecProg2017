#include <unordered_map>

#include <gtest/gtest.h>

#include <application/component/hex.h>

using namespace std;

class TestHex : public ::testing::Test {};

TEST_F(TestHex, should_generate_correct_hash_code_for_different_hex_objects) {
    unordered_map<Hex, int> map;

    Hex hex  (0, 0);
    Hex hex1 (0, 1);
    Hex hex2 (1, 0);

    map[hex]  = 0;
    map[hex1] = 1;
    map[hex2] = 2;
    EXPECT_EQ(3, map.size());
    EXPECT_EQ(0, map[hex]);
    EXPECT_EQ(1, map[hex1]);
    EXPECT_EQ(2, map[hex2]);

    map.erase(hex1);
    EXPECT_EQ(2, map.size());
    EXPECT_EQ(map.find(hex1), map.end());

    map[hex] = 3;
    EXPECT_EQ(2, map.size());
    EXPECT_EQ(3, map[hex]);
}

TEST_F(TestHex, should_return_correct_neighbor_at_specified_direction_from_origin) {
    Hex origin (0, 0);

    EXPECT_EQ(1, origin.neighbor(Direction::NE).get_col());
    EXPECT_EQ(0, origin.neighbor(Direction::NE).get_row());

    EXPECT_EQ(0, origin.neighbor(Direction::N).get_col());
    EXPECT_EQ(-1, origin.neighbor(Direction::N).get_row());

    EXPECT_EQ(-1, origin.neighbor(Direction::NW).get_col());
    EXPECT_EQ(0, origin.neighbor(Direction::NW).get_row());

    EXPECT_EQ(1, origin.neighbor(Direction::SE).get_col());
    EXPECT_EQ(1, origin.neighbor(Direction::SE).get_row());

    EXPECT_EQ(0, origin.neighbor(Direction::S).get_col());
    EXPECT_EQ(1, origin.neighbor(Direction::S).get_row());

    EXPECT_EQ(-1, origin.neighbor(Direction::SW).get_col());
    EXPECT_EQ(1, origin.neighbor(Direction::SW).get_row());
}

TEST_F(TestHex, should_return_correct_neighbor_at_specified_direction_from_random_point) {
    Hex point (3, 2);

    EXPECT_EQ(4, point.neighbor(Direction::NE).get_col());
    EXPECT_EQ(1, point.neighbor(Direction::NE).get_row());

    EXPECT_EQ(3, point.neighbor(Direction::N).get_col());
    EXPECT_EQ(1, point.neighbor(Direction::N).get_row());

    EXPECT_EQ(2, point.neighbor(Direction::NW).get_col());
    EXPECT_EQ(1, point.neighbor(Direction::NW).get_row());

    EXPECT_EQ(4, point.neighbor(Direction::SE).get_col());
    EXPECT_EQ(2, point.neighbor(Direction::SE).get_row());

    EXPECT_EQ(3, point.neighbor(Direction::S).get_col());
    EXPECT_EQ(3, point.neighbor(Direction::S).get_row());

    EXPECT_EQ(2, point.neighbor(Direction::SW).get_col());
    EXPECT_EQ(2, point.neighbor(Direction::SW).get_row());
}

TEST_F(TestHex, should_execute_equals_operator_correctly) {
    Hex a (0, 0);
    Hex b (0, 0);
    Hex c (1, 0);
    EXPECT_TRUE (a == a);
    EXPECT_TRUE (a == b);
    EXPECT_TRUE (b == a);
    EXPECT_FALSE(a == c);
    EXPECT_FALSE(b == c);
    EXPECT_FALSE(c == a);
    EXPECT_FALSE(c == b);
}

TEST_F(TestHex, should_execute_not_equals_operator_correctly) {
    Hex a (0, 0);
    Hex b (0, 0);
    Hex c (1, 0);
    EXPECT_FALSE(a != a);
    EXPECT_FALSE(a != b);
    EXPECT_FALSE(b != a);
    EXPECT_TRUE (a != c);
    EXPECT_TRUE (b != c);
    EXPECT_TRUE (c != a);
    EXPECT_TRUE (c != b);
}

TEST_F(TestHex, should_convert_offset_coordinates_to_cube_coordinates) {
    const vector<int> cube = Hex(2, 1).to_cube();
    EXPECT_EQ(2, cube[0]);
    EXPECT_EQ(-2, cube[1]);
    EXPECT_EQ(0, cube[2]);

    const vector<int> origin = Hex(0, 0).to_cube();
    EXPECT_EQ(0, origin[0]);
    EXPECT_EQ(0, origin[1]);
    EXPECT_EQ(0, origin[2]);
}

TEST_F(TestHex, should_convert_cube_coordinates_to_offset_coordinates) {
    Hex origin = Hex::to_offset(0, 0);
    EXPECT_EQ(0, origin.get_col());
    EXPECT_EQ(0, origin.get_row());

    Hex hex = Hex::to_offset(2, 0);
    EXPECT_EQ(2, hex.get_col());
    EXPECT_EQ(1, hex.get_row());
}

TEST_F(TestHex, should_return_all_hex_in_a_specified_range) {
    Hex center (3, 3);
    const unordered_set<Hex> response = center.range(2);
    EXPECT_EQ(18, response.size());
    EXPECT_EQ(1, response.count(Hex (3, 2)));
    EXPECT_EQ(1, response.count(Hex (4, 2)));
    EXPECT_EQ(1, response.count(Hex (4, 3)));
    EXPECT_EQ(1, response.count(Hex (3, 4)));
    EXPECT_EQ(1, response.count(Hex (2, 3)));
    EXPECT_EQ(1, response.count(Hex (2, 2)));
    EXPECT_EQ(1, response.count(Hex (3, 1)));
    EXPECT_EQ(1, response.count(Hex (4, 1)));
    EXPECT_EQ(1, response.count(Hex (5, 2)));
    EXPECT_EQ(1, response.count(Hex (5, 3)));
    EXPECT_EQ(1, response.count(Hex (5, 4)));
    EXPECT_EQ(1, response.count(Hex (4, 4)));
    EXPECT_EQ(1, response.count(Hex (3, 5)));
    EXPECT_EQ(1, response.count(Hex (2, 4)));
    EXPECT_EQ(1, response.count(Hex (1, 4)));
    EXPECT_EQ(1, response.count(Hex (1, 3)));
    EXPECT_EQ(1, response.count(Hex (1, 2)));
    EXPECT_EQ(1, response.count(Hex (2, 1)));
}
