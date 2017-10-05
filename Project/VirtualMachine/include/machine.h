#ifndef VIRTUALMACHINE_MACHINE_H
#define VIRTUALMACHINE_MACHINE_H

#include <map>
#include <stack>
#include <vector>

#include "instruction.h"
#include "stack_frame.h"

using namespace std;

/**
 * The <b>Machine</b> class represents a "stack based machine" which is a computer that uses
 * a last-in, first-out (LIFO) stack to hold short-lived temporary values. Most of its instructions
 * assume that operands will be from the stack, and results placed in the stack.
 * <p>
 * For a typical instruction like <em>"Add"</em>, the <b>Machine</b> takes both operands from
 * the topmost (most recent) values of the stack. The <b>Machine</b> replaces those two values
 * by the sum, calculated by the computer when it performs the <em>"Add"</em> instruction.
 * The instruction's operands are <em>'popped'</em> off the stack, and its result(s) are then
 * <em>'pushed'</em> back onto the stack, ready for the next instruction. Most stack instructions have
 * only an <b>Code</b> commanding an operation, with no additional fields to identify a constant,
 * register or memory cell. The stack easily holds more than two inputs or more than one result,
 * so a more complex set of operations can be computed. Global variables or constant operands are
 * often pushed by separate immediate instructions. Memory is often accessed by separate Load (Recall)
 * or Store instructions containing a memory address or calculating the address from values in the stack.
 * <p>
 * <b>Executing arithmetic operands.</b> You can use the functions below to execute basic arithmetic
 * operations. (The methods below assume that the values to be used in the operations will be on the stack).
 * <p>
 * <ul>
 * <li> {@link #add}
 * <li> {@link #divide}
 * <li> {@link #multiply}
 * <li> {@link #subtract}
 * </ul>
 * <p>
 * <b>Executing logical comparisons.</b> You can check if one operand is greater than, less than,
 * equal to, or not equal to another operand in the stack by using the methods:
 * <ul>
 * <li> {@link #equals()}
 * <li> {@link #greater()}
 * <li> {@link #greater_equal()}
 * <li> {@link #lower()}
 * <li> {@link #lower_equal()}
 * <li> {@link #not_equal()}
 * </ul>
 * The methods above will use both of the topmost (most recent) values in the stack, and will
 * push back the result of their comparison.
 * <p>
 * <b>Storing and removing temporary values in the Machine stack.</b> You can use the
 * following methods to store or remove short-lived temporary values from the stack:
 * <ul>
 * <li> {@link #push}
 * <li> {@link #pop}
 * </ul>
 * <p>
 * <b>Jump instructions.</b> You can use the following methods to execute jump instructions:
 * <ul>
 * <li> {@link #jump()}
 * <li> {@link #jump_if_false()}
 * <li> {@link #jump_if_true()}
 * </ul>
 * The first method transfers control unconditionally to another instruction. The other two methods
 * are conditional jumps that use the topmost value of the stack to decide if the jump should be
 * executed or not.
 * <p>
 * <b>Executing subroutines.</b>You can start and stop subroutines by using the following methods:
 * <ul>
 * <li> {@link #call()}
 * <li> {@link #return_from_procedure()}
 * </ul>
 * The first method starts a subprocess specified in the instruction argument. The second method
 * stops the execution of the topmost subprogram in the <b>StackFrame</b> and return to the last
 * process activated before this one.
 * <p>
 * <b>Allocating and freeing memory in the StackFrame.</b> You can reserve/free space to use
 * local variables inside subprograms by using the following methods:
 * <ul>
 * <li> {@link #alloc()}
 * <li> {@link #free()}
 * </ul>
 * <p>
 * <b>Starting a Machine with a set of instructions.</b> As an example, you can start a program
 * by constructing a <b>Machine</b> object with a vector of <b>Instruction</b>. After the initialization
 * the {@link #execute()} method must be called to start the main program, just like below:
 * <pre>
 * vector<Instruction> prog = (...);
 * Machine m (prog);
 * m.execute();
 * </pre>
 * By doing this, the machine will execute the array of instructions until it reach an <b>END</b> code.
 */
class Machine {

    private:
        /**
         * Represents the Instruction Pointer (IP), commonly
         * called the Program Counter (PC), indicates where
         * the <b>Machine</b> is in its program sequence.
         */
        int ip;

        /**
         * Represents a call-return stack in memory to organize
         * and store short-lived local variables and return links
         * for all currently active procedures or functions.
         */
        StackFrame exec;

        /**
         * Represents the main stack during the program execution.
         * It's used to hold temporary values.
         */
        stack<int> data;

        /**
         * The memory vector is used to store and access global variables.
         * It's managed by the functions {@link #store()} and {@link #recall()}.
         */
        vector<int> memo;

        /**
         * Represents the program, a read-only set of instructions to be
         * executed during running time.
         */
        vector<Instruction> prog;

        /** Any function that belongs to this class will be of this type.*/
        typedef void (Machine::*Function)();

        /**
         * Stores functions pointers and its respective code.
         */
        map<Code, Function> functions;

        /**
         * Maps any function of this class that is directly related to an
         * instruction. It's a more elegant way to express a switch-case.
         */
        void map_functions();

    public:
        /**
         * Constructs a <b>Machine</b> with the specified set of instructions.
         *
         * @param [prog] A set of instructions representing a program.
         */
        explicit Machine(const vector<Instruction> &prog);

        /**
         * Pops both operands from the topmost (most recent) values of the stack,
         * then replaces those two values by their sum.
         */
        void add();

        /**
         * Allocates the amount of space specified by the argument of
         * the current instruction in the <b>StackFrame</b>.
         */
        void alloc();

        /**
         * Jumps to a subroutine specified by the argument of the
         * current instruction pointed by the Instruction Pointer.
         */
        void call();

        /**
         * Pops both operands from the topmost (most recent) values of the stack,
         * then replaces those two values by their quotient.
         */
        void divide();

        /**
         * Pushes a copy of the topmost (most recent) value of the stack.
         */
        void duplicate();

        /**
         * Pops both operands from the topmost (most recent) values of the stack,
         * then replaces those two values by the result of their equality comparison (n1 == n2).
         */
        void equals();

        /**
         * Start the execution of the main program specified during
         * the construction of the <b>Machine</b>.
         */
        void execute();

        /**
         * Frees the amount of space specified by the argument of
         * the current instruction in the <b>StackFrame</b>.
         */
        void free();

        /**
         * Return the code of the current instruction that is
         * being executed.
         *
         * @return The code of the current instruction.
         */
        Code fetch_code() const;

        /**
         * Return the argument of the current instruction that is
         * being executed.
         *
         * @return The argument of the current instruction.
         */
        int fetch_arg() const;

        /**
         * Pops both operands from the topmost (most recent) values of the stack,
         * then replaces those two values by the result of their "greater than"
         * comparison (n1 < n2).
         */
        void greater();

        /**
         * Pops both operands from the topmost (most recent) values of the stack,
         * then replaces those two values by the result of their "greater equal"
         * comparison (n1 <= n2).
         */
        void greater_equal();

        /**
         * Jumps to the instruction specified by the argument of the
         * current instruction pointed by the Instruction Pointer.
         */
        void jump();

        /**
         * Jumps to the instruction specified by the argument of the
         * current instruction pointed by the Instruction Pointer if
         * the topmost (most recent) value of the stack is false.
         */
        void jump_if_false();

        /**
         * Jumps to the instruction specified by the argument of the
         * current instruction pointed by the Instruction Pointer if
         * the topmost (most recent) value of the stack is true.
         */
        void jump_if_true();

        /**
         * Pops both operands from the topmost (most recent) values of the stack,
         * then replaces those two values by the result of their "lower than"
         * comparison (n1 > n2).
         */
        void lower();

        /**
         * Pops both operands from the topmost (most recent) values of the stack,
         * then replaces those two values by the result of their "lower equal"
         * comparison (n1 >= n2).
         */
        void lower_equal();

        /**
         * Pops both operands from the topmost (most recent) values of the stack,
         * then replaces those two values by their product.
         */
        void multiply();

        /**
         * Pops both operands from the topmost (most recent) values of the stack,
         * then replaces those two values by the result of their "not equal"
         * comparison (n1 != n2).
         */
        void not_equal();

        /**
         * Pops the topmost (most recent) value of the stack.
         */
        void pop();

        /**
         * Pops and prints the topmost (most recent) value of the stack.
         */
        void print();

        /**
         * Pushes the argument of the current instruction pointed by
         * the Instruction Pointer.
         */
        void push();

        /**
         * Pushes the element at the position indicate by the argument
         * of the current instruction pointed by the Instruction Pointer
         * at the <b>StackFrame</b>.
         */
        void rce();

        /**
         * Return to the last subroutine active.
         */
        void return_from_procedure();

        /**
         * Pushes the global variable at the position indicated by
         * the argument of the current instruction pointed by the
         * Instruction Pointer.
         */
        void recall();

        /**
         * Stores the topmost (most recent) value of the stack as
         * a global variable.
         */
        void store();

        /**
         * Stores the topmost (most recent) value of the stack as a local
         * variable in the current subroutine active.
         */
        void stl();

        /**
         * Pops both operands from the topmost (most recent) values of the stack,
         * then replaces those two values by their subtraction.
         */
        void subtract();
};

#endif
