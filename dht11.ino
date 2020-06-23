
void dht11_task(void* pvParameters)
{ 
  (void) pvParameters;
  for (;;)
  {
    sensorData data;
    data = read_dht11();
    if (data.dht.valid == true){
      #ifdef BLYNK
       Blynk.virtualWrite(VIRT_DHT_TEMP, data.dht.temp);
       Blynk.virtualWrite(VIRT_DHT_HUMID, data.dht.humidity);
      #endif
      PRINT("temp:", data.dht.temp);
      PRINT("humidity:", data.dht.humidity);
      sendQueue(data);
      vTaskDelay( xDelay );
    }
    
    taskYIELD();
  }
}

sensorData read_dht11()
{
  sensorData data;
  int chk = dht.read11(DHT11PIN);
  if(chk != 0){
    PRINTE("Read dht11 error");
    data.dht.temp = 10;
    data.dht.humidity = 10;
    data.dht.valid = true;
    return data;
  }
  else {
    data.type = dht_sensor;
    data.dht.temp = dht.temperature;
    data.dht.humidity = dht.humidity;
    data.dht.valid = true;
    delay(500);
    return data;
    };
}
