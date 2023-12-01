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
#include "arm.hpp"
#include <Servo.h>
#include <Encoder.h>



Acuator* axis[8];

// Axis
Acuator axis1(PIN_AXIS_1_DIR, PIN_AXIS_1_PWM, PIN_AXIS_1_A, PIN_AXIS_1_B, PIN_AXIS_1_SW);
Acuator axis2(PIN_AXIS_2_DIR, PIN_AXIS_2_PWM, PIN_AXIS_2_A, PIN_AXIS_2_B, PIN_AXIS_2_SW);
Acuator axis3(PIN_AXIS_3_DIR, PIN_AXIS_3_PWM, PIN_AXIS_3_A, PIN_AXIS_3_B, PIN_AXIS_3_SW);
Acuator axis4(PIN_AXIS_4_DIR, PIN_AXIS_4_PWM, PIN_AXIS_4_A, PIN_AXIS_4_B, PIN_AXIS_4_SW);
Acuator axis5(PIN_AXIS_5_DIR, PIN_AXIS_5_PWM, PIN_AXIS_5_A, PIN_AXIS_5_B, PIN_AXIS_5_SW);

// Grip
Acuator axisGrip(PIN_GRIP_DIR, PIN_GRIP_PWM, PIN_GRIP_A, PIN_GRIP_B, PIN_GRIP_SW);

// Translational Platform
Acuator axisTrans(PIN_TRANS_DIR, PIN_TRANS_PWM, PIN_TRANS_A, PIN_TRANS_B, PIN_TRANS_SW);

// Fan
//Acuator axisFan(-1, PIN_FAN_PWM);

axisDirection_t getOppositeDir(axisDirection_t dir) {
  switch (dir) {
    case DIR_PLUS:
      return DIR_MINUS;
      break;
    case DIR_MINUS:
      return DIR_PLUS;
      break;
    default:
      return DIR_OFF;
      break;
  }
}

float dirToFloat(axisDirection_t dir) {
    switch (dir) {
    case DIR_PLUS:
      return 1.0F;
      break;
    case DIR_MINUS:
      return -1.0F;
      break;
    default:
      return 0;
      break;
  }
}

axisDirection_t floatToDir(float val) {
    if (val > 0) { return DIR_PLUS;}
    else if (val < 0) {return DIR_MINUS;}
    else {return DIR_OFF;}
}

void arm_init() {

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

    


    //Axis
    axis[0] = &axis1;
    axis[1] = &axis2;
    axis[2] = &axis3;
    axis[3] = &axis4;
    axis[4] = &axis5;

    // Grip
    axis[5] = &axisGrip;

    // Translational Platform
    axis[6] = &axisTrans;

    // // Fan
    // axis[7] = &axisFan;

    

   

}

void Acuator::runMotor(axisDirection_t dir, uint8_t speed) {
    switch (dir) {
        case DIR_OFF:
            digitalWrite(dir_pin_, LOW);
            analogWrite(pwm_pin_, 0);
            break;
        case DIR_PLUS:
            digitalWrite(dir_pin_, HIGH);
            analogWrite(pwm_pin_, speed);
            break;
        case DIR_MINUS:
            digitalWrite(dir_pin_, LOW);
            analogWrite(pwm_pin_, speed);
            break;
        default:
            break;
    }

    return;
}