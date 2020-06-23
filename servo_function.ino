const TickType_t xFlushDelay = 500 / portTICK_PERIOD_MS;

void flushPlantTask(void* pvParameters){
  (void) pvParameters;
  for (;;)
  {
    PRINTI("Flusing the plant");
    int pos = 0;

    for (pos = 0; pos <= 180; pos += 10) { 
      Servo1.write(pos);    
      delay(10);                      
    }
    for (pos = 180; pos >= 0; pos -= 10) { 
      Servo1.write(pos);             
      delay(105);                       
    }
    vTaskDelay(xFlushDelay);
  }
}

void BlynkFlushPlant() {
  int pos = 0;

  for (pos = 0; pos <= 180; pos += 10) { 
    Servo1.write(pos);    
    delay(10);                      
  }
  for (pos = 180; pos >= 0; pos -= 10) { 
    Servo1.write(pos);             
    delay(105);                       
  }

}
