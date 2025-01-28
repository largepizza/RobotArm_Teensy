#ifndef WAIT_MS_HPP
#define WAIT_MS_HPP

#include "commands/command.hpp"

class WaitMs : public Command {
public:
    WaitMs(uint32_t durationMs);
    void start() override;
    bool run() override;
private:
    uint32_t durationMs;
    uint32_t startTime;
};

#endif // WAIT_MS_HPP