

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
        '#include <controller/classes/action.h>',
        '#include <controller/classes/number.h>',
        '#include <controller/classes/instruction.h>\n',
	'#include <controller/classes/core.h>\n'
        '#include <model/entity/machine.h>',
        '#include <util/globals.h>',
        '#include <util/sleep.h>'
    )

    __TODO = "// Move this file to /VirtualMachine/src so this can work on production"

    @classmethod
    def create_army(cls, outputFile, name, id):
        outputFile.write("\n\tArmy army"+str(id)+"(\""+name+"\");\n")
        outputFile.write("\tarena.insert_army(army"+str(id)+");\n")

    @classmethod
    def create_robots(cls, outputFile, filename, amount, army_id, id):
        cls.decode_file(outputFile, open(filename, "r"), id)
        outputFile.write("\tfor(int i=0; i<"+amount+"; i++)\n")
        outputFile.write("\t\tarena.create_robot(army"+str(army_id)+".get_id(), prog"+str(id)+");\n")

    @classmethod
    def create_header(cls, outputFile):
        """Creates the resulting source file header, including all its dependencies
        and observations to explain how it works.
        """
        outputFile.write(cls.__TODO + "\n\n")
        for i in cls.__INCLUDES:
            outputFile.write(i+"\n")
        outputFile.write("\nusing namespace std;\n\n")

    @classmethod
    def create_globals(cls, outputFile, settings):
        outputFile.write("//Global variables and settings\n")
        outputFile.write("Arena arena;\n")
        outputFile.write("int lastRobotPos = 0;\n")
        for setting in settings:
            outputFile.write(setting+" = "+settings[setting]+";\n")
        outputFile.write("\n")

    @classmethod
    def create_main_beggining(cls, outputFile, arena_terrain):
        outputFile.write("int main() {\n")
        outputFile.write(arena_terrain+"\n")
        outputFile.write("\tarena.import_terrain(terrain);\n")

    @classmethod
    def create_main_end(cls, outputFile, sleep_time):
        outputFile.write("\tCore core(arena);\n")
        outputFile.write("\tcore.start();\n")
        outputFile.write("}\n\n")

    @classmethod
    def decode_file(cls, outputFile, file, id):
        """Decodes the assembly code passed as input text to a vector of
        instructions to be passed to a Virtual Machine.

        Any line in the input that corresponds to a comment or any blank
        line is ignored in the decode process.
        """
        outputFile.write("\tvector<Instruction> prog"+str(id)+" ({\n")

        ip = 0
        labels = {}
        instructions = []
        cls.map_labels(file, instructions, labels)

        for line in instructions:
            op_code = ""
            arg = "nullptr"
            keys = line.split()
            if len(keys) > 0 and keys[0].endswith(":"):
                keys.pop(0)
            if len(keys) > 0:
                op_code = keys.pop(0)
            if len(keys) > 0:
                arg = keys.pop(0)
                if arg in labels:
                    arg = "make_shared<Number>({})".format(labels[arg])
                elif "{" not in arg:
                    arg = "make_shared<Number>({})".format(arg)
                elif "ACTION" in arg:
                    code = keys.pop(0)
                    direction = keys.pop(0)
                    arg = "make_shared<Action>(SystemCode::{}, Direction::{})".format(
                        code[code.find("{") + 1: code.find(",")],
                        direction[direction.find(",") + 1: direction.find("}")])
                elif "CELL" in arg:
                    arg = "make_shared<Hex>("
                    for s in keys:
                        if "{" in s:
                            arg += s[1:s.find(",")] + ", "
                        elif "}" in s:
                            arg += s[:s.find("}")] + ")"
                        else:
                            arg += s[:s.find(",")] + ", "
            comma = "," if (ip != 0) else ""
            outputFile.write("        {}Instruction(Code::{},{})".format(comma, op_code.upper(), arg)+"\n")
            ip += 1
        outputFile.write("    });\n\n")

    @classmethod
    def map_labels(cls, file, instructions, labels):
        """Maps any functions labels present in the Assembly input.

        Args:
            file: a file handle to read from.

            instructions (list): The list of instructions from the input.

            labels (dictionary): An dictionary to store the labels present
                                 in the input.
        """
        ip = 0
        for line in file:
            line = cls.remove_comments(line)
            if line.strip():
                instructions.append(line)
                if ":" in line:
                    labels[line.split()[0][:-1]] = ip
                ip += 1

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

