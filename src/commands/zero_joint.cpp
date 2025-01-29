#include "commands/zero_joint.hpp"



ZeroJoint::ZeroJoint(uint8_t jointIndex, float offset = 0)
    : jointIndex(jointIndex), offset(offset) {
}

void ZeroJoint::start() {
    
}

bool ZeroJoint::run() {
    // Use gear ratio to convert float angle offset to encoder ticks
    int enc_offset = offset * gearRatios[jointIndex];

    /// Zero joint
    joint[jointIndex]->zero(enc_offset);
    return true;
}

