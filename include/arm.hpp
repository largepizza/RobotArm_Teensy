#ifndef ARM_H
#define ARM_H



///////////////////////////////////////////////////////////////////////////////
/*                                                                           */
/*                              INCLUDES                                     */
/*                                                                           */
///////////////////////////////////////////////////////////////////////////////

#include <Arduino.h>
#include <Servo.h>
#include <Encoder.h>
#include "datatypes.h"

///////////////////////////////////////////////////////////////////////////////
/*                                                                           */
/*                              PINOUT                                       */
/*                                                                           */
///////////////////////////////////////////////////////////////////////////////

#define PIN_CS_ESP 0
#define PIN_MISO_ESP 1
#define PIN_TRANS_SW 2
#define PIN_AXIS_1_A 3
#define PIN_AXIS_1_B 4
#define PIN_AXIS_2_A 5
#define PIN_AXIS_2_B 6
#define PIN_AXIS_3_A 7
#define PIN_AXIS_3_B 8
#define PIN_FAN_PWM 9
#define PIN_AXIS_4_A 10
#define PIN_AXIS_4_B 11
#define PIN_AXIS_5_A 12
#define PIN_AXIS_4_PWM 13
#define PIN_AXIS_5_PWM 14
#define PIN_GRIP_PWM 15
#define PIN_AXIS_4_DIR 16
#define PIN_AXIS_4_SW 17
#define PIN_TRANS_PWM 18
#define PIN_AXIS_5_DIR 19
#define PIN_AXIS_5_SW 20
#define PIN_GRIP_DIR 21
#define PIN_GRIP_SW 22
#define PIN_TRANS_DIR 23
#define PIN_AXIS_5_B 24
#define PIN_GRIP_A 25
#define PIN_MOSI_ESP 26
#define PIN_SCK_ESP 27
#define PIN_GRIP_B 28
#define PIN_TRANS_A 29
#define PIN_TRANS_B 30
#define PIN_AXIS_3_SW 31
#define PIN_LDO_PWR 32
#define PIN_AXIS_1_PWM 33
#define PIN_AXIS_1_DIR 34
#define PIN_AXIS_1_SW 35
#define PIN_AXIS_2_PWM 36
#define PIN_AXIS_3_PWM 37
#define PIN_AXIS_2_DIR 38
#define PIN_AXIS_2_SW 39
#define PIN_AXIS_3_DIR 40
#define PIN_TEMP 41

#define ENCODER_USE_INTERRUPTS


class Acuator {
public:
    // Constructor for actuators with encoder
    Acuator(int dir_pin, int pwm_pin, int enc_a_pin, int enc_b_pin, int sw_pin = -1)
        : dir_pin_(dir_pin), pwm_pin_(pwm_pin), sw_pin_(sw_pin), enc_a_pin_(enc_a_pin), enc_b_pin_(enc_b_pin), Enc(enc_a_pin_, enc_b_pin_) {

        if (dir_pin_ != -1) {
            pinMode(dir_pin_, OUTPUT);
        }

        pinMode(pwm_pin_, OUTPUT);
        if (sw_pin_ != -1) {
            pinMode(sw_pin_, OUTPUT);
        }
    }

    // Constructor for actuators without encoder
    Acuator(int dir_pin, int pwm_pin, int sw_pin = -1)
        : dir_pin_(dir_pin), pwm_pin_(pwm_pin), sw_pin_(sw_pin), enc_a_pin_(-1), enc_b_pin_(-1), Enc(-1,-1) {

        if (dir_pin_ != -1) {
            pinMode(dir_pin_, OUTPUT);
        }

        pinMode(pwm_pin_, OUTPUT);
        if (sw_pin_ != -1) {
            pinMode(sw_pin_, OUTPUT);
        }
    }

    Encoder Enc;

    void runMotor(axisDirection_t dir, uint8_t speed);

private:
    int dir_pin_;
    int pwm_pin_;
    int sw_pin_;
    int enc_a_pin_;
    int enc_b_pin_;
};




void arm_init();

axisDirection_t getOppositeDir(axisDirection_t dir);
float dirToFloat(axisDirection_t dir);
axisDirection_t floatToDir(float val);




#endif