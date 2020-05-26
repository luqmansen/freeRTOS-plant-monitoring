#include <dht11.h>
#define DHT11PIN 6

dht11 DHT11;

void dht11_task(void *pvParameters)
{
    while (1)
    {
      dhtData data;
      data = read_dht11();
      if (data.valid == true){
        xQueueSend(queue_1, &data, portMAX_DELAY);
        taskYIELD();  
      }
    }
 
}

dhtData read_dht11()
{
  dhtData data;
  int chk = DHT11.read(DHT11PIN);
  if(chk != 0){
    Serial.print("[ERROR] Read dht11 error: ");
    Serial.println(chk);
    data.valid = false;
  }
  else {
    data.temp = (float)DHT11.temperature;
    data.humidity = (float)DHT11.humidity;
    data.valid = true;
    delay(100);
    return data;
    }
}
