#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP

#include <deque>
#include <memory>

// Import commands
#include "commands/command.hpp"
#include "commands/run_joint_time.hpp"
#include "commands/stop_joint.hpp"
#include "commands/stop_joints.hpp"
#include "commands/run_joint_threshold.hpp"
#include "commands/run_joint_limit.hpp"
#include "commands/zero_joint.hpp"
#include "commands/wait_ms.hpp"


class Scheduler {
public:
    void add(CommandPtr cmd);
    void run();
    void clear();
    bool isEmpty() const;

private:
    std::deque<CommandPtr> commandQueue;
    CommandPtr currentCommand;
};

#endif // SCHEDULER_HPP