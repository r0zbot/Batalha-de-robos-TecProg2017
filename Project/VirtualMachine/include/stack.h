#ifndef VIRTUALMACHINE_STACK_H
#define VIRTUALMACHINE_STACK_H


#include <string>

#include <vector>

#include "util.cpp"

using namespace std;


template <class T>
class Stack {

    private:
        int rsp;
        int size;

        vector<T> data;

    public:
        Stack(int size) {
            this->data = vector<T>(size);
            this->data[0] = 0;
            this->rsp = 0;
            this->size = size;
        }

        const T get_position(const int pos) const {
            return this->data[pos];
        }

        const int get_rsp() const {
            return this->rsp;
        }

        void pop() {
            if (this->rsp > 0) {
                this->rsp--;
            }
            else {
                error("Stack is empty");
            }
        }

        void push(const T value) {
            if (this->rsp < this->size) {
                this->data[this->rsp++] = value;
            }
            else {
                error("Stack is full");
            }
        }

        const T top() const {
            if (this->rsp > 0) {
                return this->data[this->rsp-1];
            }
            else {
                error("Stack is empty");
            }
        }

        const int get_size() const {
            return this->size;
        }

        void set_position(const int pos, const T val) {
            this->data[pos] = val;
        }

        void set_rsp(const int val) {
            this->rsp = val;
        }
};


#endif
