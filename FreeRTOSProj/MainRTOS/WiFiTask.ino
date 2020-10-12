/**
MIT License

Copyright (c) 2020 Jonathan Dean

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
**/
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
