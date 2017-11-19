#ifndef VIRTUALMACHINE_ARMY_H
#define VIRTUALMACHINE_ARMY_H

#include <map>

#include <memory>

#include <model/interface/entity_move.h>

#include <view/view.h>

using namespace std;

/**
 * @file  army.h
 * @class Army
 *
 * @brief This class represents a group of {@link #EntityMove} that can
 *        work together.
 */
class Army {

    private:
        /**
         * Represents a simple ID generator for any
         * army object created.
         */
        static int id_gen;

        /**
         * Represents the army's id, that is unique for every army.
         */
        const int id;

        /**
         * Represents the army's name.
         */
        const string name;

        /**
         * Stores the entities that belongs to this group.
         */
        map<int, EntityMovePtr> soldiers;

    public:
        /**
         * @brief Constructs an <b>Army</b> with the specified name.
         *
         * @param [name] The <b>Army's</b> name.
         */
        explicit Army(const string &name);

        /**
         * @brief Checks if this <b>Army</b> contains a soldier
         *        with the specified ID.
         *
         * @param [id] The searched soldier's ID.
         *
         * @return True if the searched soldier belongs to this
         *         <b>Army</b> and false otherwise.
         */
        bool contains_soldier(int id) const;

        /**
         * @brief Gets the army's id.
         *
         * @return The army's id.
         */
        int get_id() const;

        /**
         * @brief Gets the army's name.
         *
         * @return The army's name.
         */
        string get_name() const;

        /**
         * @brief Gets a pointer to an {@link #Entity} that belongs
         *        to this <b>Army</b> an has the specified ID.
         *
         * @param [id] The {@link #Entity} ID.
         *
         * @return A pointer to the searched {@link #Entity}.
         */
        EntityMovePtr get_soldier(int id);

        /**
         * @brief Inserts a soldier in this <b>Army</b>.
         *
         * @param [entityMove] The soldier to be inserted in this <b>Army</b>.
         */
        void insert_soldier(EntityMovePtr &soldier);

        /**
         * @brief Loads this <b>Army</b> in a @{link #View}.
         *
         * This methods initializes and loads all entities associated with
         * this <b>Army</b> into a {@link #View}.
         *
         * @param [view] The {@link #View} object that will show the army.
         */
        void load(const View &view) const;

        /**
         * @brief Removes, if exists, from this <b>Army</b> a soldier
         *        with the specified ID.
         *
         * @param [id] The soldier's ID that must be removed.
         */
        void remove_soldier(int id);

        /**
         * @brief Renders this <b>Army</b> in a @{link #View}.
         *
         * This methods renders all entities associated with
         * this <b>Army</b> into a {@link #View}.
         *
         * @param [view] The {@link #View} that will show this <b>Army</b>.
         */
        void render(const View &view);

        /**
         * @brief Gets the amount of soldiers present <b>Army</b>.
         *
         * @return The amount of soldiers present <b>Army</b>.
         */
        unsigned long size() const;

        /**
         * @brief Executes the <b>Army</b> logical behavior.
         *
         * This method executes the <b>Army</b> logical behavior and
         * also executes all its soldiers logical behavior.
         */
        void update();
};

#endif
