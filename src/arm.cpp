///////////////////////////////////////////////////////////////////////////////
/*                                                                           */
/*                                 Arm                                       */
/*                                v0.1                                       */
///////////////////////////////////////////////////////////////////////////////
/*

-Nicodemus Phaklides

Description: Provides general global variables and functions for the robotic arm
             

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
#include "arm.h"
#include <Servo.h>
#include <Encoder.h>


void Arm::init() {

    pinMode(PIN_CS_ESP, INPUT);
    pinMode(PIN_MISO_ESP, OUTPUT);
    pinMode(PIN_TRANS_SW, INPUT);
    pinMode(PIN_AXIS_1_A, INPUT);
    pinMode(PIN_AXIS_1_B, INPUT);
    pinMode(PIN_AXIS_2_A, INPUT);
    pinMode(PIN_AXIS_2_B, INPUT);
    pinMode(PIN_AXIS_3_A, INPUT);
    pinMode(PIN_AXIS_3_B, INPUT);
    pinMode(PIN_FAN_PWM, OUTPUT);
    pinMode(PIN_AXIS_4_A, INPUT);
    pinMode(PIN_AXIS_4_B, INPUT);
    pinMode(PIN_AXIS_5_A, INPUT);
    pinMode(PIN_AXIS_4_PWM, OUTPUT);
    pinMode(PIN_AXIS_5_PWM, OUTPUT);
    pinMode(PIN_GRIP_PWM, OUTPUT);
    pinMode(PIN_AXIS_4_DIR, OUTPUT);
    pinMode(PIN_AXIS_4_SW, INPUT);
    pinMode(PIN_TRANS_PWM, OUTPUT);
    pinMode(PIN_AXIS_5_DIR, OUTPUT);
    pinMode(PIN_AXIS_5_SW, INPUT);
    pinMode(PIN_GRIP_DIR, OUTPUT);
    pinMode(PIN_GRIP_SW, INPUT);
    pinMode(PIN_TRANS_DIR, OUTPUT);
    pinMode(PIN_AXIS_5_B, INPUT);
    pinMode(PIN_GRIP_A, INPUT);
    pinMode(PIN_MOSI_ESP, INPUT);
    pinMode(PIN_SCK_ESP, INPUT);
    pinMode(PIN_GRIP_B, INPUT);
    pinMode(PIN_TRANS_A, INPUT);
    pinMode(PIN_TRANS_B, INPUT);
    pinMode(PIN_AXIS_3_SW, INPUT);
    pinMode(PIN_LDO_PWR, OUTPUT);
    pinMode(PIN_AXIS_1_PWM, OUTPUT);
    pinMode(PIN_AXIS_1_DIR, OUTPUT);
    pinMode(PIN_AXIS_1_SW, INPUT);
    pinMode(PIN_AXIS_2_PWM, OUTPUT);
    pinMode(PIN_AXIS_3_PWM, OUTPUT);
    pinMode(PIN_AXIS_2_DIR, OUTPUT);
    pinMode(PIN_AXIS_2_SW, INPUT);
    pinMode(PIN_AXIS_3_DIR, OUTPUT);
    pinMode(PIN_TEMP, INPUT);

}

