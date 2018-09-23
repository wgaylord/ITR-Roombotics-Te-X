import pygame
import serial
import time #These are the required libraries (make sure they are installed)

def sendPacket(byte): #user defines packet
    packet = [byte] #now we will send this packet over to the arduino

    for i in packet: #probably a better way to do this
        elements = [i]
        #print( bytes(elements))
        ser.write(bytes(elements)) #sends packets over xbee
    time.sleep(.005); #wait a bit between sending

    return;

ser = serial.Serial('COM4', 57600, timeout=1) #this is the port for your xbee


pygame.joystick.init() 
joysticks = [pygame.joystick.Joystick(x) for x in range(pygame.joystick.get_count())] #pygame will find any number of joysticks present on your computer


pygame.init()
pygame.joystick.init()
done = False
Xaxis = 0
Yaxis = 0
button = []

for i in range(12):#create an array to put button values in
    button.append(0)
    
    
joystick = pygame.joystick.Joystick(0)
joystick.init()


        
while done==False:
    for event in pygame.event.get(): #whenever we quit pygame pygame will end
        if event.type == pygame.QUIT:
            done=True

  

    Xaxis = int(round(joystick.get_axis(0) * 15 + 15)) #this should be the "drone" setup for X and Y axes.  The last joystick found is the primary
    Yaxis = int(round(joystick.get_axis(3)* 15 + 15))

        #The joystick axis are indexed at 0, so Left X = 0, Left Y = 1, Right X = 2, Right Y = 3 and so on if you have more

        #print("X axis = " + str(Xaxis) + " Y axis = " + str(Yaxis))
    ser.write([chr(Xaxis),chr(Yaxis)])

    time.sleep(0.07)
    #delay is needed for accuracy on arduino 
        #print ser.readline()
       



