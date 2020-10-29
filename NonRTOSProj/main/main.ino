#include "WiFiTask.h"
void setup() 
  {
    Serial.begin (9600);
    WiFiTask();
  }

void loop() 
  {
    WiFiSendTask();
    WiFiReadTask();
  }
