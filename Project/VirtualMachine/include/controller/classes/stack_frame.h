#ifndef VIRTUALMACHINE_STACK_FRAME_H
#define VIRTUALMACHINE_STACK_FRAME_H

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
         * Represents the "Base Pointer" for the current function
         * so that all parameters and local variables would be at
         * a fixed offset from the base pointer.
         */
        int ebp;

        /**
         * Represents the "Top Pointer" and serves as an indirect memory
         * operand pointing to the top of the frame at any time.
         */
        int esp;

        /**
         * Stores all functions local variables that are being used in
         * subprogram calls and all the callers returning addresses.
         */
        vector<Operand*> data;

    public:
        /**
         * @brief Constructs a <b>StackFrame</b> with the specified size.
         *
         * @param [size] The <b>StackFrame</b> size.
         */
        explicit StackFrame(unsigned long size);

        /**
         * @brief  Allocates the specified amount of space
         *         from the current top pointer.
         *
         * @param  [n] The amount of space that must be allocated
         *             in the <b>StackFrame</b>.
         *
         * @throws FrameOperationException if impossible to allocate
         *         the specified amount of space.
         */
        void alloc(int n);

        /**
         * @brief  Returns the address from where the {@link #Machine}
         *         shall continue the program execution.
         *
         * @return The address from where the {@link #Machine}
         *         shall continue the program execution.
         */
        int back();

        /**
         * @brief  Frees the specified amount of space in the current frame scope.
         *
         * @param  [n] The amount of space that must be freed in
         *             the current <b>StackFrame</b> scope.
         *
         * @throws FrameOperationException if trying to free space
         *         out of the current <b>StackFrame</b> scope.
         */
        void free(int n);

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
        Operand* get(int i) const;

        /**
         * @brief  Stores the specified value at the top
         *         of the <b>StackFrame</b>.
         *
         * @param  [val] The value to be stored at the top
         *               of the <b>StackFrame</b>.
         *
         * @throws FrameOperationException if impossible to store
         *         more data in the <b>StackFrame</b>.
         */
        void push(Operand *val);

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
        void set(int i, Operand *val);
};

#endif
