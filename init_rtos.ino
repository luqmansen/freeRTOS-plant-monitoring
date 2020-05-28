
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
    Serial.println("[INFO] Task schedule started");
}

void createQueue(){
    queue_1 = xQueueCreate(2, sizeof(sensorData));
    if (queue_1 == NULL)
    {
        Serial.println("[ERROR] Can't create queue");
    }
    Serial.println("[INFO] Queue created");
}

void createMutex(){
  xMutex = xSemaphoreCreateMutex();
    if (xMutex == NULL){
      Serial.println("[ERROR] Can't create mutex");
    }
    Serial.println("[INFO] Mutex created");
}

void checkTaskCreation(String task_name, BaseType_t xReturned){
  if (xReturned == pdPASS){
    Serial.print("[INFO] created ");
    Serial.print(task_name);
    Serial.println(" task");
  } else if (xReturned == errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY){
    Serial.println("[ERROR] Can't create Task, memory allocation error");
  }else{
    Serial.println("[ERROR] Create task unknown error");
  }
  checkMemory();
}
