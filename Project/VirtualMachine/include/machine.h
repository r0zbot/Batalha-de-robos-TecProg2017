#ifndef VIRTUALMACHINE_MACHINE_H
#define VIRTUALMACHINE_MACHINE_H

#include <map>
#include <stack>
#include <vector>

#include "instruction.h"

using namespace std;


class Machine {

    private:
        int ip;
        int rbp;
        
        vector<int> memo;

        stack<int> data;
        stack<int> exec;
        stack<int> rbpStack;

        Instruction *prog;

        typedef void (Machine::*Function)();
        map<Code, Function> functions;

        void map_functions();

    public:
        Machine(Instruction *prog);

        void add();
        void call();
        void divide();
        void duplicate();
        void equals();
        void execute();
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
        void rotate_carry_left();
        void store();
        void stl();
        void subtract();

        const int  fetch_arg() const;

        const Code fetch_code() const;
};


#endif