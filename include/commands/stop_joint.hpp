#ifndef STOP_JOINT_HPP
#define STOP_JOINT_HPP

#include "commands/command.hpp"
#include "arm.hpp"

class StopJoint : public Command {
public:
    StopJoint(uint8_t jointIndex);
    void start() override;
    bool run() override;

private:
    uint8_t jointIndex;
};

#endif // STOP_JOINT_HPP