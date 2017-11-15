# -*- coding: utf-8 -*-
import Tkinter as tkinter
import ttk as ttk
import tkFileDialog


class RemoveButton(tkinter.Button):
    def __init__(self, parent, visible=True, **kwargs):
        if visible:
            tkinter.Button.__init__(self, parent, text="✖", borderwidth=0, **kwargs)
        else:
            tkinter.Button.__init__(self, parent, text="✖", borderwidth=0, state="disabled", **kwargs)


def testVal(inStr,i,acttyp):
    ind=int(i)
    if acttyp == '1': #insert
        if not inStr[ind].isdigit():
            return False
    return True


class RobotSelector(ttk.Frame):
    def __init__(self, parent):
        ttk.Frame.__init__(self, parent)
        self.parent = parent

        #self.removeButton = ttk.Button(self, text="X", command=self.remove)
        #self.removeButton.pack(side="left", padx=5)
        RemoveButton(self, command=self.remove).pack(side="left", padx=5)

        ttk.Label(self, text="Quantity:  ").pack(side="left")
        self.robotAmountInput = ttk.Entry(self, width=5, validate="key")
        self.robotAmountInput['validatecommand'] = (self.robotAmountInput.register(testVal), '%P', '%i', '%d')
        self.robotAmountInput.insert(0, "5")
        self.robotAmountInput.pack(side="left")

        self.robotFilename = tkFileDialog.askopenfilename(title="Select Robot's Program", filetypes=[(".gubi", "*.gubi"), ("All files","*")])
        if not self.robotFilename:
            self.remove()

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

    def __init__(self, parent):
        ttk.Frame.__init__(self, parent)
        self.armies = []

        self.title = ttk.Label(self, text="Choose your armies and robots", anchor="n", font=("Helvetica", 16))
        self.title.pack(side="top", fill="x", pady=30)

        self.armyFrame = ttk.Frame(self)
        self.addArmy(False)
        self.addArmy(False)
        self.armyFrame.pack(fill="x")

        ttk.Button(self, text="Add Army", command=self.addArmy).pack(pady=10)

        self.runButton = ttk.Button(self, text="Run!", command=self.run)
        self.runButton.pack(side="bottom", pady=30, ipadx=40, ipady=10)

    def addArmy(self, removable=True):
        armySelection = ArmySelector(self.armyFrame, self, len(self.armies)+1, removable)
        self.armies.append(armySelection)
        armySelection.pack(side="top", fill="x", padx=30)

    def run(self):
        for army in self.armies:
            for robot in army.robots:
                if robot is not None:
                    print(army.armyNameEntry.get()+" - "+robot.robotAmountInput.get() + " - " + robot.robotFilename)

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
    configWindow.title("Robot battle configuration")
    ConfigScreen(configWindow).pack(fill="both", expand=True)
    w = 430
    h = 500

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