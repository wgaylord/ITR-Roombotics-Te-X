import pygame
import serial
import time #These are the required libraries (make sure they are installed)


ser = serial.Serial('COM6', 57600, timeout=1) #this is the port for your xbee


pygame.joystick.init() 
joysticks = [pygame.joystick.Joystick(x) for x in range(pygame.joystick.get_count())] #pygame will find any number of joysticks present on your computer


pygame.init()
pygame.joystick.init()
done = False
Xaxis = 0
Yaxis = 0
button = ""


joystick = pygame.joystick.Joystick(0)
joystick.init()


        
while done==False:
    for event in pygame.event.get(): #whenever we quit pygame pygame will end
        if event.type == pygame.QUIT:
            done=True
        
    button = 0
    

    Xaxis = int(round(joystick.get_axis(0) * -15 + 15)) 
    Yaxis = int(round(joystick.get_axis(3) * -15 + 15))
    
    
    if joystick.get_button(7) == 1:
        button = 127
    if joystick.get_button(5) == 1:
        button = 64
    if joystick.get_button(2) == 1:
        button = 32
    if joystick.get_button(0) == 1:
        button = 16
    if joystick.get_button(1) == 1:
        button = 75
    print "Sent",Xaxis,Yaxis,button
    ser.write([chr(Xaxis),chr(Yaxis),chr(button)])
    try:
        print "Returned",ord(ser.read()),ord(ser.read()),ord(ser.read())
    except:
        print "Arduino Timed out. Waiting for watchdog reset"
    
       


