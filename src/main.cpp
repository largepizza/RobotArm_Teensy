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

extern cmd_t command;
extern char cmd_buffer[BUFFER_SIZE];
extern cmdRecieveStatus_t cmdRecieveStatus;
extern dataMSGStruct data;
DynamicJsonDocument dataDoc(BUFFER_SIZE);


extern Joint* joint[7];
extern Actuator* axis[7];


uint32_t t_lastPrint;
bool statusLED = false;


///////////////////////////////////////////////////////////////////////////////
/*                                                                           */
/*                              SETUP                                        */
/*                                                                           */
///////////////////////////////////////////////////////////////////////////////
void setup() {

  arm_init();
  Serial.begin(115200);
  SerialTransfer_setup();

  cmdRecieveStatus = CMD_RECIEVE_NONE;
  digitalWrite(PIN_LDO_PWR, HIGH);

  //while(micros()%1000000 != 0);
}


///////////////////////////////////////////////////////////////////////////////
/*                                                                           */
/*                              LOOP                                         */
/*                                                                           */
///////////////////////////////////////////////////////////////////////////////
void loop() {
  
   SerialTransfer_loop();

 


  
  if (cmdRecieveStatus == CMD_RECIEVED) {
    cmdRecieveStatus = CMD_RECIEVE_NONE;
    deserializeJson(dataDoc,cmd_buffer);
    //serializeJson(dataDoc,Serial);
    //Serial.println();

    cmdType_t cmd_type = (cmdType_t)(uint8_t)dataDoc["cmd"];

    switch (cmd_type) {
      case CMD_RUN_MOTOR:
        joint[((uint8_t)dataDoc["axis"])-1]->setSpeed(((uint16_t)dataDoc["speed"]*255)/100, dataDoc["direction"]);
        //Serial.print("GOING");
        break;
      default:
        break;

    }

    // Serial.print("CMD: ");
    // Serial.print(command.cmd);
    // Serial.print(" DATA: ");
    // serializeJson(dataDoc, Serial);

  }
  
  

  

  for (uint8_t i = 0; i < 7; i++) {
    joint[i]->update();
    data.encPos[i] = joint[i]->getEncPos();

  }

  if (millis() - t_lastPrint > 100) {
    t_lastPrint = millis();
    statusLED = !statusLED;
     digitalWrite(PIN_LDO_PWR, statusLED);
    for (uint8_t i = 0; i < 7; i++) {
      Serial.print("A");
      Serial.print(i+1);
      Serial.print(": ");
      Serial.print(joint[i]->getEncPos());
      Serial.print(" - ");
      Serial.print(digitalRead(joint[i]->sw_pin_));

      Serial.print(" | ");
    }
    Serial.println();
  }



}