#include "commands/stop_joints.hpp"


extern Joint* joint[7];

void StopJoints::start() {
    for(int i = 0; i < 7; i++) {
        joint[i]->setSpeed(0, DIR_OFF);
    }
}

bool StopJoints::run() {
    return true; // Completes immediately
}