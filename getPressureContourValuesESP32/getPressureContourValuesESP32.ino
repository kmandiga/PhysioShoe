/*
   ESP32 has a 12 bit adc
   2 bytes are needed for each
   Pressure Contour value.
   This also needs switching time delay
   while multiplexing. This is for the Left Shoe.
*/

//variables for pressure contour
int analogValue;
uint8_t avLow = 0;
uint8_t avHigh = 0;

int numRows = 9;
int numCols = 3;

int digitalRowPins[9] = {32, 33, 25, 26, 27, 14, 12, 13, 16};
int digitalColPins[3] = {15, 2, 4};

uint8_t serialPacket[54];
int serialPacketSize = 54;
int serialPacketIndex = 0;

int calibrationVals[27];
int values[27];
int valuesSize = 27;

long timespent = 0;

void setup() {
  // No Setup needed for taking data from
  //pressure contour assuming packet
  //initialization is done in Bluetooth Code
  Serial.begin(9600);
  initializePins();
  initalizePacket();
  calibrateContour();
}

void loop() {
  // put your main code here, to run repeatedly:
  getPressureContourValues();
  displayContour();
  delay(200);

}
void calibrateContour()
{
  Serial.println("Calibrating");
  timespent = millis();
  for(int i = 0; i < 20; i++)
  {
    getPressureContourValues();
    for(int j = 0; j < valuesSize; j++)
    {
      calibrationVals[j] += values[j];
    }
  }
  for(int k = 0; k < valuesSize; k++)
  {
    calibrationVals[k] /= 20;
  }
  Serial.println("calibrated");
}
void getPressureContourValues() {
  /*for (int x = 0; x < numRows; x++)
    {
    pinMode(digitalRowPins[x], OUTPUT);
    digitalWrite(digitalRowPins[x], HIGH);
    for (int y = 0; y < numCols; y++)
    {
      analogValue = analogRead(y);
      avLow = lowByte(analogValue);
      avHigh = highByte(analogValue);
      serialPacket[serialPacketIndex] = avHigh;
      serialPacket[serialPacketIndex + 1] = avLow;
      serialPacketIndex += 2;
    }
    pinMode(digitalRowPins[x], INPUT);
    }
    serialPacketIndex = 0;*/
  for (int x = 0; x < numRows; x++)
  {
    pinMode(digitalRowPins[x], OUTPUT);
    digitalWrite(digitalRowPins[x], HIGH);
    for (int y = 0; y < numCols; y++)
    {
      analogValue = analogRead(digitalColPins[y]);
      values[serialPacketIndex] = analogValue - calibrationVals[serialPacketIndex];
      serialPacketIndex++;
      delay(25);
    }
    pinMode(digitalRowPins[x], INPUT);
    delay(25);
  }
  serialPacketIndex = 0;
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
    pinMode(digitalRowPins[i], OUTPUT);
    digitalWrite(digitalRowPins[i], LOW);
    pinMode(digitalRowPins[i], INPUT);
  }
}
void initalizePacket()
{
  for (int i = 0; i < serialPacketSize; i++)
  {
    serialPacket[i] = 0;
  }
  for (int i = 0; i < valuesSize; i++)
  {
    values[i] = 0;
  }
  for (int i = 0; i < valuesSize; i++)
  {
    calibrationVals[i] = 0;
  }
}
void displayContour()
{
  if (Serial.available() > 0)
  {
    int v = Serial.read();
    if ((char) v == 'r')
    {
      int index = 0;
      for (int x = 0; x < numRows; x++)
      {
        for (int y = 0; y < numCols; y++)
        {
          Serial.print(values[index]);
          if (y != 2)
          {
            Serial.print('\t');
          }
          index++;
        }
        Serial.println();
      }
      Serial.println();
    }
    v = 0;
  }
}

