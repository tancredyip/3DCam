//
// begin license header
//
// This file is part of Pixy CMUcam5 or "Pixy" for short
//
// All Pixy source code is provided under the terms of the
// GNU General Public License v2 (http://www.gnu.org/licenses/gpl-2.0.html).
// Those wishing to use Pixy source code, software and/or
// technologies under different licensing terms should contact us at
// cmucam@cs.cmu.edu. Such licensing terms are available for
// all portions of the Pixy codebase presented here.
//
// end license header
//
// This sketch is a good place to start if you're just getting started with 
// Pixy and Arduino.  This program simply prints the detected object blocks 
// (including color codes) through the serial console.  It uses the Arduino's 
// ICSP port.  For more information go here:
//
// http://cmucam.org/projects/cmucam5/wiki/Hooking_up_Pixy_to_a_Microcontroller_(like_an_Arduino)
//
// It prints the detected blocks once per second because printing all of the 
// blocks for all 50 frames per second would overwhelm the Arduino's serial port.
//
   
#include <SPI.h>  
#include <Pixy.h>

// This is the main Pixy object 
Pixy pixy;
int upper;
int lower;
int p;
int w;
int lupper;
int llower;
int check;
int ledPin = 8;

void setup()
{
  Serial.begin(9600);
  Serial.print("Starting...\n");

  pixy.init();
  uint16_t blocks;
  
  p = pixy.blocks[0].x;
  w = pixy.blocks[0].width;
  upper = p+w/2;
  lower = p-w/2;

  pinMode(ledPin,OUTPUT);

}

void loop()
{ 
  static int i = 0;
  int j;
  
  uint16_t blocks;
  char buf[32]; 
  
  // grab blocks!

  p = pixy.blocks[0].x;
  w = pixy.blocks[0].width; 
  lupper = p+w/2;
  llower = p-w/2;
  check = 0;
  blocks = pixy.getBlocks();

  //sprintf(buf, "Hi");
  
  // If there are detect blocks, print them!
  if (blocks)
  {
    i++;
    
    // do this (print) every 50 frames because printing every
    // frame would bog down the Arduino
    if (i%50==0)
    {
      
      if ((abs(lupper - upper) > 7) || (abs(llower - lower) > 7))
      {
        Serial.println("The object has left the boundaries: " );
        Serial.print("Upper is: ");
        Serial.print(upper);
        Serial.print("  Lower is: ");
        Serial.print(lower);
        Serial.print("  Live Upper is: ");
        Serial.print(lupper);
        Serial.print("  Live Lower is: ");
        Serial.println(llower);
        digitalWrite(ledPin, HIGH);
        check = 1;
      }
      
    
    }
    
  }  
}

