#include <utility>

#include <controller/classes/machine.h>

#include <util/config.h>
#include <util/log.h>

Machine::Machine(Program &prog, Robot *parent)
    : exec(MACHINE_EXECUTION_STACK_SIZE), memo(MACHINE_MEMORY_SIZE), prog(prog) {
    this->ip = 0;
    this->map_functions();
    this->parent = parent;
}

Code Machine::fetch_code() const {
    return this->prog[this->ip - 1].get_code();
}

int Machine::fetch_arg() const {
    return this->prog[this->ip - 1].get_arg();
}

void Machine::add() {
    int n1 = this->data.top();
    this->data.pop();
    int n2 = this->data.top();
    this->data.pop();
    this->data.push(n1 + n2);
}

void Machine::alloc() {
    this->exec.alloc(this->fetch_arg());
}

void Machine::call() {
    this->exec.push(this->ip);
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
    int n = this->data.top();
    this->data.push(n);
}

void Machine::equals() {
    int n1 = this->data.top();
    this->data.pop();
    int n2 = this->data.top();
    this->data.pop();
    this->data.push(n1 == n2);
}

void Machine::execute() {
    while (run(1));
}

void Machine::free() {
    this->exec.free(this->fetch_arg());
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
    this->data.push(this->exec.get(this->fetch_arg()));
}

void Machine::return_from_procedure() {
    this->ip = this->exec.back();
}

void Machine::recall() {
    this->data.push(this->memo[this->fetch_arg()]);
}

bool Machine::run(int cycles) {
    for(int i=0; i<cycles; i++){
        this->ip++;
        if (this->fetch_code() == Code::END) {
            return false;
        }
        else {
            try {
                Function f = this->functions[this->fetch_code()];
                (this->*f)();
            }
            catch (const exception &e) {
                Log::error(e.what());
            }
        }
    }
    return true;
}

void Machine::store() {
    this->memo[this->fetch_arg()] = this->data.top();
    this->data.pop();
}

void Machine::stl() {
    this->exec.set(this->fetch_arg(), this->data.top());
    this->data.pop();
}

void Machine::subtract() {
    int n1 = this->data.top();
    this->data.pop();
    int n2 = this->data.top();
    this->data.pop();
    this->data.push(n2 - n1);
}

void Machine::map_functions() {
    this->functions.insert({Code::ADD,  &Machine::add});
    this->functions.insert({Code::ALC,  &Machine::alloc});
    this->functions.insert({Code::CALL, &Machine::call});
    this->functions.insert({Code::DIV,  &Machine::divide});
    this->functions.insert({Code::DUP,  &Machine::duplicate});
    this->functions.insert({Code::EQ,   &Machine::equals});
    this->functions.insert({Code::FRE,  &Machine::free});
    this->functions.insert({Code::GT,   &Machine::greater});
    this->functions.insert({Code::GE,   &Machine::greater_equal});
    this->functions.insert({Code::JMP,  &Machine::jump});
    this->functions.insert({Code::JIF,  &Machine::jump_if_false});
    this->functions.insert({Code::JIT,  &Machine::jump_if_true});
    this->functions.insert({Code::LT,   &Machine::lower});
    this->functions.insert({Code::LE,   &Machine::lower_equal});
    this->functions.insert({Code::MUL,  &Machine::multiply});
    this->functions.insert({Code::NE,   &Machine::not_equal});
    this->functions.insert({Code::POP,  &Machine::pop});
    this->functions.insert({Code::PRN,  &Machine::print});
    this->functions.insert({Code::PUSH, &Machine::push});
    this->functions.insert({Code::RCE,  &Machine::rce});
    this->functions.insert({Code::RCL,  &Machine::recall});
    this->functions.insert({Code::RET,  &Machine::return_from_procedure});
    this->functions.insert({Code::STL,  &Machine::stl});
    this->functions.insert({Code::STO,  &Machine::store});
    this->functions.insert({Code::SUB,  &Machine::subtract});
}
