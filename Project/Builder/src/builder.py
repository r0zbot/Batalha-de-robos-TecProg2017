# The 'fileinput' module will loop through all the lines in the input
# specified as file names given in command-line arguments,
# or the standard input if no arguments are provided.
#
# Usage:
#   (1) $ python builder.py < input.txt > output.cpp
#   (2) $ python builder.py input.txt > output.cpp

import fileinput


class Builder:

    TODO = "//Move this file to /VirtualMachine/src so this can work on production"

    INCLUDES = (
        '#include "../include/code.h"',
        '#include "../include/instruction.h"',
        '#include "../include/machine.h"'
    )

    @classmethod
    def create_header(cls):
        print(cls.TODO + "\n")
        for i in cls.INCLUDES:
            print(i)
        print()

    @classmethod
    def create_main(cls):
        print("int main() {")
        print("\tMachine m (prog);")
        print("\tm.execute();")
        print("\treturn 0;\n}")

    @classmethod
    def decode_input(cls):
        ip = 0
        labels = {}
        print("Instruction prog[] = {")
        for line in fileinput.input():
            line = cls.remove_comments(line)
            if line.strip():
                opCode = ""
                arg = 0
                keys = line.split()
                if len(keys) > 0 and keys[0].endswith(":"):
                    labels[keys[0][:-1]] = ip
                    keys.pop(0)
                if len(keys) > 0:
                    opCode = keys.pop(0)
                if len(keys) > 0:
                    arg = keys.pop(0)
                    if arg in labels:
                        arg = labels[arg]
                aux = "," if (ip != 0) else ""
                print("\t{}Instruction(Code::{}, {})".format(aux, opCode.upper(), arg))
                ip += 1
        print("};\n")

    @classmethod
    def remove_comments(cls, line):
        if '#' in line:
            line = line[:line.find("#")]
        return line.strip()


if __name__ == "__main__":
    Builder.create_header()
    Builder.decode_input()
    Builder.create_main()
