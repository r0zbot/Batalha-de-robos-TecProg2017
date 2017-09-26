#ifndef VIRTUALMACHINE_MACHINE_H
#define VIRTUALMACHINE_MACHINE_H

#include <map>
#include <stack>
#include <vector>

#include "instruction.h"
#include "frame.h"

using namespace std;

class Machine {

    private:
        int ip;

        Frame exec;

        stack<int> data;

        vector<int> memo;
        vector<Instruction> prog;

        typedef void (Machine::*Function)();
        map<Code, Function> functions;

        void map_functions();

    public:
        explicit Machine(const vector<Instruction> &prog);

        Code fetch_code() const;

        int  fetch_arg() const;

        void add();
        void allocate();
        void call();
        void divide();
        void duplicate();
        void equals();
        void execute();
        void free_memory();
        void greater();
        void greater_equal();
        void jump();
        void jump_if_false();
        void jump_if_true();
        void lower();
        void lower_equal();
        void multiply();
        void not_equal();
        void pop();
        void print();
        void push();
        void rce();
        void return_from_procedure();
        void recall();
        void store();
        void stl();
        void subtract();
};

#endif
