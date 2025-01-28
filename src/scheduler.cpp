#include "scheduler.hpp"

// Import commands
#include "commands/command.hpp"
#include "commands/run_joint_time.hpp"

void Scheduler::add(CommandPtr cmd) {
    commandQueue.push_back(cmd);
}

void Scheduler::run() {
    if (!currentCommand && !commandQueue.empty()) {
        currentCommand = commandQueue.front();
        commandQueue.pop_front();
        currentCommand->start();
    }

    if (currentCommand && currentCommand->run()) {
        currentCommand.reset();
    }
}

void Scheduler::clear() {
    commandQueue.clear();
    currentCommand.reset();
}

bool Scheduler::isEmpty() const {
    return commandQueue.empty() && !currentCommand;
}