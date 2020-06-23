
void initRTOS(){
    createQueue();
//    createMutex();
    createTask();
//    createTimer();/

}

void createTask()
{
    if (queue_1 != NULL)
    {
      xReturned = xTaskCreate(lcd_task, "lcd_task", 128, NULL, 2, NULL);
      checkTaskCreation("lcd_task", xReturned);
      
      xReturned = xTaskCreate(dht11_task, "dht11_task", 128, NULL, 1, NULL);
      checkTaskCreation("dht11_task", xReturned);

      xReturned = xTaskCreate(flushPlantTask, "flushPlantTask", 128, NULL, 3, NULL);
      checkTaskCreation("flushPlantTask", xReturned);
  
//      xReturned = xTaskCreate(ldr_task, "ldr_task", 128, NULL, 0, NULL);
//      checkTaskCreation("ldr_task", xReturned);
  
  //    xReturned = xTaskCreate(mq9_task, "mq9_task", 100, NULL, 3, NULL);
  //    checkTaskCreation("mq9_task", xReturned);
    
    }
    vTaskStartScheduler();

}

//void createTimer()
//{
//  xFlushAutoTimer = xTimerCreate(
//    "FlushTimer",
//    mainAUTO_RELOAD_TIMER_PERIOD,
//    pdTRUE,
//    0,
//    FlushPlant);
//    
//  if (xFlushAutoTimer != NULL) 
//  {
//    xFlushTimerStarted = xTimerStart(xFlushAutoTimer, 0);
//    
//    if (xFlushTimerStarted == pdPASS) 
//    {
//      PRINTI("Timer task started");
//      vTaskStartScheduler();
//    }
//  }
//}

void createQueue(){
    queue_1 = xQueueCreate(10, sizeof(sensorData));
    if (queue_1 == NULL)
    {
        PRINTE("Can't create queue");
    }
    PRINTI("Queue created");
    checkMemory();
}

//void createMutex(){
//  xMutex = xSemaphoreCreateMutex();
//    if (xMutex == NULL){
//      PRINTE("Can't create mutex");
//    }
//    PRINTI("Mutex created");
//}

void checkTaskCreation(String task_name, BaseType_t xReturned){
  if (xReturned == pdPASS){
    PRINT("created ", task_name);
  } else if (xReturned == errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY){
    PRINTE("Can't create Task, memory allocation error");
  }else{
    PRINTE("Create task unknown error");
  }
  checkMemory();
}
