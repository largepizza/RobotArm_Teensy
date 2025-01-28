#ifndef RUN_JOINT_LIMIT_HPP
#define RUN_JOINT_LIMIT_HPP

#include "commands/command.hpp"
#include "arm.hpp"

class RunJointLimit : public Command {
public:
    RunJointLimit(uint8_t jointIndex, int16_t signedSpeed);
    void start() override;
    bool run() override;

private:
    uint8_t jointIndex;
    uint8_t speed;
    uint8_t dir;
};

#endif // RUN_JOINT_LIMIT_HPP