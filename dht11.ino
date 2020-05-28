

dht11 DHT11;

void dht11_task(void *pvParameters)
{ 
    sensorData data;
    while (1)
    {
      Serial.println("[INFO] DHT TASK");
      data = read_dht11();
      if (data.dht.valid == true){
        sendQueue(&data);
        Serial.println("[INFO] DHT data sent");
      }
      taskYIELD(); 
    }
 
}

sensorData read_dht11()
{
  sensorData data;
  int chk = DHT11.read(DHT11PIN);
  if(chk != 0){
    Serialprint("[ERROR] Read dht11 error: %d \n", chk);
    data.dht.valid = false;
    return data;
  }
  else {
    data.type = dht_sensor;
    data.dht.temp = (float)DHT11.temperature;
    data.dht.humidity = (float)DHT11.humidity;
    data.dht.valid = true;
    delay(100);
    return data;
    };
}
