#include "../include/machine.h"
#include "../include/util.h"


Machine::Machine(Instruction *prog) :
memo(100), data(512), exec(512), rbpStack(512) {
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

void Machine::allocate() {
    int size = this->fetch_arg();
    if (this->rbp + size < this->exec.getSize()){
        this->rbp += size;
    }
    else{
        error("Memoria insuficiente na pilha de execucao");
    }
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

void Machine::free_memory() {
    this->rbp = this->rbpStack.top();
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

void Machine::rce() {
    int pos = this->rbpStack.top() + this->fetch_arg();
    if (pos < this->rbp) {
        this->data.push(this->exec.getPosition(pos));
    }
    else {
        error("Tentativa de acesso fora da zona alocada!");
    }
}

void Machine::return_from_procedure() {
    this->ip = this->exec.top();
    this->free_memory();
    this->rbpStack.pop();
    this->exec.pop();
}

void Machine::recall() {
    this->data.push(this->memo[this->fetch_arg()]);
}

void Machine::store() {
    this->memo[this->fetch_arg()] = this->data.top();
    this->data.pop();
}

void Machine::stl() {
    int pos = this->rbpStack.top() + this->fetch_arg();
    if (pos < this->rbp) {
        this->exec.setPosition(pos, this->data.top());
        this->data.pop();
    }
    else {
        error("Fora da memória local alocada");
    }
}

void Machine::subtract() {
    int n1 = this->data.top();
    this->data.pop();
    int n2 = this->data.top();
    this->data.pop();
    this->data.push(n2 - n1);
}

const int Machine::fetch_arg() const {
    return this->prog[this->ip - 1].get_arg();
}

const Code Machine::fetch_code() const {
    return this->prog[this->ip - 1].get_code();
}

void Machine::map_functions() {
    this->functions[Code::ADD]  = &Machine::add;
    this->functions[Code::ALC]  = &Machine::allocate;
    this->functions[Code::CALL] = &Machine::call;
    this->functions[Code::DIV]  = &Machine::divide;
    this->functions[Code::DUP]  = &Machine::duplicate;
    this->functions[Code::EQ]   = &Machine::equals;
    this->functions[Code::FRE]  = &Machine::free_memory;
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
    this->functions[Code::RCL]  = &Machine::recall;
    this->functions[Code::RET]  = &Machine::return_from_procedure;
    this->functions[Code::STL]  = &Machine::stl;
    this->functions[Code::STO]  = &Machine::store;
    this->functions[Code::SUB]  = &Machine::subtract;
}
