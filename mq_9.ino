

void mq9_task(void *pvParameter){

  sensorData data;
    while (1)
    {
      data = readMQ9();
      xQueueSend(queue_1, &data, portMAX_DELAY); 
      taskYIELD(); 
    }
}

sensorData readMQ9(){
    sensorData data;
    data.type = mq9_sensor;
    data.digital.value = digitalRead(MQ9);
    Serial.print("[INFO] MQ9 reading: ");
    Serial.println(data.digital.value);  
    return data;
}
