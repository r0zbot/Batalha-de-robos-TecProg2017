#ifndef VIRTUALMACHINE_HEX_H
#define VIRTUALMACHINE_HEX_H

#include <unordered_set>
#include <vector>

#include <controller/classes/system.h>

#include <controller/interface/operand.h>

#include <model/entity/terrain.h>

using namespace std;

/**
 * @file  hex.h
 * @class Hex
 *
 * @brief The <b>Hex</b> class represents a flat-topped hexagonal position in a
 *        hexagonal grid of type "Even-Q".
 *
 * The <b>Hex</b> object represents one position in a hexagonal grid constructed
 * using an Offset Coordinate System. This system is the easiest approach to
 * represent a hexagonal multi-dimensional array with columns and rows.
 *
 * For performance and memory usages, this class provides an <b>Hash Code</b> so
 * it can be stored in hash tables and generate more efficient and generic grids.
 *
 * @see https://www.redblobgames.com/grids/hexagons/
 */
class Hex : public Operand {

    private:
        /**
         * Stores the id of a group of entities if
         * this position is a base of that group.
         *
         * If this positions is not a base of any group,
         * it stores -1.
         */
        int base;

        /**
         * Represents the column number in a hexagonal
         * multi-dimensional array.
         */
        int col;

        /**
         * Represents the amount of crystals present
         * in this position.
         */
        int crystals;

        /**
         * Represents the id of an entity present in
         * this position.
         *
         * If this position is empty, it stores -1.
         */
        int occup;

        /**
         * Represents the row number in a hexagonal
         * multi-dimensional array.
         */
        int row;

        /**
         * Represents the type of {@link Terrain} in
         * this position.
         */
        Terrain terrain;

    public:
        /**
         * @brief Constructs a Hexagon that represents the position [row][col]
         *        in a multi-dimensional array.
         *
         * @param [col]      The column number.
         * @param [row]      The row number.
         * @param [base]     The group's id who owns this position as a base.
         * @param [occup]    The entity's id present in this position.
         * @param [crystals] The number of crystal in this position.
         * @param [terrain]  The type of terrain in this position.
         */
        Hex(int col,
            int row,
            int base = -1,
            int occup = -1,
            int crystals = 0,
            Terrain terrain = Terrain::NONE);

        /**
         * @brief Copies the argument's attributes to this <b>Hex</b> object.
         *
         * @param [hex] The object that will be assigned to the function caller.
         *
         * @return A pointer to the new value of the function caller.
         */
        Hex& operator=(const Hex &hex);

        /**
         * @brief Overload of "equals" operator so it can compare two
         *        <b>Hex</b> objects.
         *
         * This method executes inner comparisons in both of the
         * hexagons's column and row, and return true only if the
         * columns and rows are equal.
         *
         * @param [hex] The hexagon to be compared to the caller object.
         *
         * @return True if the hexagons have the same column and row,
         *         false otherwise.
         */
        bool operator==(const Hex &hex) const;

        /**
         * @brief Overload of "not equals" operator so it can compare two
         *        <b>Hex</b> objects.
         *
         * This method executes inner comparisons in both of the
         * hexagons's column and row, and return true if their
         * columns are not equals or if their rows are different.
         *
         * @param [hex] The hexagon to be compared to the caller object.
         *
         * @return True if the hexagons have different columns or rows,
         *         false if they are equal.
         */
        bool operator!=(const Hex &hex) const;

        /**
         * @brief Calculates the cube distance between two hexagons in
         *        a Offset Coordinate System.
         *
         * It's only possible to calculate distances in a hexagonal grid
         * that uses Axial Coordinate System or Cube Coordinate System.
         * This method converts both of the hexagons to a Cube System
         * and find the distance between them, that is the length of the
         * line that contains both of their centers.
         *
         * @param [hex] The hexagon to be compared to the caller object.
         *
         * @return The distance between the center of the hexagons.
         */
        int distance(const Hex &hex) const;

        /**
         * @brief Returns the specified attribute.
         *
         * @param [i] An integer indicating which attribute should be returned.
         *
         * @return The specified attribute.
         */
        int get_atr(int i) const override;

        /**
         * @brief Gets the group's id who owns this <b>Hex</b> as a base.
         *
         * @return The group's id who owns this <b>Hex</b> as a base.
         */
        int get_base() const;

        /**
         * @brief Gets the hexagon column position.
         *
         * @return The hexagon column position.
         */
        int get_col() const;

        int get_crystals() const;

        /**
         * @brief Gets the entity's id present at this <b>Hex</b>.
         *
         * @return The entity's id present at this <b>Hex</b>.
         */
        int get_occup() const;

        /**
         * @brief Gets the hexagon row position.
         *
         * @return The hexagon row position.
         */
        int get_row() const;

        /**
         * @brief Gets the type of the {@link Terrain} at this <b>Hex</b>.
         *
         * @return The {@link Terrain} type at this <b>Hex</b>.
         */
        Terrain get_terrain() const;

        /**
         * @brief Gets the hexagon's neighbor at the specified direction.
         *
         * This method finds the hexagon's neighbor at the direction passed
         * as an argument.
         *
         * There are six possible directions in a flat-topped hexagonal grid,
         * and they can be accessed through {@link Direction}.
         *
         * @param [d] The {@link Direction} enum value representing a
         *            a direction.
         *
         * @return The neighbor at the specified direction.
         */
        Hex neighbor(Direction d) const;

        /**
         * @brief Finds every hexagon that is within n steps from this one.
         *
         * Given an origin (the function caller) and a range, this method
         * finds every hexagon that is within this range (n steps from the
         * origin).
         *
         * @param [n] The range size.
         *
         * @return An unordered set containing every hexagon that is n
         *         steps from the caller.
         */
        unordered_set<Hex> range(int n) const;

        /**
         * @brief Inserts a crystal into this cell.
         *
         * @return A boolean that indicates whether it was successfull or not.
         */
        bool insert_crystal();

        /**
         * @brief Removes a crystal from this cell.
         *
         * @return A boolean that indicates whether it was successful or not.
         */
        bool remove_crystal();

        /**
         * @brief Sets a new base at this <b>Hex</b>.
         *
         * @param [base] The group's id that owns this <b>Hex</b> as a base.
         */
        void set_base(int base);

        /**
         * @brief Sets a number of crystals at this <b>Hex</b>.
         *
         * @param [crystals] The new number of crystals at this <b>Hex</b>.
         */
        void set_crystals(int crystals);

        /**
         * @brief Sets a new entity at this <b>Hex</b>.
         *
         * @param [occup] The entity's id present at this <b>Hex</b>.
         */
        void set_occup(int occup);

        /**
         * @brief Sets the {@link Terrain} type at this <b>Hex</b>.
         *
         * @param [terrain] The new {@link Terrain} type at this <b>Hex</b>.
         */
        void set_terrain(Terrain terrain);

        /**
         * @brief Converts the hexagon offset coordinates to cube coordinates.
         *
         * @return A vector containing the coordinates of the hexagon in
         *         a Cube Coordinate System.
         */
        vector<int> to_cube() const;

        /**
         * @brief Converts cube coordinates to offset coordinates.
         *
         * This method converts coordinates from a Cube Coordinate System
         * to an Offset Coordinate System. As in cube coordinates the (y)
         * value is generated by the (x, z) values, its only necessary to
         * receive the (x, z) values to perform the conversion.
         *
         * @param [x] The x coordinate in the Cube Coordinate System.
         * @param [z] The z coordinate in the Cube Coordinate System.
         *
         * @return A <b>Hex</b> object with offset coordinates.
         */
        static Hex to_offset(int x, int z);
};

/**
 * @brief Overloading std hash function so it can generate  Hash Codes for
 *        <b>Hex</b> objects. This way <b>Hex</b> objects can be stored in hash tables.
 */
namespace std {
    template <> struct hash<Hex> {
        /**
         * @brief Generates a <b>Hash Code</b> for the specified {@link #Hex}.
         *
         * This methods generates a <b>Hash Code</b> based on the position
         * represented by the hexagon.
         *
         * @param [h] The {@link #Hex} object to generate the <b>Hash Code</b>
         *
         * @return The <b>Hash Code</b> for the specified {@link #Hex} object.
         */
        size_t operator()(const Hex &h) const {
            hash<int> int_hash;
            size_t hq = int_hash(h.get_col());
            size_t hr = int_hash(h.get_row());
            return hq ^ (hr + 0x9e3779b9 + (hq << 6) + (hq >> 2));
        }
    };
}

/**
 * Stores <b>Hex</b> objects representing one of the six possible directions
 * in a flat-topped "Even-Q" hexagonal grid.
 */
const Hex directions[2][6] = {
        {Hex(1, 0), Hex(0, -1), Hex(-1, 0), Hex(1, 1), Hex(0, 1), Hex(-1, 1)},
        {Hex(1, -1), Hex(0, -1), Hex(-1, -1), Hex(1, 0), Hex(0, 1), Hex(-1, 0)}
};

#endif
