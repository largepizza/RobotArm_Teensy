#ifndef SPI_TRANSFER_ROBOT_H
#define SPI_TRANSFER_ROBOT_H


#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <SerialTransfer.h>
#include "datatypes.h"
#include "arm.hpp"


#define SERIAL_TRANSFER_RATE 20

extern rxDataStruct rxData;
extern txDataStruct txData;





void SerialTransfer_setup();
void SerialTransfer_loop();




#endif