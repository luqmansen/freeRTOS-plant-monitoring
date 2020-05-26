#include <dht11.h>
#define DHT11PIN 6

dht11 DHT11;

void dht11_task(void *pvParameters)
{
    while (1)
    {
      struct dhtData data;
      data = read_dht11();
      xQueueSend(queue_1, &data, portMAX_DELAY);
      taskYIELD();
    }
 
}

dhtData read_dht11()
{
  struct dhtData data;
  int chk = DHT11.read(DHT11PIN);
  if(chk != 0){
    Serial.print("[ERROR] Read dht11 error: ");
    Serial.println(chk);
  }
  else {
    data.temp = (float)DHT11.temperature;
    data.humidity = (float)DHT11.humidity;
    delay(100);
    return data;
    }
}
