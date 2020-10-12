#ifndef _WIFI_TASK_H_
#define _WIFI_TASK_H_

void WiFiTask(void *pvParameters);
void WiFiSendTask(void *pvParameters);
void WiFiReadTask(void *pvParameters);

#endif //_WIFI_TASK_H_
