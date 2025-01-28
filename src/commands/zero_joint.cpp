#include "commands/zero_joint.hpp"



ZeroJoint::ZeroJoint(uint8_t jointIndex)
    : jointIndex(jointIndex) {
}

void ZeroJoint::start() {
    
}

bool ZeroJoint::run() {
    joint[jointIndex]->zero();
    return true;
}

