#include <controller/exception/frame_operation_exception.h>

FrameOperationException::FrameOperationException(const string &msg): msg(msg) {}

const char* FrameOperationException::what() const throw() {
    return ("FrameOperationException: " + this->msg).c_str();
}
