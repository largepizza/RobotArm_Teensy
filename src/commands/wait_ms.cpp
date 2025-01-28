#include "commands/wait_ms.hpp"

WaitMs::WaitMs(uint32_t durationMs)
    : durationMs(durationMs) {
}

void WaitMs::start() {
    startTime = millis();
}

bool WaitMs::run() {
    return (millis() - startTime) >= durationMs;
}

