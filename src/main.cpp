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
extern Acuator* axis[8];

Encoder axis1Enc(PIN_AXIS_1_A, PIN_AXIS_1_B);

///////////////////////////////////////////////////////////////////////////////
/*                                                                           */
/*                              SETUP                                        */
/*                                                                           */
///////////////////////////////////////////////////////////////////////////////
void setup() {

  arm_init();
  Serial.begin(115200);
  SerialTransfer_setup();

  axis1Enc.write(0);


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


  
  
  Serial.println(axis1Enc.read());

  

  axis[0]->runMotor(command.axisDir[0],command.axisSpeeds[0]);


  axis[1]->runMotor(command.axisDir[1],command.axisSpeeds[1]);
  axis[2]->runMotor(command.axisDir[2],command.axisSpeeds[2]);

  if (command.axisDir[3] != DIR_OFF) {
    axis[3]->runMotor(command.axisDir[3],command.axisSpeeds[3]);
    axis[4]->runMotor(getOppositeDir(command.axisDir[3]),command.axisSpeeds[3]);
  }
  else if (command.axisDir[4] != DIR_OFF) {
    axis[3]->runMotor(command.axisDir[4],command.axisSpeeds[4]);
    axis[4]->runMotor(command.axisDir[4],command.axisSpeeds[4]);
  }
  else {
    axis[3]->runMotor(DIR_OFF,0);
    axis[4]->runMotor(DIR_OFF,0);
  }

  axis[5]->runMotor(getOppositeDir(command.axisDir[5]), command.axisSpeeds[5]);

  axis[6]->runMotor(getOppositeDir(command.axisDir[6]), command.axisSpeeds[6]);

  analogWrite(PIN_FAN_PWM, command.axisSpeeds[7]);

}



