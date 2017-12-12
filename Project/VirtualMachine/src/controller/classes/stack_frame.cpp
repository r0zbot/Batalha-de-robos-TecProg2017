#include <controller/classes/stack_frame.h>

#include <controller/exception/frame_operation_exception.h>

StackFrame::StackFrame(const unsigned long size)
        : entry(0),
          data(size) {}

int StackFrame::back() {
    this->entry -= this->entries.top();
    this->entries.pop();

    const int ip = this->history.top();
    this->history.pop();

    return ip;
}

OperandPtr StackFrame::get(const int i) const {
    if (this->entry + i <= this->data.size()) {
        return this->data[this->entry + i];
    }
    throw FrameOperationException("Index out of bounds:" + to_string(this->entry + i));
}

void StackFrame::offset(int n) {
    if (this->entry + n < this->data.size()) {
        this->entries.push(n);
        this->entry += n;
    }
    else {
        throw FrameOperationException("Trying to use more memory than possible");
    }
}

void StackFrame::push(const int address) {
    this->history.push(address);
}

void StackFrame::reset() {
    this->data    = vector<OperandPtr>(this->data.size());
    this->entries = stack<int>();
    this->entry   = 0;
    this->history = stack<int>();
}

void StackFrame::set(const int i, const OperandPtr &val) {
    if (this->entry + i <= this->data.size()) {
        this->data[this->entry + i] = val;
    }
    else {
        throw FrameOperationException("Index out of bounds:" + to_string(this->entry + i));
    }
}
