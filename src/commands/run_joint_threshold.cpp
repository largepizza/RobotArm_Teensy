#include "commands/run_joint_threshold.hpp"


extern Joint* joint[7];

RunJointThreshold::RunJointThreshold(uint8_t jointIndex, int16_t signedSpeed, int32_t threshold)
    : jointIndex(jointIndex), threshold(threshold) {
    if(signedSpeed > 0) {
        dir = DIR_PLUS;
        speed = signedSpeed;
    } else {
        dir = DIR_MINUS;
        speed = -signedSpeed;
    }
}

void RunJointThreshold::start() {
    lastTime = millis();
    lastPos = joint[jointIndex]->getEncPos();

    joint[jointIndex]->setSpeed(speed, (axisDirection_t)dir);
}

bool RunJointThreshold::run() {

    uint32_t currentTime = millis();

    if (currentTime - lastTime > 100) {
        
        int32_t currentPos = joint[jointIndex]->getEncPos();
        int32_t delta = abs(currentPos - lastPos);

        if (delta < threshold) {
            joint[jointIndex]->setSpeed(0, DIR_OFF);
            return true;
        }


        lastTime = currentTime;
        lastPos = currentPos;
        
    }


    
    
    return false;
}