#ifndef VIRTUALMACHINE_ACTION_H
#define VIRTUALMACHINE_ACTION_H

#include <controller/classes/system.h>

#include <controller/interface/operand.h>

/**
 * @file action.h
 * @class Action
 *
 * @brief The <b>Action</b> class represents a general action to
 *        be executed in a specific {@link #Direction}.
 */
class Action : public Operand {

    private:
        /**
         * Represents the type of the action.
         */
        const SystemCode code;

        /**
         * Represents the direction where the action will be performed.
         */
        const Direction direction;

    public:
        /**
         * @brief Constructs an <b>Action</b> object with a specific
         *        {@link #SystemCode} and a {@link #Direction}.
         *
         * @param [code] The {@link #SystemCode} that represents the action.
         *
         * @param [direction] The {@link #Direction} where the action will be performed.
         */
        Action(SystemCode code, Direction direction);

        /**
         * @brief Return the specified <b>Operand</b> attribute.
         *
         * @param [i] The attribute position.
         *
         * @return The attribute at the specified position.
         */
        int get_atr(int i) const override;

        /**
         * @brief Gets the <b>Action</b> code.
         *
         * @return The <b>Action</b> code.
         */
        SystemCode get_code() const;

        /**
         * @brief Gets the direction where the action will be performed.
         *
         * @return The direction where the action will be performed.
         */
        Direction get_direction() const;

        /**
         * @brief Returns a string representation of this <b>Action</b> object.
         *
         * @return A string representation of this object.
         */
        string info() const override;
};

#endif
