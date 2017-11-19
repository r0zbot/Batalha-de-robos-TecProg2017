#ifndef VIRTUALMACHINE_VIEW_H
#define VIRTUALMACHINE_VIEW_H

#include <memory>

#include <concat.hpp>

#include <model/interface/entity.h>

using namespace std;

/**
 * @file  view.h
 * @class View
 *
 * @brief This class represents a interface between the system,
 *        and the View Project.
 *
 * The <b>View</b> class establishes communication between
 * the game system and the view project, being responsible
 * for transfer the entities information to be draw on the
 * main screen.
 */
class View {

    private:
        /**
         * Stores a pointer to communicate with the View Project.
         */
        shared_ptr<FILE> window;

    public:
        /**
         * @brief Constructs a <b>View</b> object to communicate
         *        with the user interface.
         */
        View();

        /**
         * @brief Initializes the {@link #Arena} grid representation.
         *
         * @param [height] The height of the grid, or number of lines.
         *
         * @param [width]  The width of the grid, or number of columns.
         */
        void load(int height, int width) const;

        /**
         * @brief Initializes a specific cell in the {@link #Arena},
         *        with all its contents.
         *
         * This method loads the cell content in the system, including
         * {@link #Terrain} types, {@link #Army} bases, etc.
         *
         * @param [hex] The cell to be initialized.
         */
        void load(const Hex &hex) const;

        /**
         * @brief Initializes the view representation for an {@link #Entity}.
         *
         * @param [e] The {@link #Entity} whose view will be loaded.
         */
        void load(const Entity &e) const;

        /**
         * @brief Renders an {@link #Entity}, whose view was already loaded
         *        in the main screen.
         *
         * @param [e] The {@link #Entity} to be rendered.
         */
        void render(const Entity &e) const;

        /**
         * @brief Ends communication with the view project.
         */
        void unload();

        /**
         * @brief Updates the view content, previously loaded in the screen.
         */
        void update();
};

#endif
