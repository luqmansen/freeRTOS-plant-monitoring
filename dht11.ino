dht11 DHT11;

void dht11_task(void *pvParameters)
{ 
    sensorData data;
    for (;;)
    {
      data = read_dht11();
      if (data.dht.valid == true){
        sendQueue(&data);
        Serialprint("[INFO] DHT data sent\r");
      }
      taskYIELD(); 
    }
 
}

sensorData read_dht11()
{
  sensorData data;
  int chk = DHT11.read(DHT11PIN);
  if(chk != 0){
    Serialprint("[ERROR] Read dht11 error: %d \r", chk);
    data.dht.valid = false;
    return data;
  }
  else {
    data.type = dht_sensor;
    data.dht.temp = (float)DHT11.temperature;
    data.dht.humidity = (float)DHT11.humidity;
    data.dht.valid = true;
    Serialprint("[INFO] temp %d | humidity %d\r", data.dht.temp, data.dht.humidity);  
    delay(100);
    return data;
    };
}
