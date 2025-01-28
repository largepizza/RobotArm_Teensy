#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <memory>
#include <Arduino.h>

class Command {
public:
    virtual ~Command() = default;
    virtual void start() = 0;
    virtual bool run() = 0; // Returns true when command completes
};

using CommandPtr = std::shared_ptr<Command>;

#endif // COMMAND_HPP