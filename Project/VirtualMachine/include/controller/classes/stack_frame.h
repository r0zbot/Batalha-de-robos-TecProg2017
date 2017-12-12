#ifndef VIRTUALMACHINE_STACK_FRAME_H
#define VIRTUALMACHINE_STACK_FRAME_H

#include <stack>
#include <vector>

#include <controller/interface/operand.h>

using namespace std;

/**
 * @file  stack_frame.h
 * @class StackFrame
 *
 * @brief The <b>StackFrame</b> class is the collection of all data on
 * the stack associated with programs subcalls.
 *
 * The <b>StackFrame</b> class allow access to both function parameters,
 * and automatic/local function variables.
 *
 * When a function is called, a new partition is created at the current
 * top pointer location. The <b>StackFrame</b> acts like a partition of
 * the {@link #Machine} data stack. All items from previous functions are
 * in the "bottom" of the <b>StackFrame</b>, and should not be modified.
 * Each current function has access to the remainder of the stack, from
 * the <b>StackFrame</b> until the end of the stack page. The current
 * function always has access to the "top" of the stack, and so functions
 * do not need to take account of the memory usage of other functions or programs.
 *
 * When the program enters a block such a function or method, space must be
 * allocated on top of the <b>StackFrame</b> for the local variables inside
 * the function scope. When the program leaves the block, the space must be freed again.
 */
class StackFrame {

    private:
        /**
         * Stores all functions local variables that are being used in
         * subprogram calls and all the callers returning addresses.
         */
        vector<OperandPtr> data;

        /**
         * Stores all the entries values that still being used
         * in function calls.
         */
        stack<int> entries;

        /**
         * Represents the "Base Pointer" for the current function
         * so that all parameters and local variables would be at
         * a fixed offset from this pointer.
         */
        int entry;

        /**
         * Stores all the return address for functions.
         */
        stack<int> history;

    public:
        /**
         * @brief Constructs a <b>StackFrame</b> with the specified size.
         *
         * @param [size] The <b>StackFrame</b> size.
         */
        explicit StackFrame(unsigned long size);

        /**
         * @brief  Sets the specified offset from the current
         *         base pointer.
         *
         * @param  [n] The offset from current base pointer.
         *
         * @throws FrameOperationException if impossible to allocate
         *         the specified amount of space.
         */
        void offset(int n);

        /**
         * @brief  Returns the address from where the {@link #Machine}
         *         shall continue the program execution.
         *
         * @return The address from where the {@link #Machine}
         *         shall continue the program execution.
         */
        int back();

        /**
         * @brief   Returns the element at an "i" offset from the
         *          current base pointer value.
         *
         * @param   [i] The offset from the current base pointer.
         *
         * @return  The element at the specified offset from
         *          the current base pointer value.
         *
         * @throws  FrameOperationException if the position specified
         *          is out of the current <b>StackFrame</b> scope.
         */
        OperandPtr get(int i) const;

        /**
         * @brief  Stores the address to the last function call.
         *
         * @param  [address] The address to the last function call.
         */
        void push(int address);

        /**
         * @brief Resets all the StackFrame content.
         */
        void reset();

        /**
         * @brief  Stores the specified value at an certain offset
         *         from the current base pointer.
         *
         * @param  [i]   The offset from the current base pointer.
         * @param  [val] The value to be stored.
         *
         * @throws FrameOperationException if the position specified
         *         is out of the current <b>StackFrame</b> scope.
         */
        void set(int i, const OperandPtr &val);
};

#endif
