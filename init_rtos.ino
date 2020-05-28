
void initRTOS(){
    createMutex();
    createQueue();
    createTask();
}

void createTask(){
    xReturned = xTaskCreate(lcd_task, "LCD TASK", 200, NULL, 3, NULL);
    checkTaskCreation("LCD", xReturned);
    
    xReturned = xTaskCreate(dht11_task, "DHT11 TASK", 200, NULL, 3, NULL);
    checkTaskCreation("DHT11" ,xReturned);
    
    xReturned = xTaskCreate(mq9_task, "MQ-9 GAS TASK", 200, NULL, 3, NULL);
    checkTaskCreation("MQ-9",xReturned);
    
    xReturned = xTaskCreate(ldr_task, "LDR TASK", 200, NULL, 3, NULL);
    checkTaskCreation("LDR", xReturned);

    
    vTaskStartScheduler();
    checkMemory();
    Serial.println(F("[INFO] Task schedule started"));
}

void createQueue(){
    queue_1 = xQueueCreate(2, sizeof(sensorData));
    if (queue_1 == NULL)
    {
        Serial.println(F("[ERROR] Can't create queue"));
    }
    Serial.println(F("[INFO] Queue created"));
}

void createMutex(){
  xMutex = xSemaphoreCreateMutex();
    if (xMutex == NULL){
      Serial.println(F("[ERROR] Can't create mutex"));
    }
    Serial.println(F("[INFO] Mutex created"));
}

void checkTaskCreation(String task_name, BaseType_t xReturned){
  if (xReturned == pdPASS){
    Serial.print(F("[INFO] created "));
    Serial.println(task_name);
  } else if (xReturned == errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY){
    Serial.println(F("[ERROR] Can't create Task, memory allocation error"));
  }else{
    Serial.println(F("[ERROR] Create task unknown error"));
  }
  checkMemory();
}
