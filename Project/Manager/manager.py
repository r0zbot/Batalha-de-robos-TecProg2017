# -*- coding: utf-8 -*-
from builder import Builder
import Tkinter as tkinter
import ttk as ttk
import tkFileDialog
import tkMessageBox
import platform
import os

configWindow = None

def testVal(inStr, i, acttyp):
    ind=int(i)
    if acttyp == '1': #insert
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
    def __init__(self, parent, text, default):
        ttk.Frame.__init__(self, parent)
        ttk.Label(self, text=text+":  ").pack(side="left")
        self.entry = ttk.Entry(self, width=10, validate="key")
        self.entry['validatecommand'] = (self.entry.register(testVal), '%P', '%i', '%d')
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
        self.robotAmountInput['validatecommand'] = (self.robotAmountInput.register(testVal), '%P', '%i', '%d')
        self.robotAmountInput.insert(0, "5")
        self.robotAmountInput.pack(side="left")

        self.robotFilename = tkFileDialog.askopenfilename(title="Select Robot's Program", filetypes=[(".gubi", "*.gubi"), ("All files","*")])
        if not self.robotFilename:
            configWindow.after(0, self.remove)

        ttk.Label(self, text="  ..."+self.robotFilename[-20:]).pack(side="right")

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
        self.armyNameEntry.insert(0, "Army "+str(armyNumber))
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



class ConfigScreen(ttk.Frame):

    terrainFile = None

    def __init__(self, parent):
        ttk.Frame.__init__(self, parent)
        self.armies = []


        self.outputFilename = tkFileDialog.askopenfilename(title="Select main file",
                                         filetypes=[("Main file", "main.cpp"), ("All files", "*")])
        if not self.outputFilename:
            configWindow.after(0, parent.destroy)

        ttk.Label(self, text="Arena Settings", anchor="n", font=("Helvetica", 16)).pack(side="top", fill="x", pady=30)
        self.terrainButton = ttk.Button(self, text="Select arena terrain file...", command=self.selectTerrainFile)
        self.terrainButton.pack()

        ttk.Label(self).pack(pady=3) # spacing

        self.machineInstructions = NumberSetting(self, "Instructions per turn per machine", 50)
        self.sleepTime = NumberSetting(self, "Sleep time (in ms) per turn", 200)
        self.availableCrystals = NumberSetting(self, "Available crystals", 120)
        self.maxCrystals = NumberSetting(self, "Maximum amount of crystals per cell", 120)
        self.robotFuel = NumberSetting(self, "Robot starting fuel", 100)
        self.robotHealth = NumberSetting(self, "Robot starting health", 100)
        self.robotMeleeAttack = NumberSetting(self, "Robot melee attack damage", 20)
        self.robotFuelUsage = NumberSetting(self, "Fuel usage per movement", 20)
        # uncoment when implemented
        # self.robotShortAttack = NumberSetting(self, "Robot short range attack damage", 25)
        # self.robotLongAttack = NumberSetting(self, "Robot long range attack damage", 30)



        ttk.Label(self, text="Armies and robots", anchor="n", font=("Helvetica", 16)).pack(side="top", fill="x", pady=30)

        self.armyFrame = ttk.Frame(self)
        self.addArmy(False)
        self.addArmy(False)
        self.armyFrame.pack(fill="x")

        ttk.Button(self, text="Add Army", command=self.addArmy).pack(pady=10)

        ttk.Button(self, text="Save and Run!", command=self.run).pack(side="bottom", pady=30, ipadx=40, ipady=10)

    def selectTerrainFile(self):
        filename = tkFileDialog.askopenfilename(title="Select a terrain file", filetypes=[(".terrain", "*.terrain"), ("All files","*")])
        if filename:
            self.terrainFile = filename
            self.terrainButton.configure(text="Selected!")

    def addArmy(self, removable=True):
        armySelection = ArmySelector(self.armyFrame, self, len(self.armies)+1, removable)
        self.armies.append(armySelection)
        armySelection.pack(side="top", fill="x", padx=30)

    def run(self):

        if not self.terrainFile:
            tkMessageBox.showerror("Missing terrain file", "Please select a terrain file!")
            return
        outputFile = open(self.outputFilename, "w")
        Builder.create_header(outputFile)
        Builder.create_main_beggining(outputFile, self.terrainFile)
        currentArmy = 0
        currentRobot = 0
        for army in self.armies:
            currentArmy += 1
            Builder.create_army(outputFile, army.armyNameEntry.get(), currentArmy)
            for robot in army.robots:
                if robot is not None:
                    currentRobot += 1
                    Builder.create_robots(outputFile, robot.robotFilename, robot.robotAmountInput.get(), currentArmy, currentRobot)
        Builder.create_main_end(outputFile, self.sleepTime.entry.get())
        outputFile.close()
        if platform.system() == "Windows":
            os.startfile(os.path.join(os.path.dirname(self.outputFilename), '..\\build.bat'))
        else:
            #OBS: untested!
            os.system(os.path.join(os.path.dirname(self.outputFilename), '../build.sh'))


        # file = open(os.path.dirname(os.path.abspath(__file__))+"/config.arena", "w")
        # file.write(self.terrainFile+"\n")
        # file.write(self.machineInstructions.entry.get()+"\n")
        # file.write(self.sleepTime.entry.get()+"\n")
        # file.write(self.availableCrystals.entry.get()+"\n")
        # file.write(self.maxCrystals.entry.get()+"\n")
        # file.write(self.robotFuel.entry.get()+"\n")
        # file.write(self.robotHealth.entry.get()+"\n")
        # file.write(self.robotMeleeAttack.entry.get()+"\n")
        # file.write(self.robotFuelUsage.entry.get()+"\n")
        # file.write(str(len(self.armies))+"\n")
        # for army in self.armies:
        #     file.write(army.armyNameEntry.get()+"\n")
        #     file.write(str(len(army.robots))+"\n")
        #     for robot in army.robots:
        #         if robot is not None:
        #             #print(army.armyNameEntry.get()+" - "+robot.robotAmountInput.get() + " - " + robot.robotFilename)
        #             file.write(robot.robotAmountInput.get()+"\n")
        #             file.write(robot.robotFilename+"\n")


    def calculate(self):
        # get the value from the input widget, convert
        # it to an int, and do a calculation
        try:
            i = int(self.entry.get())
            result = "%s*2=%s" % (i, i*2)
        except ValueError:
            result = "Please enter digits only"

        # set the output widget to have our result
        self.output.configure(text=result)

if __name__ == "__main__":
    configWindow = tkinter.Tk(className="ConfigScreen")
    configWindow.title("Robot battle configurator")
    ConfigScreen(configWindow).pack(fill="both", expand=True)
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
    configWindow.mainloop()