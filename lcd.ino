
void lcd_task(void *pvParameters)
{
    (void) pvParameters;
    for (;;)
    {
        sensorData data;
        PRINTI("LCD TASK");
        if (xQueueReceive(queue_1, &data, 10) == pdPASS)
        {   
            if (data.type == dht_sensor){
              PRINTI("DHT");  
              lcd.setCursor(0,0);
              lcd.print("temp(C): ");
              lcd.setCursor(10,0);
              lcd.print(data.dht.temp);
              lcd.setCursor(0, 1);
              lcd.print("humidity(%): ");
              lcd.setCursor(14,1);
              lcd.print(data.dht.humidity);
            } else if (data.type == ldr_sensor){
              PRINTI("LDR");  
              lcd.setCursor(0,2);
              lcd.print("lux: ");
              lcd.setCursor(6,2);
              lcd.print(data.analog.value);
            } else{
              PRINTW("Empty data"); 
             }
        }
        vTaskDelay( xDelay );
    }
}
