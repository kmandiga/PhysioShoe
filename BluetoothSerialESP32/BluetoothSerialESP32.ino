//Sets up the packet for the ESP Module to transfer data
//Need to test the communication

#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

int packetSize = 61;
uint8_t serialPacket[61];

void setup() {
  SerialBT.begin("PhysioShoeRS"); //Device Name RS = Right Shoe
  setupPacket();

}

void loop() {
  // put your main code here, to run repeatedly:
  //send packet
  if(SerialBT.available() > 0)
  {
    Serial.println(SerialBT.read());
  }

}
void setupPacket() {//formats the packet that will be transferred via bluetooth
  for (int i = 0; i < packetSize; i++)
  {
    if (i == 0) {
      serialPacket[i] = '$';
    }
    else if (i == 1)
    {
      serialPacket[i] = 0x02;
    }
    else if (i == packetSize - 2)
    {
      serialPacket[i] = '\r';
    }
    else if (i == packetSize - 1)
    {
      serialPacket[i] = '\n';
    }
    else
    {
      serialPacket[i] = 0;
    }
  }
}
