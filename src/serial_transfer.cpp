#include "serial_transfer.hpp"




cmd_t command;
cmdRecieveStatus_t cmdRecieveStatus;

dataMSGStruct data;

SerialTransfer myTransfer;
uint32_t t_lastTransfer;

char cmd_buffer[BUFFER_SIZE];

void SerialTransfer_setup() {

    Serial1.begin(115200);
    myTransfer.begin(Serial1);
    
    
}

void SerialTransfer_loop() {

  if (millis() - t_lastTransfer >= SERIAL_TRANSFER_RATE) {
      t_lastTransfer = millis();


      myTransfer.sendDatum(data);
  }
  else {
    if(myTransfer.available())
  {
    
    

      uint16_t recSize = 0;

      //recSize = myTransfer.rxObj(command, recSize);
      recSize = myTransfer.rxObj(cmd_buffer, recSize);

      Serial.println(cmd_buffer);
      
      cmdRecieveStatus = CMD_RECIEVED;
      



    /*
    Serial.print("T: ");
    Serial.print(command.t_msg);
    Serial.print(" | ");
    for (uint8_t i = 0; i < 8; i++) {
      if (command.axisDir[i] == DIR_MINUS) {
        Serial.print("-");
      }
      else if (command.axisDir[i] == DIR_OFF) {
        Serial.print("^");
      }
      else {
        Serial.print("+");
      }
      Serial.print(command.axisSpeeds[i]);
      Serial.print(", ");
    }
    Serial.println("");
    */
   digitalWriteFast(LED_BUILTIN, HIGH);
  }
  else {
    digitalWriteFast(LED_BUILTIN, LOW);
  }
  }
  
 
}