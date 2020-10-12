/**
 * Author: Jon
 */
#include <WiFi.h>
#include "WiFiTask.h"

const char* ssid     = "xxxxxxxxxx";
const char* password = "xxxxxxxxxx";

String tcp_ip = "xxx.xxx.xxx.xxx";
const int tcp_port = 10000;

WiFiClient client;


void WiFiConnect()
{
  if ((WiFi.status() != WL_CONNECTED))
  {
    vTaskDelay(100);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        vTaskDelay(1000);
        Serial.print("connecting to ssid\n");
    };  
  }
}

void WiFiTCPConnect()
{
  if ((WiFi.status() == WL_CONNECTED)&& (client.connected() == false))
  {
    while (!client.connect(tcp_ip.c_str(), tcp_port)) {
        Serial.println("tcp connection failed\n");
        vTaskDelay(1000);
    }
    Serial.println("Connected to: " + tcp_ip + " Port: " + String(tcp_port)+"\n");
  }
}

void WiFiTask(void *pvParameters)
{
  (void) pvParameters;
    
  while(1)
  {
    WiFiConnect();
    WiFiTCPConnect();
    vTaskDelay(100);
  }  
}

void WiFiReadTask(void *pvParameters)
{
  (void) pvParameters;
  while(1)
  {
    while ((WiFi.status() == WL_CONNECTED)&&(client.available() == false) && (client.connected() != false)) {
      // while we're connected and no data's available
    }
    while((WiFi.status() == WL_CONNECTED)&&(client.available() != false) && (client.connected() != false)) {
      String line = client.readStringUntil('\n');
      Serial.print(line + "\n");
    }
    vTaskDelay(100);
  }
}

void WiFiSendTask(void *pvParameters)
{
  (void) pvParameters;
  while (1)
  {
    while ((WiFi.status() == WL_CONNECTED)&&(client.connected() == false))
    {
      vTaskDelay(1000);  // wait for read task to reconnect
    }
    while ((WiFi.status() == WL_CONNECTED)&&(client.connected()!= false))
    {
      vTaskDelay(100);
      int val = analogRead(34); // reads pin 34
      WiFiSendData(String(val));
    }
  }
}

void WiFiSendData(String data)
{
  if ((WiFi.status() == WL_CONNECTED)&&(client.connected()!=false))
  {
    client.print(data + "\n");
  }
}
