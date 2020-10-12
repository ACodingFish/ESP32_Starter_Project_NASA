# ESP32_Starter_Project_NASA
Starter code for NASA Project.

## Server (RPI)
The server is a simple multi-threaded server.
### Configuration
Configure the test server in test_server.py with the following:
* ip (HOST)
* port (PORT)

Some configuration options are only seen within PI_Server.py such as:
* Max message size
* Max number of clients

### Launching
Launch the test server by running test_server.py in python3.7 or higher.

Type a message containing 'quit' to exit. Otherwise, type anything else to send it to all attached clients.

## RTOS Client (ESP32)

### Configuration
Configure the client in WiFiTask.ino with the following:
* ssid (WiFi Network Name)
* password (WiFi Network Password)
* ip (Host)
* port

### Launching
Make sure the required libraries are installed before compiling (esp32, etc).

Upload the code using the Arduino IDE to the EXPRESSIF ESP32-WROVER-B Module.

The code will automatically connect to the server and periodically send ADC data from pin 34.

