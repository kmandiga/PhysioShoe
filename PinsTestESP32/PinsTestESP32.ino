//Analog Pin Test
/*
int pinToTest = 4;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pinToTest, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(analogRead(pinToTest));
  delay(500);
}
*/

//Digital Pin Test

int pinToTest = 16;
int val = 0;

void setup()
{
  Serial.begin(9600);

  pinMode(pinToTest, OUTPUT);

  digitalWrite(pinToTest, LOW);
}
void loop()
{
  if(Serial.available()>0)
  {
    val = Serial.read();
    switch (val)
    {
      case 'a':
      digitalWrite(pinToTest, HIGH);
      break;
      case 's':
      digitalWrite(pinToTest, LOW);
      break;
    }
  }
  delay(100);
}

