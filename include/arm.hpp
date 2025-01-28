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

#define PIN_TX_ESP 0
#define PIN_RX_ESP 1
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
#define PIN_CURRENT_SENSE 26
#define PIN_BUZZER 27
#define PIN_GRIP_B 28
#define PIN_TRANS_A 29
#define PIN_TRANS_B 30
#define PIN_AXIS_3_SW 31
#define PIN_DISABLE 32
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
#define ENCODER_SLOTS 20.0F

const double gearRatios[7] = {127.1, 127.1, 127.1, 65.5, 65.5, 19.5, 10.0};





class Actuator {
public:
    // Constructor for actuators with encoder
    Actuator(int dir_pin, int pwm_pin)
        : dir_pin_(dir_pin), pwm_pin_(pwm_pin) {

        if (dir_pin_ != -1) {
            pinMode(dir_pin_, OUTPUT);
        }

        pinMode(pwm_pin_, OUTPUT);


    }

    Encoder* Enc;
    bool inverted = false;

    void runMotor(axisDirection_t dir, uint8_t speed);
    int getVelocity();

    int index_;
    int dir_pin_;
    int pwm_pin_;
    
    int enc_a_pin_;
    int enc_b_pin_;

private:
    uint8_t speed_;
    axisDirection_t dir_;

};

class Joint {
    public:

        void init(uint8_t index, uint8_t sw_pin);


        void update();
        void setSpeed(uint8_t speed, axisDirection_t dir);


        uint8_t getIndex();
        int getVelocity();
        int getSpeed();
        int getEncPos();
        double getAngle();
        bool getLimit();
        void zero();
        axisDirection_t getDir();
        int sw_pin_;

        private:
            uint8_t speed_;
            axisDirection_t dir_;
            uint8_t index_;
            bool switchState_;
            double angle_;
            int encPos_;
            int encPosOffset_;
};



void arm_init();

axisDirection_t getOppositeDir(axisDirection_t dir);
float dirToFloat(axisDirection_t dir);
axisDirection_t floatToDir(float val);

extern Joint* joint[7];
extern Actuator* axis[7];
extern Encoder* encoder[7];

#endif