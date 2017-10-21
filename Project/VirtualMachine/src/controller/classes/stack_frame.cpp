#include <controller/classes/number.h>
#include <controller/classes/stack_frame.h>

#include <controller/exception/frame_operation_exception.h>

#include <util/log.h>

StackFrame::StackFrame(const unsigned long size): data(size) {
    this->ebp = 0;
    this->esp = 0;
}

int StackFrame::back() {
    if (this->ebp != this->esp) {
        Log::warn("Must free memory before return frame");
        this->esp = this->ebp;
    }
    this->ebp += this->data[this->esp - 1]->get_atr(0) - 2;
    return this->data[this->esp]->get_atr(0);
}

Operand* StackFrame::get(const int i) const {
    if (this->ebp + i <= this->esp - 2) {
        return this->data[this->ebp + i];
    }
    throw FrameOperationException("Index out of bounds RCE:" + to_string(i));
}

void StackFrame::alloc(const int n) {
    if (this->ebp + n + 2 <= this->data.size() - this->esp) {
        this->data[this->ebp + n + 1] = new Number(-n);
        this->esp = this->ebp + n + 2;
    }
    else {
        throw FrameOperationException("Trying to alloc more memory than possible");
    }
}

void StackFrame::free(const int n) {
    int keep = -(this->data[this->esp - 1]->get_atr(0) + n);
    if (keep == 0) {
        this->esp = this->ebp;
    }
    else if (keep > 0) {
        this->alloc(keep);
    }
    else {
        throw FrameOperationException("Trying to free memory out of scope FRE:" + to_string(n));
    }
}

void StackFrame::push(Operand *val) {
    if (this->esp <= this->data.size()) {
        this->data[this->esp] = val;
        this->ebp = this->esp;
    }
    else {
        throw FrameOperationException("Impossible to store more data in frame");
    }
}

void StackFrame::set(const int i, Operand *val) {
    if (this->ebp + i <= this->esp - 2) {
        this->data[this->ebp + i] = val;
    }
    else {
        throw FrameOperationException("Index out of bounds STL:" + to_string(i));
    }
}
