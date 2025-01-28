#include "commands/run_joint_time.hpp"

extern Joint* joint[7];

RunJointTime::RunJointTime(uint8_t jointIndex, int16_t signedSpeed, uint32_t durationMs)
    : jointIndex(jointIndex), durationMs(durationMs) {
    if (signedSpeed > 0) {
        dir = DIR_PLUS;
        speed = signedSpeed;
    } else {
        dir = DIR_MINUS;
        speed = -signedSpeed;
    }
}

void RunJointTime::start() {
    joint[jointIndex]->setSpeed(speed, (axisDirection_t)dir);
    startTime = millis();
}

bool RunJointTime::run() {
    return (millis() - startTime) >= durationMs;
}