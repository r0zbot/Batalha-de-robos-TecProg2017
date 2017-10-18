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
    MOUNTAIN, ///< Represents mountain terrains
    NONE,     ///< Represents normal terrains
    STREET    ///< Represents street terrains
};

#endif
