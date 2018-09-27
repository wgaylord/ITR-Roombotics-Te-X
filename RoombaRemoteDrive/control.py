import pygame
import serial
import time #These are the required libraries (make sure they are installed)



ser = serial.Serial('COM4', 57600, timeout=1) #this is the port for your xbee


pygame.joystick.init() 
joysticks = [pygame.joystick.Joystick(x) for x in range(pygame.joystick.get_count())] #pygame will find any number of joysticks present on your computer


pygame.init()
pygame.joystick.init()
done = False
Active = True
Xaxis = 15
Yaxis = 15
button = []

for i in range(12):#create an array to put button values in
    button.append(0)
    
    
joystick = pygame.joystick.Joystick(0)
joystick.init()


        
while done==False:
    for event in pygame.event.get(): #whenever we quit pygame pygame will end
        if event.type == pygame.QUIT:
            done=True
        if event.type == pygame.JOYAXISMOTION: # Only update the bot if we have to.
            if event.axis == 0:
                Xaxis = int(round(event.value * 15 + 15))
            if event.axis == 3:
                Yaxis = int(round(event.value * 15 + 15))
            ser.write([chr(Xaxis),chr(Yaxis)])
        if event.type == pygame.JOYBUTTONDOWN:
            if event.button == 1:
                ser.write([Active*255,(!Active*)255])
                Active = !Active
                
                

    time.sleep(0.005)
   
       



