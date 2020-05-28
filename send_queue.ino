void sendQueue(sensorData *data){
  Serial.println("[INFO] Trying to send data"); 
  xSemaphoreTake(xMutex, portMAX_DELAY);
  xQueueSend(queue_1, &data, portMAX_DELAY); 
  xSemaphoreGive(xMutex);
}
