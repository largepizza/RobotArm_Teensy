#include "serial_transfer.hpp"






rxDataStruct rxData;
txDataStruct txData;


SerialTransfer myTransfer;
uint32_t t_lastTransfer;

char cmd_buffer[BUFFER_SIZE];

void SerialTransfer_setup() {

    Serial.begin(500000);
    myTransfer.begin(Serial);
    
    
}

void SerialTransfer_loop() {

  if (millis() - t_lastTransfer >= SERIAL_TRANSFER_RATE) {
      t_lastTransfer = millis();


      //Pack encoder data
      for (uint8_t i = 0; i < 6; i++) {
        txData.encoders[i] = joint[i]->getEncPos();
      }
      //Pack controller data
      for (uint8_t i = 0; i < 6; i++) {
        txData.controller_axis[i] = rxData.controller_axis[i];
      }

      //Pack angles
      for (uint8_t i = 0; i < 6; i++) {
        txData.angles[i] = (float)joint[i]->getAngle();
      }

      uint16_t txSize = 0;
      txSize = myTransfer.txObj(txData, txSize);

      //Send data
      myTransfer.sendData(txSize, 0x01);
  }
  else {
    if(myTransfer.available())
    {
      
      

        uint16_t recSize = 0;

        recSize = myTransfer.rxObj(rxData, recSize);




    }
    
 
}
}