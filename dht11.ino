dht dht;

void dht11_task(void *pvParameters)
{ 
    sensorData data;
    while (1)
    {
      PRINTS("\r[INFO] DHT TASK SENDING DATA");
      data = read_dht11();
      if (data.dht.valid == true){
        sendQueue(data);
        PRINTS("\r[INFO] DHT data sent");
      }
//      taskYIELD(); 
        xTaskDelay(10);

    }
 
}

sensorData read_dht11()
{
  sensorData data;
  int chk = dht.read11(DHT11PIN);
  if(chk != 0){
    PRINT("\r[ERROR] Read dht11 error: ", chk);
    data.dht.valid = false;
    return data;
  }
  else {
    data.type = dht_sensor;
    data.dht.temp = dht.temperature;
    data.dht.humidity = dht.humidity;
    data.dht.valid = true;
    PRINT("\r[INFO] data type :", data.type);
    PRINT("\r[INFO] read temp :", data.dht.temp);
    PRINT("\r[INFO] read humidity :", data.dht.humidity);    
    delay(100);
    return data;
    };
}
