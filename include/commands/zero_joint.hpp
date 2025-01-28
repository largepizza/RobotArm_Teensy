#ifndef ZERO_JOINT_HPP
#define ZERO_JOINT_HPP

#include "commands/command.hpp"
#include "arm.hpp"

class ZeroJoint : public Command {
public:
    ZeroJoint(uint8_t jointIndex);
    void start() override;
    bool run() override;

private:

    uint8_t jointIndex;


};

#endif // ZERO_JOINT_HPP