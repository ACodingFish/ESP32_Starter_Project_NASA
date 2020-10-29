
#include <WiFi.h>
#include "WiFiTask.h"

//constants
const char* ssid     = "xxxxxxxxxx";
const char* password = "xxxxxxxxxx";
const unsigned int MAX_INPUT = 2048;
String tcp_ip = "xxx.xxx.x.xx";
const int tcp_port = 10000;

WiFiClient client;

//functions for non-blocking recieve
void process_data (const char * data)
{
Serial.println (data);
}

void processIncomingByte (const byte inByte)
{
static char input_line [MAX_INPUT];
static unsigned int input_pos = 0;

switch (inByte)
  {

  case '\n':   // end of text
    input_line [input_pos] = 0;  // terminating null byte
    
    
    process_data (input_line);
    
    
    input_pos = 0;  
    break;

  case '\r':   
    break;

  default:
    
    if (input_pos < (MAX_INPUT - 1))
      input_line [input_pos++] = inByte;
    break;

  } 
 
}
//end of functions for a non-blocking recieve 

//WiFi setup functions
void WiFiConnect()
{
  if ((WiFi.status() != WL_CONNECTED))
  {
    delay(100);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
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
        delay(1000);
    }
    Serial.println("Connected to: " + tcp_ip + " Port: " + String(tcp_port)+"\n");
  }
}

void WiFiTask()
{
    
 
    WiFiConnect();
    WiFiTCPConnect();
    delay(100);

}
//end of WiFi setup functions

//ESP32 read and write functions
void WiFiReadTask()
{
    if((client.available() > 0) && (WiFi.status() == WL_CONNECTED) && (client.connected() != false))
    
    {
       processIncomingByte(client.read ());
    }
    
}

void WiFiSendTask()
{
   if((WiFi.status() == WL_CONNECTED)&&(client.connected()!= false))
    {
      int val = analogRead(34); // reads pin 34
      WiFiSendData(String(val));
    }
}

void WiFiSendData(String data)
{
    if ((WiFi.status() == WL_CONNECTED)&&(client.connected()!=false))
    {
     
      client.print(data + "\n");
    }
    
    if ((WiFi.status() != WL_CONNECTED) || (client.connected()== false))
    {
      WiFiTask();
    }
}
//end of ESP32 read and write functions

//end of functions 
