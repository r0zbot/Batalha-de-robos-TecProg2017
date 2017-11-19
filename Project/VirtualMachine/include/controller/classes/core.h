#ifndef VIRTUALMACHINE_CORE_H
#define VIRTUALMACHINE_CORE_H

#ifdef linux
#include <unistd.h>
#include <limits.h>
#endif

#ifdef _WIN32
#include <windows.h>
#endif

#include <memory>

#include <controller/classes/arena.h>

#include <view/view.h>

using namespace std;

/**
 * @file  core.h
 * @class Core
 *
 * @brief This class controls the entire system and its properties.
 *
 * The <b>Core</b> class is in charge of controlling the game system during
 * the execution of its functions. This class manages the game cycle, which
 * includes three main phases: the <b>Load</b> phase, when every {@link #Entity}
 * in the game is initialized. The <b>Update</b> phase, when the entities in the
 * current game have their logic updated. The <b>Render</b> phase, when every
 * {@link #Entity} is rendered in the main screen.
 */
class Core {

    private:
        /**
         * Represents the {@link #Arena} for the current game.
         */
        Arena arena;

        /**
         * Represents the system sleep time in milliseconds.
         */
        const unsigned int sleep_time;

        /**
         * Represents the {@link #View} interface.
         */
        View view;

        /**
         * @brief Loads the entire game system.
         *
         * This method initializes the system, and
         * initializes all the game entities.
         */
        void on_load();

        /**
         * @brief Renders the entire game system.
         *
         * This method renders the system in the current {@link #View},
         * and renders all the game entities.
         */
        void on_render();

        /**
         * @brief Unload the entire game system.
         *
         * This method finishes the system execution,
         * and unload all the game entities.
         */
        void on_unload();

        /**
         * @brief Update the entire game system logic.
         *
         * This method updates the system logic, and
         * updates all the game entities logic.
         */
        void on_update();

        /**
         * @brief Pauses the system for a specific amount of time.
         */
        void sleep() const;

    public:
        /**
         * @brief Constructs a <b>Core</b> object to manage the system.
         *
         * @param [arena]      The {@link #Arena} in the current game.
         * @param [sleep_time] The system sleep time in milliseconds.
         */
        Core(const Arena &arena, unsigned int sleep_time);

        /**
         * @brief Gets the path to the final binary.
         *
         * @return The path to the final binary.
         */
        static string get_bin_path();

        /**
         * @brief Gets the path to the view project.
         *
         * @return The path to the view project.
         */
        static string get_view_path();

        /**
         * @brief Gets the path to an {@link #Entity} sprite.
         *
         * @return The path to to an {@link #Entity} sprite.
         */
        static string get_soldier_image_path(int army_id);

        /**
         * @brief Starts the execution of the game cycle.
         */
        void start();
};

#endif
