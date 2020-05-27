
void lcd_task(void *pvParameter)
{
    sensorData data;
    while (1)
    {
        lcd.setCursor(0, 0);
        if (xQueueReceive(queue_1, &data, portMAX_DELAY) == pdPASS)
        {   
            if (data.type == dht_sensor){
              lcd.print("temp (C):");
              lcd.setCursor(9,0);
              lcd.print(data.dht.temp);
              lcd.setCursor(0, 1);
              lcd.print("humidity (%):");
              lcd.setCursor(13,1);
              lcd.print(data.dht.humidity);
            }
        }
        taskYIELD();
    }
}
