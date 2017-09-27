#ifndef VIRTUALMACHINE_FRAME_OPERATION_EXCEPTION_H_H
#define VIRTUALMACHINE_FRAME_OPERATION_EXCEPTION_H_H

#include <stdexcept>
#include <string>

using namespace std;

class FrameOperationException: public exception {

    private:
        string msg;

    public:
        explicit FrameOperationException(const string &msg);

        const char* what() const throw() override;
};

#endif
