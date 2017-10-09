#include <utility>

#include <log.h>
#include <machine.h>
#include <config.h>

Machine::Machine(Program &prog) :
exec(MACHINE_EXECUTION_STACK_SIZE), memo(MACHINE_MEMORY_SIZE), prog(prog) {
    this->ip = 0;
    this->map_functions();
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
    this->functions.insert(make_pair(Code::ADD,  &Machine::add));
    this->functions.insert(make_pair(Code::ALC,  &Machine::alloc));
    this->functions.insert(make_pair(Code::CALL, &Machine::call));
    this->functions.insert(make_pair(Code::DIV,  &Machine::divide));
    this->functions.insert(make_pair(Code::DUP,  &Machine::duplicate));
    this->functions.insert(make_pair(Code::EQ,   &Machine::equals));
    this->functions.insert(make_pair(Code::FRE,  &Machine::free));
    this->functions.insert(make_pair(Code::GT,   &Machine::greater));
    this->functions.insert(make_pair(Code::GE,   &Machine::greater_equal));
    this->functions.insert(make_pair(Code::JMP,  &Machine::jump));
    this->functions.insert(make_pair(Code::JIF,  &Machine::jump_if_false));
    this->functions.insert(make_pair(Code::JIT,  &Machine::jump_if_true));
    this->functions.insert(make_pair(Code::LT,   &Machine::lower));
    this->functions.insert(make_pair(Code::LE,   &Machine::lower_equal));
    this->functions.insert(make_pair(Code::MUL,  &Machine::multiply));
    this->functions.insert(make_pair(Code::NE,   &Machine::not_equal));
    this->functions.insert(make_pair(Code::POP,  &Machine::pop));
    this->functions.insert(make_pair(Code::PRN,  &Machine::print));
    this->functions.insert(make_pair(Code::PUSH, &Machine::push));
    this->functions.insert(make_pair(Code::RCE,  &Machine::rce));
    this->functions.insert(make_pair(Code::RCL,  &Machine::recall));
    this->functions.insert(make_pair(Code::RET,  &Machine::return_from_procedure));
    this->functions.insert(make_pair(Code::STL,  &Machine::stl));
    this->functions.insert(make_pair(Code::STO,  &Machine::store));
    this->functions.insert(make_pair(Code::SUB,  &Machine::subtract));
}
