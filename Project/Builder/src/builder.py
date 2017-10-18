import fileinput
import sys


class Builder:
    """This class works as a code interpreter.

    The Builder class can read assembly code files and return its code translation
    as a source file to be execute by a Virtual Machine.

    The input code accepted corresponds to a set of instruction's code and its
    respectives arguments. The set of instructions will be translated to the
    Virtual Machine's native language.

    Any blank lines or code comments (lines that starts whit #) will be ignored.

    Attributes:
        INCLUDES (str): Stores all the dependencies to be linked in the
                        resulting source file.

        TODO (str):     Represents an observation explaining where the
                        resulting source file should be placed so it can
                        work correctly.

    Example:
        The builder class read a direct input from 'stdin'::
            $ python builder.py < input.txt > output.cpp

        Or you can simply pass the input file name as an argument to the program::
            $ python builder.py input.txt > output.cpp
    """

    __INCLUDES = (
        '#include <vector>\n',
        '#include <controller/classes/code.h>',
        '#include <controller/classes/instruction.h>',
        '#include <model/entity/machine.h>'
    )

    __TODO = "// Move this file to /VirtualMachine/src so this can work on production"

    @classmethod
    def create_header(cls):
        """Creates the resulting source file header, including all its dependencies
        and observations to explain how it works.
        """
        print(cls.__TODO + "\n")
        for i in cls.__INCLUDES:
            print(i)
        print("\nusing namespace std;\n")

    @classmethod
    def create_main(cls):
        """Creates the main method containing a vector of instructions to be
        executed by a Virtual Machine
        """
        print("int main() {\n")
        cls.decode_input()
        print("    Machine m (prog);")
        print("    m.execute();")
        print("    return 0;\n}")

    @classmethod
    def decode_input(cls):
        """Decodes the assembly code passed as input text to a vector of
        instructions to be passed to a Virtual Machine.

        Any line in the input that corresponds to a comment or any blank
        line is ignored in the decode process.
        """
        ip = 0
        labels = {}
        instructions = []
        print("    vector<Instruction> prog ({")
        for line in fileinput.input():
            line = cls.remove_comments(line)
            if line.strip():
                instructions.append(line)
                if ":" in line:
                    labels[line.split()[0][:-1]] = ip
                ip += 1
        ip = 0
        for line in instructions:
            op_code = ""
            arg = 0
            keys = line.split()
            if len(keys) > 0 and keys[0].endswith(":"):
                keys.pop(0)
            if len(keys) > 0:
                op_code = keys.pop(0)
            if len(keys) > 0:
                arg = keys.pop(0)
                if arg in labels:
                    arg = labels[arg]
            aux = "," if (ip != 0) else ""
            print("        {}Instruction(Code::{}, {})".format(aux, op_code.upper(), arg))
            ip += 1
        print("    });\n")

    @classmethod
    def remove_comments(cls, line):
        """Remove any comments presents in the specified string.

        Args:
            line (str): The line of code with comments to be removed.

        Returns:
            str: The specified line without code comments.
        """
        if '#' in line:
            line = line[:line.find("#")]
        return line.strip()


if __name__ == "__main__":
    Builder.create_header()
    Builder.create_main()
    sys.exit(0)
