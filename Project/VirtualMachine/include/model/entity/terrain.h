#ifndef VIRTUALMACHINE_TERRAIN_H
#define VIRTUALMACHINE_TERRAIN_H

/**
 * @file terrain.h
 * @enum Terrain
 *
 * @brief The <b>Terrain</b> is a strongly typed enum that defines
 *        types of terrains that can exists in a grid cell.
 */
enum Terrain {
    MOUNTAIN = 0, ///< Represents mountain terrains
    NONE     = 1, ///< Represents normal terrains
    STREET   = 2  ///< Represents street terrains
};

#endif
