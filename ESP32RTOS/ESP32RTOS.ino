#define LED1 14

TaskHandle_t Task1;


void codeForTask1(void * parameter)
{
  for(;;)
  {
    Serial.print("This task runs on Core: ");
  Serial.println(xPortGetCoreID());

  Serial.println("ON");
  delay(1000);
  Serial.println("OFF");
  delay(1000);
  }
}

void setup()
{
  Serial.begin(115200);
  pinMode(LED1, OUTPUT);

  xTaskCreatePinnedToCore(
    codeForTask1,
    "Task_1",
    1000,
    NULL,
    1,
    &Task1,
    0);
}

void loop()
{
  
}

