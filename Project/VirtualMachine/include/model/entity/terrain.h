#ifndef VIRTUALMACHINE_TERRAIN_H
#define VIRTUALMACHINE_TERRAIN_H

/**
 * @file terrain.h
 * @enum Terrain
 *
 * @brief The <b>Terrain</b> is a strongly typed enum that defines
 *        types of terrains that can exists in a grid cell.
 */
enum class Terrain {
    NONE     = 0, ///< Represents normal terrains
    MOUNTAIN = 1, ///< Represents mountain terrains
    STREET   = 2, ///< Represents street terrains
    ROCK     = 3, ///< Represents a rock, so entities can't occupy this space
    GRASS    = 4  ///< Represents grass terrains
};

#endif
