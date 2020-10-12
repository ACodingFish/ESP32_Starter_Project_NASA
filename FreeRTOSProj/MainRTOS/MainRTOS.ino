#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif

#include "WiFiTask.h"

void TaskAnalogRead( void *pvParameters );

// the setup function runs once when you press reset or power the board
void setup() {
  
  // initialize serial communication at 115200 bits per second:
  Serial.begin(115200);
  
  // Now set up two tasks to run independently.
 /* xTaskCreatePinnedToCore(
    TaskBlink
    ,  "TaskBlink"   // A name just for humans
    ,  1024  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL 
    ,  ARDUINO_RUNNING_CORE); */

  xTaskCreatePinnedToCore(
    WiFiTask
    ,  "WiFi"
    ,  4096  // Stack size
    ,  NULL
    ,  3  // Priority
    ,  NULL 
    ,  ARDUINO_RUNNING_CORE);

  xTaskCreatePinnedToCore(
    WiFiSendTask
    ,  "WiFiSend"
    ,  4096  // Stack size
    ,  NULL
    ,  1  // Priority
    ,  NULL 
    ,  ARDUINO_RUNNING_CORE);

    
  xTaskCreatePinnedToCore(
    WiFiReadTask
    ,  "WiFiRead"
    ,  4096  // Stack size
    ,  NULL
    ,  1  // Priority
    ,  NULL 
    ,  ARDUINO_RUNNING_CORE);

  // Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started.
}

void loop()
{
  // Empty. Things are done in Tasks.
}

/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/


/*void TaskAnalogRead(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
  while(1)
  {
    int val = analogRead(34); // reads pin 34
    vTaskDelay(100);
  }

  }
}*/
