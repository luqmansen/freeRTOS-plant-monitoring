

void mq9_task(void *pvParameter){
  for(;;){
    float val= digitalRead(MQ9);
    Serial.print("MQ9 reading: ");
    Serial.println(val);  
    taskYIELD(); 
  }
}
