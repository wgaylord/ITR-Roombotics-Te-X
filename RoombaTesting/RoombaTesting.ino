#include <SoftwareSerial.h>

SoftwareSerial roombaSerial(10,11);

int incomingByte = 0;

void setup(){
   Serial.begin(9600);
  roombaSerial.begin(57600); //this baud rate is specified in the documentation
  roombaSerial.write(128); //Initialization step 1
  delay(50);
  roombaSerial.write(130); //step 2
  
  delay(50);
  roombaSerial.write(132);
  
  roombaSerial.write(139); //LEDS
  roombaSerial.print(0);
  roombaSerial.print(1);
  roombaSerial.write(255);
  
  delay(20000);


  
 
}
void loop()
{
  drive(500, 32768);
  delay(1000);
  drive(500, 1);
  delay(300);

 
}


void drive(int velocity, int radius){
  //I put this if(...) sanity check in here because I have honestly no idea what the roomba would do
  //outside of this range of values. It's not even documented :-(
 
    roombaSerial.write(137); //DRIVE
    roombaSerial.write((velocity>>8 & 0xFF)); //Split 16-bit velocity into 2 bytes and send
    roombaSerial.write((velocity & 0xFF));
    roombaSerial.write((radius>>8 & 0xFF));
    roombaSerial.write((radius & 0xFF));
  
}
