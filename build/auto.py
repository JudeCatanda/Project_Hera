import os
import subprocess
from tkinter import *
from tkinter import messagebox

def build():
    os.system("cls")
    proc = subprocess.Popen(["ninja"], stdout=subprocess.PIPE, shell=True)
    (out, err) = proc.communicate()
    messagebox.showinfo("Comp", out)

def run_hera():
    os.system("cls")
    proc = subprocess.Popen([".\hera.exe"], stdout=subprocess.PIPE, shell=True)
    (out, err) = proc.communicate()
    messagebox.showinfo("Run", out)

def re_config_cmake():
    os.system("cls")
    os.system("cd C:\\Users\\User\\Documents\\C++\\hera && cmake -G\"Ninja\" -B build")

def CLS():
    os.system("cls")


BuildWindow = Tk()
BuildWindow.title("Build Tool")
BuildWindow.geometry("800x600")

BuildButtonCommand = Button(BuildWindow, text="Build With Ninja", command=build)
BuildButtonCommand.pack()

RunHeraButtonCommand = Button(BuildWindow, text="Run Hera", command=run_hera)
RunHeraButtonCommand.pack()

ReConfigCmakeButtonCommand = Button(BuildWindow, text="Re-Configure Cmake", command=re_config_cmake)
ReConfigCmakeButtonCommand.pack()

ClearTheCommandLineScreenButtonCommand = Button(BuildWindow, text="Clear", command=CLS)
ClearTheCommandLineScreenButtonCommand.pack()

BuildWindow.mainloop()
