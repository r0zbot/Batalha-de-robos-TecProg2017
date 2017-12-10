#include <iostream>

#include <concat.hpp>

#include <controller/classes/action.h>
#include <controller/classes/number.h>

#include <model/entity/machine.h>

#include <util/config.h>
#include <util/globals.h>
#include <util/log.h>

Machine::Machine(const Program &program, const Hex &pos, const string &image_path)
    : stop(false),
      ip(0),
      exec(MACHINE_EXECUTION_STACK_SIZE),
      memo(MACHINE_MEMORY_SIZE),
      program(program),
      EntityMove(pos,
                 image_path,
                 Config::machine_fuel,
                 Config::machine_inventory_size,
                 Config::machine_health,
                 Config::machine_melee_attack,
                 Config::machine_short_attack,
                 Config::machine_long_attack) {
    this->map_functions();
}

OperandPtr Machine::fetch_arg() const {
    return this->program[this->ip - 1].get_arg();
}

Code Machine::fetch_code() const {
    return this->program[this->ip - 1].get_code();
}

OperandPtr Machine::top() const {
    return this->data.top();
}

void Machine::add() {
    auto n1 = dynamic_pointer_cast<Number>(this->data.top());
    this->data.pop();
    auto n2 = dynamic_pointer_cast<Number>(this->data.top());
    this->data.pop();
    if (n1 && n2) {
        this->data.push(make_shared<Number>(n1->get_value() + n2->get_value()));
    }
    else {
        this->print("<ERROR> Operands in Code::ADD are not Numbers");
        this->stop = true;
    }
}

void Machine::alloc() {
    auto n = dynamic_pointer_cast<Number>(this->fetch_arg());
    if (n) {
        this->exec.alloc(n->get_value());
    }
    else {
        this->print("<ERROR> Operand in Code::ALC is not Number");
        this->stop = true;
    }
}

void Machine::atr() {
    auto aux = &this->data.top();
    this->data.pop();
    auto arg = dynamic_pointer_cast<Number>(this->fetch_arg());
    if (arg) {
        this->data.push(make_shared<Number>(aux->get()->get_atr(arg->get_value())));
    }
    else {
        this->print("<ERROR> Operand in Code::ATR is not Number");
        this->stop = true;
    }
}

void Machine::attack_melee() {
    this->data.push(make_shared<Number>(arena.request_attack_melee(*this, this->pos.neighbor((Direction) this->fetch_arg()->get_atr(1)))));
}

void Machine::attack_short() {
    this->data.push(make_shared<Number>(arena.request_attack_short(*this, this->pos.neighbor((Direction) this->fetch_arg()->get_atr(1)))));
}

void Machine::attack_long() {
    this->data.push(make_shared<Number>(arena.request_attack_long(*this, this->pos.neighbor((Direction) this->fetch_arg()->get_atr(1)))));
}

void Machine::call() {
    this->exec.push(make_shared<Number>(this->ip));
    this->jump();
}

void Machine::collect_crystal() {
    this->data.push(make_shared<Number>(arena.request_collect(*this, this->pos.neighbor((Direction) this->fetch_arg()->get_atr(1)))));
}

void Machine::divide() {
    auto n1 = dynamic_pointer_cast<Number>(this->data.top());
    this->data.pop();
    auto n2 = dynamic_pointer_cast<Number>(this->data.top());
    this->data.pop();
    if (n1 && n2) {
        this->data.push(make_shared<Number>(n2->get_value() / n1->get_value()));
    }
    else {
        this->print("<ERROR> Operands in Code::DIV are not Numbers");
        this->stop = true;
    }
}

void Machine::drop_crystal() {
    this->data.push(make_shared<Number>(arena.request_drop(*this, this->pos.neighbor((Direction) this->fetch_arg()->get_atr(1)))));
}

void Machine::duplicate() {
    auto top = &this->data.top();
    this->data.push(*top);
}

void Machine::equals() {
    auto n1 = dynamic_pointer_cast<Number>(this->data.top());
    this->data.pop();
    auto n2 = dynamic_pointer_cast<Number>(this->data.top());
    this->data.pop();
    if (n1 && n2) {
        this->data.push(make_shared<Number>(n1->get_value() == n2->get_value()));
    }
    else {
        this->print("<ERROR> Operands in Code::EQ are not Numbers");
        this->stop = true;
    }
}

void Machine::execute() {
    while (!this->stop) {
        this->update();
    }
}

void Machine::free() {
    auto n = dynamic_pointer_cast<Number>(this->fetch_arg());
    if (n) {
        this->exec.free(n->get_value());
    }
    else {
        this->print("<ERROR> Operand in Code::FRE is not Number");
        this->stop = true;
    }
}

void Machine::greater() {
    auto n1 = dynamic_pointer_cast<Number>(this->data.top());
    this->data.pop();
    auto n2 = dynamic_pointer_cast<Number>(this->data.top());
    this->data.pop();
    if (n1 && n2) {
        this->data.push(make_shared<Number>(n1->get_value() < n2->get_value()));
    }
    else {
        this->print("<ERROR> Operands in Code::GT are not Numbers");
        this->stop = true;
    }
}

void Machine::greater_equal() {
    auto n1 = dynamic_pointer_cast<Number>(this->data.top());
    this->data.pop();
    auto n2 = dynamic_pointer_cast<Number>(this->data.top());
    this->data.pop();
    if (n1 && n2) {
        this->data.push(make_shared<Number>(n1->get_value() <= n2->get_value()));
    }
    else {
        this->print("<ERROR> Operands in Code::GE are not Numbers");
        this->stop = true;
    }
}

void Machine::jump() {
    auto n = dynamic_pointer_cast<Number>(this->fetch_arg());
    if (n) {
        this->ip = n->get_value();
    }
    else {
        this->print("<ERROR> Operand in Code::JMP is not Number");
        this->stop = true;
    }
}

void Machine::jump_if_false() {
    auto n = dynamic_pointer_cast<Number>(this->data.top());
    if (n && !n->get_value()) {
        this->jump();
        this->data.pop();
    }
}

void Machine::jump_if_true() {
    auto n = dynamic_pointer_cast<Number>(this->data.top());
    if (n && n->get_value()) {
        this->jump();
        this->data.pop();
    }
}

void Machine::lower() {
    auto n1 = dynamic_pointer_cast<Number>(this->data.top());
    this->data.pop();
    auto n2 = dynamic_pointer_cast<Number>(this->data.top());
    this->data.pop();
    if (n1 && n2) {
        this->data.push(make_shared<Number>(n1->get_value() > n2->get_value()));
    }
    else {
        this->print("<ERROR> Operands in Code::LT are not Numbers");
        this->stop = true;
    }
}

void Machine::lower_equal() {
    auto n1 = dynamic_pointer_cast<Number>(this->data.top());
    this->data.pop();
    auto n2 = dynamic_pointer_cast<Number>(this->data.top());
    this->data.pop();
    if (n1 && n2) {
        this->data.push(make_shared<Number>(n1->get_value() >= n2->get_value()));
    }
    else {
        this->print("<ERROR> Operands in Code::LT are not Numbers");
        this->stop = true;
    }
}

void Machine::move() {
    this->data.push(make_shared<Number>(arena.request_movement(*this, this->pos.neighbor((Direction) this->fetch_arg()->get_atr(1)))));
}

void Machine::multiply() {
    auto n1 = dynamic_pointer_cast<Number>(this->data.top());
    this->data.pop();
    auto n2 = dynamic_pointer_cast<Number>(this->data.top());
    this->data.pop();
    if (n1 && n2) {
        this->data.push(make_shared<Number>(n1->get_value() * n2->get_value()));
    }
    else {
        this->print("<ERROR> Operands in Code::MUL are not Numbers");
        this->stop = true;
    }
}

void Machine::no_operation(){}

void Machine::not_equal() {
    auto n1 = dynamic_pointer_cast<Number>(this->data.top());
    this->data.pop();
    auto n2 = dynamic_pointer_cast<Number>(this->data.top());
    this->data.pop();
    if (n1 && n2) {
        this->data.push(make_shared<Number>(n1->get_value() != n2->get_value()));
    }
    else {
        this->print("<ERROR> Operands in Code::NE are not Numbers");
        this->stop = true;
    }
}

void Machine::pop() {
    this->data.pop();
}

void Machine::print() {
    arena.print(*this->data.top(), *this);
    this->data.pop();
}

void Machine::print(const string &s) {
    arena.print(s, *this);
}

void Machine::push() {
    this->data.push(this->fetch_arg());
}

void Machine::rce() {
    auto n = dynamic_pointer_cast<Number>(this->fetch_arg());
    if (n) {
        this->data.push(this->exec.get(n->get_value()));
    }
    else {
        this->print("<ERROR> Operand in Code::RCE is not Number");
        this->stop = true;
    }
}

void Machine::recall() {
    auto n = dynamic_pointer_cast<Number>(this->fetch_arg());
    if (n) {
        this->data.push(this->memo[n->get_value()]);
    }
    else {
        this->print("<ERROR> Operand in Code::RCL is not Number");
        this->stop = true;
    }
}

void Machine::reset() {
    this->stop = false;
    this->ip = 0;
    this->exec.reset();
    this->memo.clear();

    while (!this->data.empty()) {
        this->data.pop();
    }
}

void Machine::return_from_procedure() {
    this->ip = this->exec.back();
}

void Machine::see() {
    auto d = (Direction) this->fetch_arg()->get_atr(1);
    auto cell = make_shared<Hex>(* new Hex(arena.get_cell(this->pos.neighbor(d))));
    this->data.push(cell);
}

void Machine::set_program(const Program &program) {
    this->program = program;
    this->reset();
}

void Machine::store() {
    auto n = dynamic_pointer_cast<Number>(this->fetch_arg());
    if (n) {
        this->memo[n->get_value()] = this->data.top();
        this->data.pop();
    }
}

void Machine::stl() {
    this->exec.set(this->fetch_arg()->get_atr(0), this->data.top());
    this->data.pop();
}

void Machine::subtract() {
    auto n1 = dynamic_pointer_cast<Number>(this->data.top());
    this->data.pop();
    auto n2 = dynamic_pointer_cast<Number>(this->data.top());
    this->data.pop();
    if (n1 && n2) {
        this->data.push(make_shared<Number>(n2->get_value() - n1->get_value()));
    }
    else {
        this->print("<ERROR> Operands in Code::SUB are not Numbers");
        this->stop = true;
    }
}

void Machine::system() {
    if (this->systemFunctions.count((SystemCode) this->fetch_arg()->get_atr(0)) != 1) {
        this->print(concat(this->fetch_arg()->get_atr(0), " is not a valid system instruction."));
        return;
    }
    Function f = this->systemFunctions[(SystemCode) this->fetch_arg()->get_atr(0)];
    (this->*f)();
}

void Machine::update() {
    if (this->stop || this->hp <= 0) {
        return;
    }
    for (int i = 0; i < Config::machine_instructions_cycle; i++) {
        ++this->ip;
        if (this->fetch_code() == Code::END) {
            this->stop = true;
            return;
        }
        else if (!this->use_fuel(Config::machine_inst_fuel_usage)) {
            arena.print("Not enough fuel to process!", *this);
            this->stop = true;
            return;
        }
        else if(this->hp <= 0){
            arena.print("Im dead!", *this);
            this->stop = true;
            return;
        }
        try {
            if (this->fetch_code() == Code::SYS) {
                this->system();
                break;
            }
            else {
                Function f = this->functions[this->fetch_code()];
                (this->*f)();
            }
        }
        catch (const exception &e) {
            Log::error(e.what());
        }
    }
}


void Machine::map_functions() {
    this->functions.insert({Code::ADD,  &Machine::add});
    this->functions.insert({Code::ALC,  &Machine::alloc});
    this->functions.insert({Code::ATR,  &Machine::atr});
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
    this->functions.insert({Code::NOP,  &Machine::no_operation});
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

    this->systemFunctions.insert({SystemCode::ATKMELEE, &Machine::attack_melee});
    this->systemFunctions.insert({SystemCode::ATKSHORT, &Machine::attack_short});
    this->systemFunctions.insert({SystemCode::ATKLONG,  &Machine::attack_long});
    this->systemFunctions.insert({SystemCode::COLLECT,  &Machine::collect_crystal});
    this->systemFunctions.insert({SystemCode::DROP,     &Machine::drop_crystal});
    this->systemFunctions.insert({SystemCode::MOVE,     &Machine::move});
    this->systemFunctions.insert({SystemCode::SEE,      &Machine::see});
}
