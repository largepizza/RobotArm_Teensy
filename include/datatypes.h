#pragma once

#include <Arduino.h>

#define BUFFER_SIZE 256

typedef enum axisDirection_t {
    DIR_OFF,
    DIR_PLUS,
    DIR_MINUS
};

typedef enum cmdType_t : int32_t {
  CMD_DATA_IN = 0,
  CMD_DATA_OUT = 1,
  CMD_CONFIG = 2
};

typedef enum controlStatus_t {
  CONTROL_NONE,
  CONTROL_JOINT_CONTROLLER,
  CONTROL_ZERO,
  CONTROL_JOINT_PID
};


enum cmdSendStatus_t {
    CMD_SEND_READY,
    CMD_SEND_QUEUED,
};

enum cmdRecieveStatus_t {
  CMD_RECIEVE_NONE,
  CMD_RECIEVED
};

// RX and TX data structures
typedef struct __attribute__((packed)) rxDataStruct {
    int32_t cmdType;
    float controller_axis[6];
    int32_t controller_buttons[8];
    float joint_targets[7];
} rxDataStruct;

typedef struct __attribute__((packed)) txDataStruct {
  int32_t cmdType;
  float controller_axis[6];
  int32_t encoders[7];
  float angles[6];
  float current;
  float temp;
  uint8_t limit_switches[6];
} txDataStruct;

// Config data structure
typedef struct __attribute__((packed)) configDataStruct {
  int32_t cmdType;
  float joints_kp[7];
  float joints_ki[7];
  float joints_kd[7];
  

} configDataStruct;