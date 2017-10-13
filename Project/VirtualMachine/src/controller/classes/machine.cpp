#include <utility>

#include <controller/classes/machine.h>

#include <util/config.h>
#include <util/log.h>

#include <model/entity/robot.h>
#include <util/globals.h>
#include <concat.hpp>

Machine::Machine(Program &prog)
    : exec(MACHINE_EXECUTION_STACK_SIZE), memo(MACHINE_MEMORY_SIZE), prog(prog) {
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

void Machine::attack_melee() {
    arena.request_attack_melee(*this->parent, (Direction) this->data.top());
    this->data.pop();
}

void Machine::attack_short() {
    arena.request_attack_short(*this->parent, (Direction) this->data.top());
    this->data.pop();
}

void Machine::attack_long() {
    arena.request_attack_long(*this->parent, (Direction) this->data.top());
    this->data.pop();
}

void Machine::call() {
    this->exec.push(this->ip);
    this->jump();
}

void Machine::collect_crystal() {
    arena.request_collect(*this->parent, (Direction) this->data.top());
    this->data.pop();
}

void Machine::divide() {
    int den = this->data.top();
    this->data.pop();
    int num = this->data.top();
    this->data.pop();
    this->data.push(num / den);
}

void Machine::drop_crystal() {
    arena.request_drop(*this->parent, (Direction) this->data.top());
    this->data.pop();
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

void Machine::move() {
    arena.request_movement(*this->parent, (Direction) this->data.top());
    this->data.pop();
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
    arena.print(this->data.top(), *this->parent);
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
    if(this->endReached){
        return false;
    }
    for(int i=0; i<cycles; i++){
        this->ip++;
        if (this->fetch_code() == Code::END) {
            this->endReached = true;
            return false;
        }
        else {
            try {
                if(!this->parent->use_fuel(FUEL_PER_INSTRUCTION)){
                    arena.print("Not enough fuel!", *this->parent);
                    return false;
                }
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

void Machine::set_parent(Robot *robot) {
    this->parent = robot;
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

void Machine::system() {
    if(this->systemFunctions.count((SystemCode) this->fetch_arg()) != 1) {
        Log::warn(concat(this->fetch_arg(), " is not a valid system instruction."));
        return;
    }
    Function f = this->systemFunctions[(SystemCode) this->fetch_arg()];
    (this->*f)();
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
    this->functions.insert({Code::SYS,  &Machine::system});

    this->systemFunctions.insert({SystemCode::ATKMELEE,  &Machine::attack_melee});
    this->systemFunctions.insert({SystemCode::ATKSHORT,  &Machine::attack_short});
    this->systemFunctions.insert({SystemCode::ATKLONG,  &Machine::attack_long});
    this->systemFunctions.insert({SystemCode::COLLECT, &Machine::collect_crystal});
    this->systemFunctions.insert({SystemCode::DROP,  &Machine::drop_crystal});
    this->systemFunctions.insert({SystemCode::MOVE,  &Machine::move});
}
