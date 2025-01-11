#pragma once

#include <Arduino.h>

#define BUFFER_SIZE 256

typedef enum axisDirection_t {
    DIR_OFF,
    DIR_PLUS,
    DIR_MINUS
};

typedef enum cmdType_t {
  CMD_NONE,
  CMD_RUN_MOTOR,
  CMD_ZERO,
  CMD_JOINT_SPACE
};


enum cmdSendStatus_t {
    CMD_SEND_READY,
    CMD_SEND_QUEUED,
};

enum cmdRecieveStatus_t {
  CMD_RECIEVE_NONE,
  CMD_RECIEVED
};


typedef struct __attribute__((packed)) rxDataStruct {
    float controller_axis[6];
    int32_t controller_buttons[8];
} rxDataStruct;

typedef struct __attribute__((packed)) txDataStruct {
  float controller_axis[6];
  int32_t encoders[7];
} txDataStruct;