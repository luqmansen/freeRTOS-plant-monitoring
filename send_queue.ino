
void sendQueue(sensorData data){
  PRINTI("Trying to send data");
//  xSemaphoreTake(xMutex, portMAX_/DELAY);
  xQueueSend(queue_1, &data, portMAX_DELAY); 
//  xSemaphoreGive(xMutex);/
  PRINTI("Data sent");
}
