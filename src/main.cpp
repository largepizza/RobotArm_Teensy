///////////////////////////////////////////////////////////////////////////////
/*                                                                           */
/*                        Robot Arm Teensy Software                          */
/*                               v0.1                                        */
///////////////////////////////////////////////////////////////////////////////
/*

-Nicodemus Phaklides

Description: Controller for Scorbot ER-V robot arm using a Teensy 4.1 as an Serial subscriber



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
#include <ArduinoJson.h>

///////////////////////////////////////////////////////////////////////////////
/*                                                                           */
/*                              GLOBALS                                      */
/*                                                                           */
///////////////////////////////////////////////////////////////////////////////

extern char cmd_buffer[BUFFER_SIZE];







uint32_t t_lastPrint;
bool statusLED = false;


///////////////////////////////////////////////////////////////////////////////
/*                                                                           */
/*                              SETUP                                        */
/*                                                                           */
///////////////////////////////////////////////////////////////////////////////
void setup() {

  arm_init();

  SerialTransfer_setup();


  digitalWrite(PIN_DISABLE, LOW);

  //while(micros()%1000000 != 0);
}


///////////////////////////////////////////////////////////////////////////////
/*                                                                           */
/*                              LOOP                                         */
/*                                                                           */
///////////////////////////////////////////////////////////////////////////////
void loop() {
  
   SerialTransfer_loop();

 
  // Joint control
  // Joint 0 - YAW
  if (abs(rxData.controller_axis[0]) > 0.2f ) {
    joint[0]->setSpeed(abs(rxData.controller_axis[0]) * 255.0f, floatToDir(rxData.controller_axis[0]));
  }
  else {
    joint[0]->setSpeed(0, DIR_OFF);
  }
  // Joint 1 - SHOULDER
  if (abs(rxData.controller_axis[1]) > 0.2f ) {
    joint[1]->setSpeed(abs(rxData.controller_axis[1]) * 255.0f,floatToDir(rxData.controller_axis[1]));
  }
  else {
    joint[1]->setSpeed(0, DIR_OFF);
  }
  // Joint 2 - ELBOW
  if (abs(rxData.controller_axis[3]) > 0.2f ) {
    joint[2]->setSpeed(abs(rxData.controller_axis[3]) * 255.0f,floatToDir(rxData.controller_axis[3]));
  }
  else {
    joint[2]->setSpeed(0, DIR_OFF);
  }
  // Joint 3 - WRIST
  if (abs(rxData.controller_axis[2]) > 0.2f ) {
    joint[3]->setSpeed(abs(rxData.controller_axis[2]) * 255.0f,floatToDir(rxData.controller_axis[2]));
  }
  else {
    joint[3]->setSpeed(0, DIR_OFF);
  }
  // Joint 4 - WRIST ROTATION
  if (rxData.controller_buttons[5] > 0) {
    joint[4]->setSpeed(100, DIR_PLUS);
  }
  else if (rxData.controller_buttons[4] > 0) {
    joint[4]->setSpeed(100, DIR_MINUS);
  }
  else {
    joint[4]->setSpeed(0, DIR_OFF);
  }
  // Joint 5 - GRIPPER
  if (rxData.controller_buttons[0] > 0) {
    joint[5]->setSpeed(100, DIR_PLUS);
  }
  else if (rxData.controller_buttons[1] > 0) {
    joint[5]->setSpeed(100, DIR_MINUS);
  }
  else {
    joint[5]->setSpeed(0, DIR_OFF);
  }
  // Joint 6 - TRANSLATION
  float transControl = (rxData.controller_axis[4]+1.0f)/2.0f - (rxData.controller_axis[5]+1.0f)/2.0f;
  if (abs(transControl) > 0.2f ) {
    joint[6]->setSpeed(abs(transControl) * 255.0, floatToDir(transControl));
  }
  else {
    joint[6]->setSpeed(0, DIR_OFF);
  }


  

  

  

  for (uint8_t i = 0; i < 7; i++) {
    joint[i]->update();

  }




}