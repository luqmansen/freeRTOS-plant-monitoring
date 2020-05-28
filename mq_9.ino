

void mq9_task(void *pvParameter){

  sensorData data;
    while (1)
    {
      data = readMQ9();
      sendQueue(&data);
      Serialprint("[INFO] MQ9 data sent \r"); 
      taskYIELD(); 
    }
}

sensorData readMQ9(){
    sensorData data;
    data.type = mq9_sensor;
    data.digital.value = digitalRead(MQ9);
    Serialprint("[INFO] MQ9 reading: %d \r",data.digital.value);
    return data;
}
