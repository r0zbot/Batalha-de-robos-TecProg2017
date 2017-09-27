#include <exception/frame_operation_exception.h>

#include "frame.h"
#include "log.h"

Frame::Frame(const int size): data(size) {
    this->ebp = 0;
    this->esp = 0;
}

int Frame::back() {
    if (this->ebp != this->esp) {
        Log::warn("Must free memory before return frame");
        this->esp = this->ebp;
    }
    this->ebp += this->data[this->esp - 1] - 2;
    return this->data[this->esp];
}

int Frame::get(const int i) const {
    if (this->ebp + i <= this->esp - 2) {
        return this->data[this->ebp + i];
    }
    throw FrameOperationException("Index out of bounds RCE:" + to_string(i));
}

void Frame::alloc(const int n) {
    if (this->ebp + n + 2 <= this->data.size() - this->esp) {
        this->data[this->ebp + n + 1] = -n;
        this->esp = this->ebp + n + 2;
    }
    else {
        throw FrameOperationException("Trying to alloc more memory than possible");
    }
}

void Frame::free(const int n) {
    int keep = -(this->data[this->esp - 1] + n);
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

void Frame::push(const int val) {
    if (this->esp <= this->data.size()) {
        this->data[this->esp] = val;
        this->ebp = this->esp;
    }
    else {
        throw FrameOperationException("Impossible to store more data in frame");
    }
}

void Frame::set(const int i, const int val) {
    if (this->ebp + i <= this->esp - 2) {
        this->data[this->ebp + i] = val;
    }
    else {
        throw FrameOperationException("Index out of bounds STL:" + to_string(i));
    }
}
