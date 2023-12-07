#pragma once

#include <Arduino.h>

enum axisDirection_t {
    DIR_OFF,
    DIR_PLUS,
    DIR_MINUS
};



struct commandMSGStruct {
  uint32_t t_msg;
  uint8_t axisSpeeds[8];
  uint8_t axisDir[8];
} __attribute__((packed));


struct dataMSGStruct {
  int encPos[7];


} __attribute__((packed));