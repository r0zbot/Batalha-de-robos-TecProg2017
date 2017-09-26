#include "frame.h"

Frame::Frame(const int size): data(size) {
    this->ebp = 0;
    this->esp = 0;
}

int Frame::back() {
    this->ebp += this->data[this->esp - 1] - 2;
    return this->data[this->esp];
}

int Frame::get(const int i) const {
    return this->data[this->ebp + i];
}

void Frame::alloc(const int n) {
    this->data[this->ebp + n + 1] = -n;
    this->esp = this->ebp + n + 2;
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
        // ERROR
    }
}

void Frame::push(const int val) {
    this->data[this->esp] = val;
    this->ebp = this->esp;
}

void Frame::set(const int i, const int val) {
    this->data[this->ebp + i] = val;
}
