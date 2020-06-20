
void initRTOS(){
    createMutex();
    createQueue();
    createTask();
}

void createTask(){
    xReturned = xTaskCreate(lcd_task, "LCD TASK", 200, NULL, 3, NULL);
    checkTaskCreation("LCD", xReturned);
    
    xReturned = xTaskCreate(dht11_task, "DHT11 TASK", 200, NULL, 1, NULL);
    checkTaskCreation("DHT11" ,xReturned);
    
//    xReturned = xTaskCreate(mq9_task, "MQ-9 GAS TASK", 200, NULL, 3, NULL);
//    checkTaskCreation("MQ-9",xReturned);
//    
    xReturned = xTaskCreate(ldr_task, "LDR TASK", 200, NULL, 1, NULL);
    checkTaskCreation("LDR", xReturned);

    
    vTaskStartScheduler();
    checkMemory();
    PRINTS("\r[INFO] Task schedule started");
}

void createQueue(){
    queue_1 = xQueueCreate(2, sizeof(sensorData));
    if (queue_1 == NULL)
    {
        PRINTS("\r[ERROR] Can't create queue");
    }
    PRINTS("\r[INFO] Queue created");
}

void createMutex(){
  xMutex = xSemaphoreCreateMutex();
    if (xMutex == NULL){
      PRINTS("\r[ERROR] Can't create mutex");
    }
    PRINTS("\r[INFO] Mutex created");
}

void checkTaskCreation(String task_name, BaseType_t xReturned){
  if (xReturned == pdPASS){
    PRINT("\r[INFO] created ", task_name);
  } else if (xReturned == errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY){
    PRINTS("\r[ERROR] Can't create Task, memory allocation error");
  }else{
    PRINTS("\r[ERROR] Create task unknown error");
  }
  checkMemory();
}
