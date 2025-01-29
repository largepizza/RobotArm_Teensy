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
#include "control.hpp"

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

  control_init();

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
  

  for (uint8_t i = 0; i < 7; i++) {
    joint[i]->update();

  }

  getSensors();
  control_loop();
  SerialTransfer_loop();




}