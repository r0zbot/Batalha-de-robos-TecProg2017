#include "stack.h"


template <class T>
Stack<T>::Stack(const int size) {
    this->data = vector<T>(size);
    this->data[0] = 0;
    this->rsp = 0;
    this->size = size;
}

template <class T>
const T Stack<T>::get_position(const int pos) const {
    return this->data[pos];
}

template <class T>
const int Stack<T>::get_rsp() const {
    return this->rsp;
}

template <class T>
void Stack<T>::pop() {
    if (this->rsp > 0) {
        this->rsp--;
    }
    else {
        error("Stack is empty");
    }
}

template <class T>
void Stack<T>::push(const T value) {
    if (this->rsp < this->size) {
        this->data[this->rsp++] = value;
    }
    else {
        error("Stack is full");
    }
}

template <class T>
const T Stack<T>::top() const {
    if (this->rsp > 0) {
        return this->data[this->rsp - 1];
    }
    else {
        error("Stack is empty");
    }
}

template <class T>
const int Stack<T>::get_size() const {
    return this->size;
}

template <class T>
void Stack<T>::set_position(const int pos, const T val) {
    this->data[pos] = val;
}

template <class T>
void Stack<T>::set_rsp(const int val) {
    this->rsp = val;
}