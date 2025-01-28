#ifndef STOP_JOINTS_HPP
#define STOP_JOINTS_HPP

#include "commands/command.hpp"
#include "arm.hpp"

class StopJoints : public Command {
public:
    void start() override;
    bool run() override;
};

#endif // STOP_JOINTS_HPP