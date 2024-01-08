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


struct cmd_t {
  uint8_t cmd;
  uint32_t t;
} __attribute__((packed));


struct dataMSGStruct {
  int encPos[7];
  int speed[7];


} __attribute__((packed));