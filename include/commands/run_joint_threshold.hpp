#ifndef RUN_JOINT_THRESHOLD_HPP
#define RUN_JOINT_THRESHOLD_HPP

#include "commands/command.hpp"
#include "arm.hpp"

class RunJointThreshold : public Command {
public:
    RunJointThreshold(uint8_t jointIndex, int16_t signedSpeed, int32_t threshold);
    void start() override;
    bool run() override;

private:
    uint8_t jointIndex;
    uint8_t speed;
    uint8_t dir;
    int32_t threshold;
    int32_t lastPos;
    uint32_t lastTime;
};

#endif // RUN_JOINT_THRESHOLD_HPP