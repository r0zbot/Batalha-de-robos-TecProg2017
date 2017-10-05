# Usage:
#   (1) $ python builder.py < input.txt > output.cpp
#   (2) $ python builder.py input.txt > output.cpp

import fileinput
import sys


class Builder:

    TODO = "// Move this file to /VirtualMachine/src so this can work on production"

    INCLUDES = (
        '#include <vector>\n',
        '#include <code.h>',
        '#include <instruction.h>',
        '#include <machine.h>'
    )

    @classmethod
    def create_header(cls):
        print(cls.TODO + "\n")
        for i in cls.INCLUDES:
            print(i)
        print("\nusing namespace std;\n")

    @classmethod
    def create_main(cls):
        print("int main() {\n")
        cls.decode_input()
        print("    Machine m (prog);")
        print("    m.execute();")
        print("    return 0;\n}")

    @classmethod
    def decode_input(cls):
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
        if '#' in line:
            line = line[:line.find("#")]
        return line.strip()


if __name__ == "__main__":
    Builder.create_header()
    Builder.create_main()
    sys.exit(0)  # TODO: return something else to indicate exception
