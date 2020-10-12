/**
 * Author: Jon
 */
#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif

#include "WiFiTask.h"

void setup() {
  
  // init serial
  Serial.begin(115200);
  

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

}

void loop()
{
  // Empty. Use Tasks only.
}
