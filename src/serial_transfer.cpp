#include "serial_transfer.hpp"




commandMSGStruct command;
dataMSGStruct data;

SerialTransfer myTransfer;
uint32_t t_lastTransfer;


void SerialTransfer_setup() {

    Serial1.begin(115200);
    myTransfer.begin(Serial1, false);
    
    
}

void SerialTransfer_loop() {

  if (millis() - t_lastTransfer >= SERIAL_TRANSFER_RATE) {
      t_lastTransfer = millis();


      myTransfer.sendDatum(data);
  }
  
 if(myTransfer.available())
  {
    digitalWriteFast(LED_BUILTIN, HIGH);
    myTransfer.rxObj(command);

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
  }
  else {
    digitalWriteFast(LED_BUILTIN, LOW);
  }
}