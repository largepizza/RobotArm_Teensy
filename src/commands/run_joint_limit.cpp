#include "commands/run_joint_limit.hpp"


extern Joint* joint[7];

RunJointLimit::RunJointLimit(uint8_t jointIndex, int16_t signedSpeed) 
    : jointIndex(jointIndex) {
    if(signedSpeed > 0) {
        dir = DIR_PLUS;
        speed = signedSpeed;
    } else {
        dir = DIR_MINUS;
        speed = -signedSpeed;
    }
}

void RunJointLimit::start() {
    joint[jointIndex]->setSpeed(speed, (axisDirection_t)dir);
}

bool RunJointLimit::run() {
    if(joint[jointIndex]->getLimit()) {
        joint[jointIndex]->setSpeed(0, DIR_OFF);
        return true;
    }
    return false;
}