#ifndef CONTROL_HPP
#define CONTROL_HPP


#include <Arduino.h>
#include "datatypes.h"
#include "arm.hpp"
#include "scheduler.hpp"
#include "serial_transfer.hpp"
#include <PID_v1.h>

extern controlStatus_t controlStatus;


void control_init();
void control_loop();

void joint_controller();
void joint_pid();


#endif