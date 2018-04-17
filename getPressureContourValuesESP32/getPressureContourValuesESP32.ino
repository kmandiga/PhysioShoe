//digitalPins may need some changing for the ESP module.
//Unsure of the pinout.

//variables for pressure contour
int numRows = 9;//number of rows in array
int numCols = 3;//number of cols in array
int digitalPinsIndex = 5;//starting index of digital pins for the pressure array

int analogValue;


void setup() {
  // No Setup needed for taking data from
  //pressure contour assuming packet
  //initialization is done in Bluetooth Code
  initializePins();
}

void loop() {
  // put your main code here, to run repeatedly:
  getPressureContourValues();

}
void getPressureContourValues() {
  for (int x = 0; x < numRows; x++)
    {
    pinMode(digitalPinsIndex, OUTPUT);
    digitalWrite(digitalPinsIndex, HIGH);
    for (int y = 0; y < numCols; y++)
    {
      analogValue = analogRead(y);
      uint8_t avLow = lowByte(analogValue);
      uint8_t avHigh = highByte(analogValue);
      serialPacket[packetIndex] = avHigh;
      serialPacket[packetIndex+1] = avLow;
      packetIndex+=2;
    }
    pinMode(digitalPinsIndex, INPUT);
    digitalPinsIndex++;
    }
    packetIndex = 2;
    digitalPinsIndex = 5;
  /*for (int x = 0; x < numRows; x++)
  {
    for (int y = 0; y < numCols; y++)
    {
      uint8_t avLow = lowByte(temp);
      uint8_t avHigh = highByte(temp);
      serialPacket[packetIndex] = avHigh;
      serialPacket[packetIndex+1] = avLow;
      packetIndex+=2;
    }
    temp += 112;
  }
  packetIndex = 2;
  temp = 0;*/
}
void initializePins() {//initializes all the I/O pins for the pressure sensor array
  for (int i = 0; i < numRows; i++)
  {
    pinMode(digitalPinsIndex + i, INPUT);
  }
}
