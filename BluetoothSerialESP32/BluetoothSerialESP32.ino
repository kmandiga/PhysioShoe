//Sets up the packet for the ESP Module to transfer data
//Need to test the communication

#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

int packetSize = 61;
uint8_t serialPacket[61];
uint8_t command[20] = {' ', ' ', ' ', ' ', ' ',
                    ' ', ' ', ' ', ' ', ' ',
                    ' ', ' ', ' ', ' ', ' ',
                    ' ', ' ', ' ', ' ', '\0'
                   };
int numBytes = 0;
bool tempFlag = false;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("PhysioShoe"); //Device Name LS = Left Shoe
  setupPacket();

}

void loop() {

  recieveData();
  delay(1000);
  if(tempFlag)
  {
    sendData();
  }


}
void recieveData()
{
    /*
   * Timing is super important for properly recieving
   * all data. If too little time is given, data sent
   * gets split up. If too much time is given, data is
   * pooled together. (if 5 bytes are sent multiple 
   * times to quickly and delay is too large
   * it might store 10 bytes)
   */
    numBytes = SerialBT.available();
    if (numBytes <= 20 && numBytes > 0)
    {
      for (int i = 0; i < numBytes; i++)
      {
        command[i] = SerialBT.read();
      }
      for (int i = 18; i >= numBytes; i--)
      {
        command[i] = ' ';
      }
      Serial.println((char*) command);
      numBytes = 0;
      tempFlag = true;
    }
}
void sendData()
{
  SerialBT.write(command, 20);
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
