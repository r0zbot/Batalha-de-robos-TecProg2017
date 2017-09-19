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
        Stack(const int size);

        const int get_rsp() const;
        const int get_size() const;

        const T get_position(const int pos) const;
        const T top() const;

        void pop();
        void push(const T value);
        void set_position(const int pos, const T val);
        void set_rsp(const int val);
};
#include "stack.cpp"

#endif
