# -*- coding: utf-8 -*-
from builder import Builder
import Tkinter as tkinter
import ttk as ttk
import tkFileDialog
import tkMessageBox
import platform
import os
import random

configWindow = None


def validateFloat(inStr, i, acttyp):
    ind = int(i)
    if acttyp == '1':  # insert
        if (inStr[ind].isdigit() or inStr[ind] == "."):
            try:
                x = float(inStr)
            except:
                return False
        else:
            return False
    return True


def validateInt(inStr, i, acttyp):
    ind = int(i)
    if acttyp == '1':  # insert
        if not inStr[ind].isdigit():
            return False
    return True


class RemoveButton(tkinter.Button):
    def __init__(self, parent, visible=True, **kwargs):
        if visible:
            tkinter.Button.__init__(self, parent, text="✖", borderwidth=0, **kwargs)
        else:
            tkinter.Button.__init__(self, parent, text="✖", borderwidth=0, state="disabled", **kwargs)


class NumberSetting(ttk.Frame):
    def __init__(self, parent, text, default, isFloat=False):
        ttk.Frame.__init__(self, parent)
        ttk.Label(self, text=text + ":  ").pack(side="left")
        self.entry = ttk.Entry(self, width=10, validate="key")
        if isFloat:
            self.entry['validatecommand'] = (self.entry.register(validateFloat), '%P', '%i', '%d')
        else:
            self.entry['validatecommand'] = (self.entry.register(validateInt), '%P', '%i', '%d')
        self.entry.insert(0, default)
        self.entry.pack(side="right")
        self.pack(fill="x", padx=40, pady=1)


class RobotSelector(ttk.Frame):
    def __init__(self, parent):
        ttk.Frame.__init__(self, parent)
        self.parent = parent

        RemoveButton(self, command=self.remove).pack(side="left", padx=5)

        ttk.Label(self, text="Quantity:  ").pack(side="left")
        self.robotAmountInput = ttk.Entry(self, width=5, validate="key")
        self.robotAmountInput['validatecommand'] = (self.robotAmountInput.register(validateInt), '%P', '%i', '%d')
        self.robotAmountInput.insert(0, "5")
        self.robotAmountInput.pack(side="left")

        self.robotFilename = tkFileDialog.askopenfilename(title="Select Robot's Program",
                                                          filetypes=[(".gubi", "*.gubi"), ("All files", "*")])
        if not self.robotFilename:
            configWindow.after(0, self.remove)

        ttk.Label(self, text="  ..." + self.robotFilename[-20:]).pack(side="right")

    def remove(self):
        self.parent.robots.remove(self)
        self.pack_forget()
        self.destroy()


class ArmySelector(ttk.Frame):
    def __init__(self, parentFrame, parentClass, armyNumber, removable):
        ttk.Frame.__init__(self, parentFrame)
        self.parent = parentClass
        self.robots = []
        self.armyTitleFrame = ttk.Frame(self)

        RemoveButton(self.armyTitleFrame, removable, command=self.remove).pack(side="left", padx=5)

        self.armyLabel = ttk.Label(self.armyTitleFrame, text="Army name: ")
        self.armyLabel.pack(side="left")

        self.addRobotButton = ttk.Button(self.armyTitleFrame, text="Add Robots", command=self.addRobot)
        self.addRobotButton.pack(side="right")

        self.armyNameEntry = ttk.Entry(self.armyTitleFrame)
        self.armyNameEntry.insert(0, "Army " + str(armyNumber))
        self.armyNameEntry.pack(side="right", fill="x", padx=10, expand=True)

        self.armyTitleFrame.pack(side="top", fill="x")

    def addRobot(self):
        robotInput = RobotSelector(self)
        self.robots.append(robotInput)
        robotInput.pack(pady=2)

    def remove(self):
        for robot in self.robots:
            robot.remove()
        self.parent.armies.remove(self)
        self.pack_forget()
        self.destroy()


# https://stackoverflow.com/questions/16188420/python-tkinter-scrollbar-for-frame

class VerticalScrolledFrame(ttk.Frame):
    """A pure Tkinter scrollable frame that actually works!
    * Use the 'interior' attribute to place widgets inside the scrollable frame
    * Construct and pack/place/grid normally
    * This frame only allows vertical scrolling

    """

    def __init__(self, parent, *args, **kw):
        ttk.Frame.__init__(self, parent, *args, **kw)

        # create a canvas object and a vertical scrollbar for scrolling it
        vscrollbar = ttk.Scrollbar(self, orient="vertical")
        vscrollbar.pack(fill="y", side="right", expand="false")
        canvas = tkinter.Canvas(self, bd=0, highlightthickness=0,
                                yscrollcommand=vscrollbar.set)
        canvas.pack(side="left", fill="both", expand="true")
        vscrollbar.config(command=canvas.yview)

        # reset the view
        canvas.xview_moveto(0)
        canvas.yview_moveto(0)

        # create a frame inside the canvas which will be scrolled with it
        self.interior = interior = ttk.Frame(canvas)
        interior_id = canvas.create_window(0, 0, window=interior,
                                           anchor="nw")

        # track changes to the canvas and frame width and sync them,
        # also updating the scrollbar
        def _configure_interior(event):
            # update the scrollbars to match the size of the inner frame
            size = (interior.winfo_reqwidth(), interior.winfo_reqheight())
            canvas.config(scrollregion="0 0 %s %s" % size)
            if interior.winfo_reqwidth() != canvas.winfo_width():
                # update the canvas's width to fit the inner frame
                canvas.config(width=interior.winfo_reqwidth())

        interior.bind('<Configure>', _configure_interior)

        def _configure_canvas(event):
            if interior.winfo_reqwidth() != canvas.winfo_width():
                # update the inner frame's width to fill the canvas
                canvas.itemconfigure(interior_id, width=canvas.winfo_width())

        canvas.bind('<Configure>', _configure_canvas)


class ConfigScreen(ttk.Frame):

    def __init__(self, parent):
        ttk.Frame.__init__(self, parent)
        self.armies = []
        self.outputFilename = ""
        self.terrain = ""

        # Running assincronously to avoid locking the text Entries
        configWindow.after(100, self.selectMainFile)

        ttk.Label(self, text="Arena Settings", anchor="n", font=("Helvetica", 16)).pack(side="top", fill="x", pady=30)
        self.terrainFrame = ttk.Frame(self)
        self.terrainButton = ttk.Button(self.terrainFrame, text="Open arena terrain file...", command=self.selectTerrainFile)
        self.terrainButton.pack(side="right")
        self.terrainGenerateButton = ttk.Button(self.terrainFrame, text="Generate random terrain ", command=self.showTerrainGenerationOptions)
        self.terrainGenerateButton.pack(side="right")
        self.terrainButton.pack(side="right")
        self.terrainFrame.pack()

        ttk.Label(self).pack(pady=3)  # spacing

        self.machineInstructions = NumberSetting(self, "Instructions per turn per machine", 50)
        self.sleepTime = NumberSetting(self, "Sleep time (in ms) per turn", 1000)
        self.availableCrystals = NumberSetting(self, "Available crystals", 120)
        self.maxCrystals = NumberSetting(self, "Maximum amount of crystals per cell", 20)
        self.robotHealth = NumberSetting(self, "Robot starting health", 100)
        self.robotMeleeAttack = NumberSetting(self, "Robot melee attack damage", 20)
        self.robotFuel = NumberSetting(self, "Robot starting fuel", 100, True)
        self.robotFuelUsage = NumberSetting(self, "Fuel usage per movement", 1.5, True)
        self.robotInstructionFuelUsage = NumberSetting(self, "Fuel usage per instruction", 0.01, True)
        # uncoment when implemented
        # self.robotShortAttack = NumberSetting(self, "Robot short range attack damage", 25)
        # self.robotLongAttack = NumberSetting(self, "Robot long range attack damage", 30)



        ttk.Label(self, text="Armies and robots", anchor="n", font=("Helvetica", 16)).pack(side="top", fill="x",pady=30)

        self.armyFrame = ttk.Frame(self)
        self.addArmy(False)
        self.addArmy(False)
        self.armyFrame.pack(fill="x")

        ttk.Button(self, text="Add Army", command=self.addArmy).pack(pady=10)

        ttk.Button(self, text="Save and Run!", command=self.run).pack(side="bottom", pady=30, ipadx=40, ipady=10)

    def generateTerrain(self):
        height = self.heightEntry.entry.get()
        width = self.widthEntry.entry.get()
        self.terrain = "\tint terrain["+height+"]["+width+"] = {\n"
        for i in range(0, int(height)):
            self.terrain += "\t\t{"
            for j in range(0, int(width)):
                self.terrain += str(random.randint(0, 4))+", "
            self.terrain += "}, \n"
        self.terrain += "\t};"
        self.terrain = self.terrain.replace(", }", "}")
        self.terrainGenerateButton.configure(text="Done!", command=self.generateTerrain)
        print(self.terrain)

    def showTerrainGenerationOptions(self, ):
        ttk.Label(self.terrainFrame, text="Generate random terrain:").pack()
        self.widthEntry = NumberSetting(self.terrainFrame, "Width", 20)
        self.widthEntry.pack()
        self.heightEntry = NumberSetting(self.terrainFrame, "Height", 10)
        self.heightEntry.pack()
        self.terrainButton.pack_forget()
        self.terrainGenerateButton.configure(text="Generate", command=self.generateTerrain)

    def selectMainFile(self):
        self.outputFilename = tkFileDialog.askopenfilename(title="Select main file",
                                                          filetypes=[("Main file", "main.cpp"), ("All files", "*")])
        if not self.outputFilename:
            os._exit(1)

    def selectTerrainFile(self):
        filename = tkFileDialog.askopenfilename(title="Select a terrain file",
                                                filetypes=[(".terrain", "*.terrain"), ("All files", "*")])
        if filename:
            self.terrain = open(filename, "r").read()
            self.terrainButton.configure(text="Selected!")
            self.terrainGenerateButton.pack_forget()

    def addArmy(self, removable=True):
        armySelection = ArmySelector(self.armyFrame, self, len(self.armies) + 1, removable)
        self.armies.append(armySelection)
        armySelection.pack(side="top", fill="x", padx=30)

    def run(self):

        if not self.terrain:
            tkMessageBox.showerror("Missing terrain", "Please select or generate a terrain!")
            return

        outputFile = open(self.outputFilename, "w")
        Builder.create_header(outputFile)

        settings = {"int machineInstructionsPerCycle": self.machineInstructions.entry.get(),
                    "int arenaSleepTime": self.sleepTime.entry.get(),
                    "int availableCrystals": self.availableCrystals.entry.get(),
                    "int maxCrystalsPerCell": self.maxCrystals.entry.get(),
                    "unsigned int robotHealth": self.robotHealth.entry.get(),
                    "int robotMeleeAttack": self.robotMeleeAttack.entry.get(),
                    "double robotFuel": self.robotFuel.entry.get(),
                    "double robotMovFuelUsage": self.robotFuelUsage.entry.get(),
                    "double robotInstFuelUsage": self.robotInstructionFuelUsage.entry.get()}

        Builder.create_globals(outputFile, settings)

        Builder.create_main_beggining(outputFile, self.terrain)
        currentArmy = 0
        currentRobot = 0
        for army in self.armies:
            currentArmy += 1
            Builder.create_army(outputFile, army.armyNameEntry.get(), currentArmy)
            for robot in army.robots:
                if robot is not None:
                    currentRobot += 1
                    Builder.create_robots(outputFile, robot.robotFilename, robot.robotAmountInput.get(), currentArmy,
                                          currentRobot)
        Builder.create_main_end(outputFile, self.sleepTime.entry.get())
        outputFile.close()
        if platform.system() == "Windows":
            os.startfile(os.path.join(os.path.dirname(self.outputFilename), '..\\build.bat'))
        else:
            # OBS: untested!
            os.system(os.path.join(os.path.dirname(self.outputFilename), '../build.sh'))

    def calculate(self):
        # get the value from the input widget, convert
        # it to an int, and do a calculation
        try:
            i = int(self.entry.get())
            result = "%s*2=%s" % (i, i * 2)
        except ValueError:
            result = "Please enter digits only"

        # set the output widget to have our result
        self.output.configure(text=result)


if __name__ == "__main__":
    configWindow = tkinter.Tk(className="ConfigScreen")
    configWindow.title("Robot battle configurator")
    w = 430
    h = 750

    # get screen width and height
    ws = configWindow.winfo_screenwidth()
    hs = configWindow.winfo_screenheight()

    # calculate x and y coordinates for the Tk root window
    x = (ws / 2) - (w / 2)
    y = (hs / 2) - (h / 2)

    # set the dimensions of the screen
    # and where it is placed
    configWindow.geometry('%dx%d+%d+%d' % (w, h, x, y))
    scrollFrame = VerticalScrolledFrame(configWindow)
    scrollFrame.pack(fill="both", expand=True)
    ConfigScreen(scrollFrame.interior).pack(fill="both", expand=True)
    configWindow.mainloop()
