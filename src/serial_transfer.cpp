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

      txData.cmdType = CMD_DATA_OUT;

      for (uint8_t i = 0; i < 6; i++) {
        //Pack encoder data
        txData.encoders[i] = joint[i]->getEncPos();
      
        //Pack controller data
        txData.controller_axis[i] = rxData.controller_axis[i];

        //Pack angles
        txData.angles[i] = (float)joint[i]->jointAngle;

        //Pack limit switches
        txData.limit_switches[i] = (uint8_t)joint[i]->getLimit();
      
      }

      //Pack current
      txData.current = inputCurrent;

      //Pack temp
      txData.temp = temp;

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