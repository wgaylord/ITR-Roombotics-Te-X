//Main program for Xbee Communication & Roomba Control
//Loosely based on the principals of SerialCTL written by Nash Kaminski
//By learning and experimenting with the principals of the program, future ITR members will gain a strong base of understanding
//for the SerialCTL program


#include <SoftwareSerial.h>
#include <Servo.h>
#include <avr/wdt.h>

Servo crabber;
Servo Lift;

int Xaxis = 15; //This value represents the recieved X value (0 to 30)
int Yaxis = 15; //This value represents the recieved Y value
int buttons = 0;
int crabberAngle = 90;


void setup() {  
  
  Serial.begin(57600);   //this Serial line will read data from the xbee
  Serial2.begin(57600);    //this Serial line will send commands to the roomba
  
  Serial2.write(128); //These two bytes initialize the roomba
  delay(50);
  Serial2.write(130);
  delay(50);  
  Serial2.write(132); //This sets the Roomba in 'unsafe' mode
  delay(50);
  Serial2.write(139); //LEDS
  Serial2.print(0);
  Serial2.print(1);
  Serial2.write(255);

  crabber.attach(22);
  Lift.attach(3, 1000, 2000);
  crabber.write(crabberAngle);
  watchdogSetup();

  }

void loop() {
  //The laptop-xbee-remote combination, or control station, will transmit bytes to the roomba that contain information on the state of the remote
  wdt_reset();
  if(Serial.available() >2){ //if there is new data from the control station, interpret it
    
    Xaxis = Serial.read();  //get the value
    Yaxis = Serial.read();
    buttons = Serial.read();
    
    driveRoomba(Xaxis, Yaxis, 13,17); //This method takes the current X and Y value of the remote and translates it into Roomba motion.
    handleButtons();
   
    crabber.write(crabberAngle);
    Serial.write(Xaxis);
    Serial.write(Yaxis);
    Serial.write(buttons);
    Serial.flush();
  }
  Serial2.write(132);

}

byte driveRoomba(int joyX, int joyY, int boundsLow, int boundsHigh)
{
  //This function uses input values to move the robot
  //Then sends an instruction to the robot
  
  int speed = map(joyY, 0,30, -480,480);  //The Y value acts as the power to the motors
  int radius = map(joyX,0,30, -180,180); //the X value acts as the radius for the robots turn (the further from the center of the joystick the smaller the radius)
  

  //for example to move straight, you simply move the Y axis up 
  //0,0 for the joysticks is in the top left corner

  

  
  if(joyX < boundsLow) //these functions invert the radius (remember further from center the smaller the radius so tighter turns)
  {
    radius = map(joyX,0,15,-1,-200);
  }
  if(joyX > boundsHigh)
  {
    radius = map(joyX,15,30,200,0);
  }
  
  if(joyX > boundsLow && joyX < boundsHigh) //if the stick is in the center (based on given bounds) then we want to set it to 0
  {
     radius = 32768;//this is the given 0 value for the radius, part of the documentation
  }
  if(joyY > boundsLow 
  && joyY < boundsHigh)
  {
    speed = 0;
  }
  
  
  Serial2.write(137);      //This line sends the instructions over serial
  Serial2.write((speed >> 8) & 255);
  Serial2.write((speed) & 255);
  Serial2.write((radius >> 8) & 255);
  Serial2.write((radius) & 255);

  
}

void handleButtons(){

    if((buttons == 64)){
      Lift.write(0);
      delay(20);
      
    }else{
     if(buttons == 127){
      Lift.write(180);
      delay(20);
     
    }else{
      Lift.write(90);
    }
    }
    if(buttons == 32){
      crabberAngle +=1;
    }
    if(buttons == 16){
      crabberAngle -=1;
    }
     if(buttons == 75){
       Serial2.write(128); //These two bytes initialize the roomba
  delay(50);
  Serial2.write(130);
  delay(50);  
  Serial2.write(132); //This sets the Roomba in 'unsafe' mode
  delay(50);
  Serial2.write(139); //LEDS
  Serial2.print(0);
  Serial2.print(1);
  Serial2.write(255);
    }
    
    

}


void watchdogSetup(void)
{
 cli();
 wdt_reset();
/*
 WDTCSR configuration:
 WDIE = 1: Interrupt Enable
 WDE = 1 :Reset Enable
 See table for time-out variations:
 WDP3 = 0 :For 1000ms Time-out
 WDP2 = 1 :For 1000ms Time-out
 WDP1 = 1 :For 1000ms Time-out
 WDP0 = 0 :For 1000ms Time-out
*/
// Enter Watchdog Configuration mode:
WDTCSR |= (1<<WDCE) | (1<<WDE);
// Set Watchdog settings:
 WDTCSR = (1<<WDIE) | (1<<WDE) |
(0<<WDP3) | (1<<WDP2) | (0<<WDP1) |
(0<<WDP0);

sei();
}
