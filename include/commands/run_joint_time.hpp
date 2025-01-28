#ifndef RUN_JOINT_TIME_HPP
#define RUN_JOINT_TIME_HPP

#include "commands/command.hpp"
#include "arm.hpp"

class RunJointTime : public Command {
public:
    RunJointTime(uint8_t jointIndex, int16_t signedSpeed, uint32_t durationMs);
    void start() override;
    bool run() override;

private:
    uint8_t jointIndex;
    uint8_t speed;
    uint8_t dir;
    uint32_t durationMs;
    uint32_t startTime;
};

#endif // RUN_JOINT_TIME_HPP