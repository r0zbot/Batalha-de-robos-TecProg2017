#ifndef VIRTUALMACHINE_FRAME_OPERATION_EXCEPTION_H_H
#define VIRTUALMACHINE_FRAME_OPERATION_EXCEPTION_H_H

#include <stdexcept>
#include <string>

using namespace std;

/**
 * @file  frame_operation_exception.h
 * @class FrameOperationException
 *
 * @brief The <b>FrameOperationException</b> represents errors
 *        that occurred in a {@link #StackFrame}.
 *
 * The <b>FrameOperationException</b> class is the general class
 * of exceptions produced by failed or interrupted process during
 * the execution of instructions inside of a {@link #StackFrame} scope.
 */
class FrameOperationException: public exception {

    private:
        /**
         * The detail message (which is saved for later retrieval
         * by the {@link #what()} method).
         */
        string msg;

    public:
        /**
         * @brief Constructs a <b>FrameOperationException</b> with the specified detail message.
         *
         * @param [msg]
         *        The detail message (which is saved for later retrieval
         *        by the {@link #what()} method).
         */
        explicit FrameOperationException(const string &msg);

        /**
         * @brief Returns a C-style character string describing the exception name
         *        and the general cause of the current error.
         *
         * @return The specified detail message passed to the exception.
         */
        const char* what() const throw() override;
};

#endif
