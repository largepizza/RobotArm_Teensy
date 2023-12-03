///////////////////////////////////////////////////////////////////////////////
/*                                                                           */
/*                        Robot Arm Teensy Software                          */
/*                               v0.1                                        */
///////////////////////////////////////////////////////////////////////////////
/*

-Nicodemus Phaklides

Description: Controller for Scorbot ER-V robot arm using a Teensy 4.1 as an SPI subscriber



Changelog 

v0.1:
- Initial release

*/
///////////////////////////////////////////////////////////////////////////////
/*                                                                           */
/*                              INCLUDES                                     */
/*                                                                           */
///////////////////////////////////////////////////////////////////////////////
#include <Arduino.h>
#include <Servo.h>                             

#include "datatypes.h"
#include "arm.hpp" //Includes pinout definitions, basic commands
#include "serial_transfer.hpp"

///////////////////////////////////////////////////////////////////////////////
/*                                                                           */
/*                              GLOBALS                                      */
/*                                                                           */
///////////////////////////////////////////////////////////////////////////////

extern commandMSGStruct command;
extern Joint* joint[7];
extern Actuator* axis[7];


uint32_t t_lastPrint;


///////////////////////////////////////////////////////////////////////////////
/*                                                                           */
/*                              SETUP                                        */
/*                                                                           */
///////////////////////////////////////////////////////////////////////////////
void setup() {

  arm_init();
  Serial.begin(115200);
  SerialTransfer_setup();




  while(micros()%1000000 != 0);
}


///////////////////////////////////////////////////////////////////////////////
/*                                                                           */
/*                              LOOP                                         */
/*                                                                           */
///////////////////////////////////////////////////////////////////////////////
void loop() {
  
  SerialTransfer_loop();

  digitalWrite(PIN_LDO_PWR, HIGH);


  
  
  

  

  
  for (uint8_t i = 0; i < 7; i++) {
    joint[i]->setSpeed(command.axisSpeeds[i], command.axisDir[i]);
    

  }
  

  for (uint8_t i = 0; i < 7; i++) {
    joint[i]->update();

  }

  if (millis() - t_lastPrint > 100) {
    t_lastPrint = millis();
    for (uint8_t i = 0; i < 7; i++) {
      Serial.print("A");
      Serial.print(i+1);
      Serial.print(": ");
      Serial.print(joint[i]->getEncPos());
      Serial.print(" - ");
      Serial.print(digitalRead(axis[i]->sw_pin_));

      Serial.print(" | ");
    }
    Serial.println();
  }



}