#include "memory.h"

Memory::Memory(const int size): data(size) {
    this->ebp = 0;
    this->esp = 0;
}

int Memory::back() {
    this->ebp += this->data[this->esp - 1] - 2;
    return this->data[this->esp];
}

int Memory::get(const int i) const {
    return this->data[this->ebp + i];
}

void Memory::alloc(const int n) {
    this->data[this->ebp + n + 1] = -n;
    this->esp = this->ebp + n + 2;
}

void Memory::free(const int n) {
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

void Memory::push(const int val) {
    this->data[this->esp] = val;
    this->ebp = this->esp;
}

void Memory::set(const int i, const int val) {
    this->data[this->ebp + i] = val;
}
