#!/usr/bin/env python
"""
A simple example of hooking the keyboard on Linux using pyxhook

Any key pressed prints out the keys values, program terminates when spacebar is pressed
"""

#Libraries we need
import pyxhook
import time
import os

powershell=0
altf2=0

previous_time=0
current_time=0
time_interval=0

#This function is called every time a key is presssed
def kbevent( event ):
    #print key info
    print (event)
    
    global powershell
    global altf2
    global previous_time
    global current_time
    global time_interval


    #Time interval
    current_time=time.time()
    time_interval=current_time-previous_time

    print("previous : %f" %previous_time)
    print("current : %f" %current_time)
    print("time_interval : %f" %time_interval)

    previous_time = current_time

    if(time_interval<0.001):
        os.system("gnome-screensaver-command --lock")       

    #If the ascii value matches spacebar, terminate the while loop
    if event.Ascii == 32:
        global running
        running = False

    #If the ascii value matches f3, terminate the while loop
    if event.Ascii == 65472:
        global running
        running = False


    #p
    if powershell==0:
        if event.Ascii == 112:
            powershell=1
        else:
            powershell=0
    #o
    elif powershell==1:
        if event.Ascii == 111:
            powershell=2
        else:
            powershell=0
    #w
    elif powershell==2:
        if event.Ascii == 119:
            powershell=3
        else:
            powershell=0
    #e
    elif powershell==3:
        if event.Ascii == 101:
            powershell=4
        else:
            powershell=0
    #r
    elif powershell==4:
        if event.Ascii == 114:
            powershell=5
        else:
            powershell=0
    #s
    elif powershell==5:
        if event.Ascii == 115:
            powershell=6
        else:
            powershell=0
    #h
    elif powershell==6:
        if event.Ascii == 104:
            powershell=7
        else:
            powershell=0
    #e
    elif powershell==7:
        if event.Ascii == 101:
            powershell=8
        else:
            powershell=0
    #l
    elif powershell==8:
        if event.Ascii == 108:
            powershell=9
        else:
            powershell=0
    #l
    elif powershell==9:
        if event.Ascii == 108:
            powershell=10
        else:
            powershell=0

    if powershell == 10:
        os.system("gnome-screensaver-command --lock")
        powershell=0


    #alt
    if altf2==0:
        if event.Ascii == 65513 or event.Ascii == 65514:
            altf2=1
        else:
            altf2=0
    elif altf2==1:
        if event.Ascii == 65471:
            altf2=2
        else:
            altf2=0

    if altf2==2:
        os.system("gnome-screensaver-command --lock")
        altf2=0

    #print powershell
    #if event.Ascii == 97:
        #os.system("gnome-screensaver-command --lock")

#Create hookmanager
hookman = pyxhook.HookManager()
#Define our callback to fire when a key is pressed down
hookman.KeyDown = kbevent
#Hook the keyboard
hookman.HookKeyboard()
#Start our listener
hookman.start()
    
#Create a loop to keep the application running
running = True
while running:
    time.sleep(0.1)

#end lock
os.system("gnome-screensaver-command --lock")

#Close the listener when we are done
hookman.cancel()

