#ifndef VIRTUALMACHINE_MACHINE_H
#define VIRTUALMACHINE_MACHINE_H

#include <map>
#include <stack>

#include <controller/classes/stack_frame.h>
#include <controller/classes/syscall.h>

#include <model/interface/entity_move.h>

#define MACHINE_EXECUTION_STACK_SIZE 6000  ///< The execution stack size in a {@link #Machine}.
#define MACHINE_MEMORY_SIZE          2000  ///< The memory size in a {@link #Machine}.

using namespace std;

/**
 * @file  machine.h
 * @class Machine
 *
 * @brief This class is the core of the Virtual Machine and will
 *        execute a set of instructions as a main program.
 *
 * The <b>Machine</b> class represents a "stack based machine"
 * which is a computer that uses a last-in, first-out (LIFO)
 * stack to hold short-lived temporary values. Most of its
 * instructions assume that operands will be from the stack,
 * and results placed in the stack.
 * <p>
 * For a typical instruction like <em>"Add"</em>, the <b>Machine</b>
 * takes both operands from the topmost (most recent) values of the
 * stack. The <b>Machine</b> replaces those two values by the sum,
 * calculated by the computer when it performs the <em>"Add"</em>
 * instruction. The instruction's operands are <em>'popped'</em> off
 * the stack, and its result(s) are then <em>'pushed'</em> back onto
 * the stack, ready for the next instruction. Most stack instructions
 * have only an {@link #Code} commanding an operation, with no additional
 * fields to identify a constant, register or memory cell. The stack easily
 * holds more than two inputs or more than one result, so a more complex set
 * of operations can be computed. Global variables or constant operands are
 * often pushed by separate immediate instructions. Memory is often accessed
 * by separate Load (Recall) or Store instructions containing a memory address
 * or calculating the address from values in the stack.
 * <p>
 * <b>Executing arithmetic operands.</b> You can use the functions below to
 * execute basic arithmetic operations. (The methods below assume that the
 * values to be used in the operations will be on the stack).
 * <p>
 * <ul>
 *   <li> {@link #add}      </li>
 *   <li> {@link #divide}   </li>
 *   <li> {@link #multiply} </li>
 *   <li> {@link #subtract} </li>
 * </ul>
 * <p>
 * <b>Executing logical comparisons.</b> You can check if one operand is
 * greater than, less than, equal to, or not equal to another operand in
 * the stack by using the methods:
 * <ul>
 *   <li> {@link #equals}        </li>
 *   <li> {@link #greater}       </li>
 *   <li> {@link #greater_equal} </li>
 *   <li> {@link #lower}         </li>
 *   <li> {@link #lower_equal}   </li>
 *   <li> {@link #not_equal}     </li>
 * </ul>
 * The methods above will use both of the topmost (most recent) values in
 * the stack, and will push back the result of their comparison.
 * <p>
 * <b>Storing and removing temporary values in the Machine stack.</b> You can
 * use the following methods to store or remove short-lived temporary values
 * from the stack:
 * <ul>
 *   <li> {@link #push}  </li>
 *   <li> {@link #pop}   </li>
 * </ul>
 * <p>
 * <b>Jump instructions.</b> You can use the following methods to execute jump instructions:
 * <ul>
 *   <li> {@link #jump}           </li>
 *   <li> {@link #jump_if_false}  </li>
 *   <li> {@link #jump_if_true}   </li>
 * </ul>
 * The first method transfers control unconditionally to another instruction.
 * The other two methods are conditional jumps that use the topmost value of
 * the stack to decide if the jump should be executed or not.
 * <p>
 * <b>Executing subroutines.</b>You can start and stop subroutines by using the following methods:
 * <ul>
 *   <li> {@link #call}                  </li>
 *   <li> {@link #return_from_procedure} </li>
 * </ul>
 * The first method starts a subprocess specified in the instruction argument.
 * The second method stops the execution of the topmost subprogram in the
 * {@link #StackFrame} and return to the last process activated before this one.
 * <p>
 * <b>Allocating and freeing memory in the StackFrame.</b> You can reserve/free
 * space to use local variables inside subprograms by using the following methods:
 * <ul>
 *   <li> {@link #alloc}  </li>
 *   <li> {@link #free}   </li>
 * </ul>
 * <p>
 * <b>Starting a Machine with a set of instructions.</b> As an example, you
 * can start a program by constructing a <b>Machine</b> object with a vector
 * of {@link #Instruction}. After the initialization the {@link #execute()}
 * method must be called to start the main program, just like below:
 * <pre>
 * vector<Instruction> prog = (...);
 * Machine m (prog);
 * m.execute();
 * </pre>
 * By doing this, the machine will execute the array of instructions until
 * it reach an <b>END</b> code.
 */
class Machine : public EntityMove {

    private:
        /** Any function that belongs to this class will be of this type.*/
        typedef void (Machine::*Function)();

        /**
         * Represents the main stack during the program execution.
         * It's used to hold temporary values.
         */
        stack<OperandPtr> data;

        /**
         * Stores functions pointers and its respective code.
         */
        map<Code, Function> functions;

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
        StackFrame memo;

        /**
         * Represents the program, a set of instructions to be
         * executed during running time.
         */
        vector<Instruction> program;

        /**
         * Indicates whether or not the code has reached its end.
         */
        bool stop;

        /**
         * Stores system functions pointers and its respective code.
         */
        map<SystemCode, Function> systemFunctions;

        /**
         * @brief Maps any function of this class that is directly related to an
         *        instruction. It's a more elegant way to express a switch-case.
         */
        void map_functions();

        /**
         * @brief Prints a string with extra information about it.
         *
         * @param [s] The string to be printed.
         */
        void print(const string &s);

        /**
         * @brief Resets the <b>Machine</b> to its original state.
         *
         * Removes all the data from the <b>Machine</b> so it can
         * be fully used again.
         */
        void reset();

    public:
        /**
         * @brief Constructs a <b>Machine</b> with the specified set
         *        set of instructions and a position in the hexagonal grid.
         *
         * @param [prog] A set of instructions representing a program.
         *
         * @param [pos]  The initial position in the grid.
         *
         * @param [image_path] The path to this <b>Machine</b> sprite.
         */
        explicit Machine(const Program &program,
                         const Hex &pos = Hex(0, 0),
                         const string &image_path = "");

        /**
         * @brief Sums both of the topmost values of the stack.
         *
         * Pops both of the topmost (most recent) values of the
         * stack, then replaces those two values by their sum.
         */
        void add();

        /**
         * @brief Pushes the specified attribute of the topmost element of the stack.
         *
         * Pops the topmost element of the stack and pushes its attribute specified
         * by the instruction's argument.
         */
        void atr();

        /**
         * @brief Long range attack on another robot. Called through a system call.
         *
         * Requests the arena to attack another robot in long range in a given
         * direction. The direction is given in the stack, which is popped after
         * this is called.
         */
        void attack_long();

        /**
         * @brief Melee attacks another robot. Called through a system call.
         *
         * Requests the arena to melee attack another robot in a given
         * direction. The direction is given in the stack, which is popped
         * after this is called.
         */
        void attack_melee();

        /**
         * @brief Short range attack on another robot. Called through a system call.
         *
         * Requests the arena to attack another robot in short range in a given
         * direction. The direction is given in the stack, which is popped after
         * this is called.
         */
        void attack_short();

        /**
         * @brief Starts the execution of a subroutine.
         *
         * Jumps to a subroutine specified by the argument of the
         * current instruction pointed by the Instruction Pointer.
         */
        void call();

        /**
         * @brief Collects a crystal. Called through a system call.
         *
         * Requests the arena to collect a crystal in a neighboring cell
         * in a given direction. The direction is given in the stack,
         * which is popped after this is called.
         */
        void collect_crystal();

        /**
         * @brief Divides both of the topmost values of the stack.
         *
         * Pops both of the topmost (most recent) values of the stack,
         * then replaces those two values by their quotient.
         */
        void divide();

        /**
         * @brief Drops a crystal. Called through a system call.
         *
         * Requests the arena to drop a crystal in a neighboring cell
         * in a given direction. The direction is given in the stack,
         * which is popped after this is called.
         */
        void drop_crystal();

        /**
         * @brief Duplicates the topmost value of the stack.
         *
         * Pushes a copy of the topmost (most recent) value of the stack.
         */
        void duplicate();

        /**
         * @brief Sets the new offset at memory.
         *
         * Sets the offset specified by the argument of the
         * current instruction in the <b>StackFrame</b>.
         */
        void entry();

        /**
         * @brief Executes an equals comparison for both of the topmost
         *        values of the stack.
         *
         * Pops both of topmost (most recent) values of the stack,
         * then replaces those two values by the result of their
         * equality comparison (n1 == n2).
         */
        void equals();

        /**
         * @brief Calls {@link #update()} until the <b>Machine</b> no longer has
         *        code to execute.
         */
        void execute();

        /**
         * @brief Returns the argument of the current instruction that is
         *        being executed.
         *
         * @return The argument of the current instruction.
         */
        OperandPtr fetch_arg() const;

        /**
         * @brief Returns the code of the current instruction that is
         *        being executed.
         *
         * @return The code of the current instruction.
         */
        Code fetch_code() const;

        /**
         * @brief Executes an greater comparison for both of the topmost
         *        values of the stack.
         *
         * Pops both of topmost (most recent) values of the stack, then
         * replaces those two values by the result of their "greater than"
         * comparison (n1 < n2).
         */
        void greater();

        /**
         * @brief Executes an greater equals comparison for both of the topmost
         *        values of the stack.
         *
         * Pops both of the topmost (most recent) values of the stack,
         * then replaces those two values by the result of their
         * "greater equal" comparison (n1 <= n2).
         */
        void greater_equal();

        /**
         * @brief Executes an unconditional jump.
         *
         * Jumps to the instruction specified by the argument
         * of the jump function.
         */
        void jump();

        /**
         * @brief Executes a jump if the topmost value of the stack is false.
         *
         * Jumps to the instruction specified by the argument of the
         * jump function if the topmost (most recent) value of
         * the stack is false.
         */
        void jump_if_false();

        /**
         * @brief Executes a jump if the topmost value of the stack is true.
         *
         * Jumps to the instruction specified by the argument of the
         * jump function if the topmost (most recent) value of
         * the stack is true.
         */
        void jump_if_true();

        /**
         * @brief Executes an lower comparison for both of the topmost
         *        values of the stack.
         *
         * Pops both of the topmost (most recent) values of the stack, then
         * replaces those two values by the result of their "lower than"
         * comparison (n1 > n2).
         */
        void lower();

        /**
         * @brief Executes an lower equals comparison for both of the topmost
         *        values of the stack.
         *
         * Pops both of the topmost (most recent) values of the stack, then
         * replaces those two values by the result of their "lower equal"
         * comparison (n1 >= n2).
         */
        void lower_equal();

        /**
         * @brief Moves the entity in a direction. Called through a system call.
         *
         * Requests the arena to move the entity to a neighboring cell in a
         * specific direction. The direction is given in the stack, which is
         * popped after this is called.
         */
        void move() override;

        /**
         * @brief Multiplies both of the topmost values of the stack.
         *
         * Pops both of the topmost (most recent) values of the stack,
         * then replaces those two values by their product.
         */
        void multiply();

        /**
         * @brief Pushes the specified attribute of the current entity.
         *
         * Pushes the attribute specified by the instruction's argument.
         */
        void my_attribute();

        /**
         * @brief Executes an not equals comparison for both of the topmost
         *        values of the stack.
         *
         * Pops both of the topmost (most recent) values of the stack, then
         * replaces those two values by the result of their "not equal"
         * comparison (n1 != n2).
         */
        void not_equal();

        /**
         * @brief Executes an instruction that does nothing.
         */
        void no_operation();

        /**
         * @brief Pops the topmost (most recent) value of the stack.
         */
        void pop();

        /**
         * @brief Prints the topmost value of the stack.
         *
         * Pops and prints the topmost (most recent) value of the stack.
         */
        void print();

        /**
         * @brief Pushes a value to the stack.
         *
         * Pushes the argument of the current instruction pointed by
         * the Instruction Pointer.
         */
        void push();

        /**
         * @brief Returns to the last subroutine active.
         */
        void return_from_procedure();

        /**
         * @brief Pushes an global variable to the top of the stack.
         *
         * Pushes the global variable at the position indicated by
         * the argument of the current instruction pointed by the
         * Instruction Pointer.
         */
        void recall();

        /**
         * @brief Pushes a cell to the top of the stack.
         *
         * Request the {@link Arena} to store a reference for a specific grid cell
         * int the top of the stack, so its attributes can be analyzed.
         */
        void see();

        /**
         * @brief Initialize a new set of instructions to this <b>Machine</b>.
         *
         * @param [program] The new set of instructions to be executed.
         */
        void set_program(const Program &program) override;

        /**
         * @brief Stores a value as a global variable.
         *
         * Stores the topmost (most recent) value of the stack as
         * a global variable in the memory of the <b>Machine</b>.
         */
        void store();

        /**
         * @brief Substracts both of the topmost values of the stack.
         *
         * Pops both of the topmost (most recent) values of the stack,
         * then replaces those two values by their subtraction.
         */
        void subtract();

        /**
         * @brief Calls a system function given as a parameter.
         *
         * Calls another function given as a parameter, usually to perform an action
         * in the arena, consisting of a system call.
         */
        void system();

        /**
         * @brief Returns a pointer to the topmost element in the stack.
         *
         * @return A pointer to the topmost element in the stack.
         */
        OperandPtr top() const;

        /**
         * @brief Runs the current virtual machine for a determined
         *        amount of cycles.
         */
        void update() override;
};

#endif
