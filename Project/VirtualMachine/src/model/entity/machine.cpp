#include <controller/classes/action.h>
#include <controller/classes/number.h>

#include <model/entity/machine.h>

#include <util/config.h>
#include <util/globals.h>
#include <util/log.h>

Machine::Machine(Program &prog, const Hex &pos)
    : stop(false),
      ip(0),
      exec(MACHINE_EXECUTION_STACK_SIZE),
      memo(MACHINE_MEMORY_SIZE),
      prog(prog),
      EntityMove(pos) {
    this->map_functions();
}

Code Machine::fetch_code() const {
    return this->prog[this->ip - 1].get_code();
}

Operand* Machine::fetch_arg() const {
    return &this->prog[this->ip - 1].get_arg();
}

Operand* Machine::top() const {
    return this->data.top();
}

void Machine::add() {
    auto n1 = dynamic_cast<Number*>(this->data.top());
    this->data.pop();
    auto n2 = dynamic_cast<Number*>(this->data.top());
    this->data.pop();
    if (n1 && n2) {
        this->data.push(new Number(n1->get_atr(0) + n2->get_atr(0)));
    }
    else {
        Log::error("Operands in Code::ADD are not Numbers");
    }
}

void Machine::alloc() {
    auto n = dynamic_cast<Number*>(this->fetch_arg());
    if (n) {
        this->exec.alloc(n->get_atr(0));
    }
    else {
        Log::error("Operand in Code::ALC is not Number");
    }
}

void Machine::atr() {
    auto aux = this->data.top();
    this->data.pop();
    auto arg = dynamic_cast<Number*>(this->fetch_arg());
    if (arg) {
        this->data.push(new Number(aux->get_atr(arg->get_atr(0))));
    }
    else {
        Log::error("Operand in Code::ATR is not Number");
    }
}

void Machine::attack_melee() {
    arena.request_attack_melee(
            *this,
            this->pos.neighbor((Direction) this->fetch_arg()->get_atr(1)));
}

void Machine::attack_short() {
    arena.request_attack_short(
            *this,
            this->pos.neighbor((Direction) this->fetch_arg()->get_atr(1)));
}

void Machine::attack_long() {
    arena.request_attack_long(
            *this,
            this->pos.neighbor((Direction) this->fetch_arg()->get_atr(1)));
}

void Machine::call() {
    this->exec.push(new Number(this->ip));
    this->jump();
}

void Machine::collect_crystal() {
    arena.request_collect(
            *this,
            this->pos.neighbor((Direction) this->fetch_arg()->get_atr(1)));
}

void Machine::divide() {
    auto n1 = dynamic_cast<Number*>(this->data.top());
    this->data.pop();
    auto n2 = dynamic_cast<Number*>(this->data.top());
    this->data.pop();
    if (n1 && n2) {
        this->data.push(new Number(n2->get_atr(0) / n1->get_atr(0)));
    }
    else {
        Log::error("Operands in Code::DIV are not Numbers");
    }
}

void Machine::drop_crystal() {
    arena.request_drop(
            *this,
            this->pos.neighbor((Direction) this->fetch_arg()->get_atr(1)));
}

void Machine::duplicate() {
    auto n = dynamic_cast<Number*>(this->data.top());
    this->data.push(new Number(n->get_atr(0)));
}

void Machine::equals() {
    auto n1 = dynamic_cast<Number*>(this->data.top());
    this->data.pop();
    auto n2 = dynamic_cast<Number*>(this->data.top());
    this->data.pop();
    if (n1 && n2) {
        this->data.push(new Number(n1->get_atr(0) == n2->get_atr(0)));
    }
    else {
        Log::error("Operands in Code::EQ are not Numbers");
    }
}

void Machine::execute() {
    while (!this->stop) {
        this->update(1);
    }
}

void Machine::free() {
    auto n = dynamic_cast<Number*>(this->fetch_arg());
    if (n) {
        this->exec.free(n->get_atr(0));
    }
    else {
        Log::error("Operand in Code::FRE is not Number");
    }
}

void Machine::greater() {
    auto n1 = dynamic_cast<Number*>(this->data.top());
    this->data.pop();
    auto n2 = dynamic_cast<Number*>(this->data.top());
    this->data.pop();
    if (n1 && n2) {
        this->data.push(new Number(n1->get_atr(0) < n2->get_atr(0)));
    }
    else {
        Log::error("Operands in Code::GT are not Numbers");
    }
}

void Machine::greater_equal() {
    auto n1 = dynamic_cast<Number*>(this->data.top());
    this->data.pop();
    auto n2 = dynamic_cast<Number*>(this->data.top());
    this->data.pop();
    if (n1 && n2) {
        this->data.push(new Number(n1->get_atr(0) <= n2->get_atr(0)));
    }
    else {
        Log::error("Operands in Code::GE are not Numbers");
    }
}

void Machine::jump() {
    auto n = dynamic_cast<Number*>(this->fetch_arg());
    if (n) {
        this->ip = n->get_atr(0);
    }
    else {
        Log::error("Operand in Code::JMP is not Number");
    }
}

void Machine::jump_if_false() {
    auto n = dynamic_cast<Number*>(this->data.top());
    if (n && !n->get_atr(0)) {
        this->jump();
        this->data.pop();
    }
}

void Machine::jump_if_true() {
    auto n = dynamic_cast<Number*>(this->data.top());
    if (n && n->get_atr(0)) {
        this->jump();
        this->data.pop();
    }
}

void Machine::lower() {
    auto n1 = dynamic_cast<Number*>(this->data.top());
    this->data.pop();
    auto n2 = dynamic_cast<Number*>(this->data.top());
    this->data.pop();
    if (n1 && n2) {
        this->data.push(new Number(n1->get_atr(0) > n2->get_atr(0)));
    }
    else {
        Log::error("Operands in Code::LT are not Numbers");
    }
}

void Machine::lower_equal() {
    auto n1 = dynamic_cast<Number*>(this->data.top());
    this->data.pop();
    auto n2 = dynamic_cast<Number*>(this->data.top());
    this->data.pop();
    if (n1 && n2) {
        this->data.push(new Number(n1->get_atr(0) >= n2->get_atr(0)));
    }
    else {
        Log::error("Operands in Code::LT are not Numbers");
    }
}

void Machine::move() {
    arena.request_movement(
            *this,
            this->pos.neighbor((Direction) this->fetch_arg()->get_atr(1)));
}

void Machine::multiply() {
    auto n1 = dynamic_cast<Number*>(this->data.top());
    this->data.pop();
    auto n2 = dynamic_cast<Number*>(this->data.top());
    this->data.pop();
    if (n1 && n2) {
        this->data.push(new Number(n1->get_atr(0) * n2->get_atr(0)));
    }
    else {
        Log::error("Operands in Code::MUL are not Numbers");
    }
}

void Machine::not_equal() {
    auto n1 = dynamic_cast<Number*>(this->data.top());
    this->data.pop();
    auto n2 = dynamic_cast<Number*>(this->data.top());
    this->data.pop();
    if (n1 && n2) {
        this->data.push(new Number(n1->get_atr(0) != n2->get_atr(0)));
    }
    else {
        Log::error("Operands in Code::NE are not Numbers");
    }
}

void Machine::pop() {
    this->data.pop();
}

void Machine::print() {
    int n = this->data.top()->get_atr(0);
    printf("%d\n", n);
    this->data.pop();
}

void Machine::push() {
    this->data.push(this->fetch_arg());
}

void Machine::rce() {
    auto n = dynamic_cast<Number*>(this->fetch_arg());
    if (n) {
        this->data.push(this->exec.get(n->get_atr(0)));
    }
    else {
        Log::error("Operand in Code::RCE is not Number");
    }
}

void Machine::return_from_procedure() {
    this->ip = this->exec.back();
}

void Machine::recall() {
    auto n = dynamic_cast<Number*>(this->fetch_arg());
    if (n) {
        this->data.push(this->memo[n->get_atr(0)]);
    }
    else {
        Log::error("Operand in Code::RCL is not Number");
    }
}

void Machine::see() {
    auto d = (Direction) dynamic_cast<Action*>(this->fetch_arg())->get_atr(1);
    this->data.push(&arena.get_cell(this->pos.neighbor(d)));
}

void Machine::store() {
    auto n = dynamic_cast<Number*>(this->fetch_arg());
    if (n) {
        this->memo[n->get_atr(0)] = this->data.top();
        this->data.pop();
    }
}

void Machine::stl() {
    auto aux = this->data.top();
    this->exec.set(this->fetch_arg()->get_atr(0), aux);
    this->data.pop();
}

void Machine::subtract() {
    auto n1 = dynamic_cast<Number*>(this->data.top());
    this->data.pop();
    auto n2 = dynamic_cast<Number*>(this->data.top());
    this->data.pop();
    if (n1 && n2) {
        this->data.push(new Number(n2->get_atr(0) - n1->get_atr(0)));
    }
    else {
        Log::error("Operands in Code::SUB are not Numbers");
    }
}

void Machine::system() {
    if (this->systemFunctions.count((SystemCode) this->fetch_arg()->get_atr(0)) != 1) {
        Log::warn(to_string(this->fetch_arg()->get_atr(0)) + " is not a valid system instruction.");
        return;
    }
    Function f = this->systemFunctions[(SystemCode) this->fetch_arg()->get_atr(0)];
    (this->*f)();
}

void Machine::update(int cycles) {
    if (this->stop || this->hp <= 0) {
        return;
    }
    for (int i = 0; i < cycles; i++) {
        ++this->ip;
        if (this->fetch_code() == Code::END) {
            this->stop = true;
            return;
        }
        else if (!this->use_fuel(FUEL_PER_INSTRUCTION)) {
            arena.print("Not enough fuel!", *this);
            this->stop = true;
            return;
        }
        try {
            if (this->fetch_code() == Code::SYS) {
                this->system();
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
    this->systemFunctions.insert({SystemCode::SEE,  &Machine::see});
}
