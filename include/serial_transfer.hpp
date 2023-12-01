#ifndef SPI_TRANSFER_ROBOT_H
#define SPI_TRANSFER_ROBOT_H


#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <SerialTransfer.h>
#include "datatypes.h"



#define SERIAL_TRANSFER_RATE 10







void SerialTransfer_setup();
void SerialTransfer_loop();




#endif