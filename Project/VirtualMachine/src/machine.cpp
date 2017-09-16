#include "../include/machine.h"

Machine::Machine(Instruction *prog) :
memo(100), data(512), exec(512), rbpStack(512)
{
    this->prog = prog;
    this->ip = 0;
    this->rbp = 0;
    this->map_functions();
}

void Machine::add() {
    int n1 = this->data.top();
    this->data.pop();
    int n2 = this->data.top();
    this->data.pop();
    this->data.push(n1 + n2);
}

void Machine::call() {
    this->exec.push(this->ip);
    this->rbpStack.push(this->rbp);
    this->jump();
}

void Machine::divide() {
    int den = this->data.top();
    this->data.pop();
    int num = this->data.top();
    this->data.pop();
    this->data.push(num / den);
}

void Machine::duplicate() {
    this->data.push(this->data.top());
}

void Machine::equals() {
    int n1 = this->data.top();
    this->data.pop();
    int n2 = this->data.top();
    this->data.pop();
    this->data.push(n1 == n2);
}

void Machine::execute() {
    bool run = true;
    while (run) {
        this->ip++;
        if (this->fetch_code() == Code::END) {
            run = false;
        }
        else {
            Function f = this->functions[this->fetch_code()];
            (this->*f)();
        }
    }
}

void Machine::greater() {
    int n1 = this->data.top();
    this->data.pop();
    int n2 = this->data.top();
    this->data.pop();
    this->data.push(n1 < n2);
}

void Machine::greater_equal() {
    int n1 = this->data.top();
    this->data.pop();
    int n2 = this->data.top();
    this->data.pop();
    this->data.push(n1 <= n2);
}

void Machine::jump() {
    this->ip = this->fetch_arg();
}

void Machine::jump_if_false() {
    if (!this->data.top()) {
        this->jump();
    }
    this->data.pop();
}

void Machine::jump_if_true() {
    if (this->data.top()) {
        this->jump();
    }
    this->data.pop();
}

void Machine::lower() {
    int n1 = this->data.top();
    this->data.pop();
    int n2 = this->data.top();
    this->data.pop();
    this->data.push(n1 > n2);
}

void Machine::lower_equal() {
    int n1 = this->data.top();
    this->data.pop();
    int n2 = this->data.top();
    this->data.pop();
    this->data.push(n1 >= n2);
}

void Machine::multiply() {
    int n1 = this->data.top();
    this->data.pop();
    int n2 = this->data.top();
    this->data.pop();
    this->data.push(n1 * n2);
}

void Machine::not_equal() {
    int n1 = this->data.top();
    this->data.pop();
    int n2 = this->data.top();
    this->data.pop();
    this->data.push(n1 != n2);
}

void Machine::pop() {
    this->data.pop();
}

void Machine::print() {
    printf("%d\n", this->data.top());
    this->data.pop();
}

void Machine::push() {
    this->data.push(this->fetch_arg());
}

void Machine::rce(){
    this->memo[this->rbp+this->fetch_arg()] = this->exec.top();
    this->exec.pop();
}

void Machine::return_from_procedure() {
    this->ip = this->exec.top();
    this->rbp = this->rbpStack.top();
    this->rbpStack.pop();
    this->exec.pop();
}

void Machine::rotate_carry_left() {
    this->data.push(this->memo[this->fetch_arg()]);
}

void Machine::store() {
    this->memo[this->fetch_arg()] = this->data.top();
    this->rbp++;
    this->data.pop();
}

void Machine::stl() {
    this->exec.push(this->data.top());
    this->data.pop();
}

void Machine::subtract() {
    int n1 = this->data.top();
    this->data.pop();
    int n2 = this->data.top();
    this->data.pop();
    this->data.push(n2 - n1);
}

const Code Machine::fetch_code() const {
    return this->prog[this->ip - 1].get_code();
}

const int Machine::fetch_arg() const {
    return this->prog[this->ip - 1].get_arg();
}

void Machine::map_functions() {
    this->functions[Code::ADD]  = &Machine::add;
    this->functions[Code::CALL] = &Machine::call;
    this->functions[Code::DIV]  = &Machine::divide;
    this->functions[Code::DUP]  = &Machine::duplicate;
    this->functions[Code::EQ]   = &Machine::equals;
    this->functions[Code::GT]   = &Machine::greater;
    this->functions[Code::GE]   = &Machine::greater_equal;
    this->functions[Code::JMP]  = &Machine::jump;
    this->functions[Code::JIF]  = &Machine::jump_if_false;
    this->functions[Code::JIT]  = &Machine::jump_if_true;
    this->functions[Code::LT]   = &Machine::lower;
    this->functions[Code::LE]   = &Machine::lower_equal;
    this->functions[Code::MUL]  = &Machine::multiply;
    this->functions[Code::NE]   = &Machine::not_equal;
    this->functions[Code::POP]  = &Machine::pop;
    this->functions[Code::PRN]  = &Machine::print;
    this->functions[Code::PUSH] = &Machine::push;
    this->functions[Code::RCE]  = &Machine::rce;
    this->functions[Code::RCL]  = &Machine::rotate_carry_left;
    this->functions[Code::RET]  = &Machine::return_from_procedure;
    this->functions[Code::STL]  = &Machine::stl;
    this->functions[Code::STO]  = &Machine::store;
    this->functions[Code::SUB]  = &Machine::subtract;
}
