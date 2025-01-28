#include "commands/stop_joint.hpp"


extern Joint* joint[7];

StopJoint::StopJoint(uint8_t jointIndex) : jointIndex(jointIndex) {}

void StopJoint::start() {
    joint[jointIndex]->setSpeed(0, DIR_OFF);
}

bool StopJoint::run() {
    return true; // Completes immediately
}