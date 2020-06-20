
void lcd_task(void *pvParameter)
{
    sensorData data;
    lcd.clear();
    while (1)
    {
        PRINTS("\r[INFO] LCD TASK");
        if (xQueueReceive(queue_1, &data, portMAX_DELAY) == pdPASS)
        {   
            PRINTS("\r[INF0] received: ");
            if (data.type == dht_sensor){
              Serial.println("DHT");  
              lcd.setCursor(0,0);
              lcd.print("temp(C): ");
              lcd.setCursor(10,0);
              lcd.print(data.dht.temp);
              lcd.setCursor(0, 1);
              lcd.print("humidity(%): ");
              lcd.setCursor(14,1);
              lcd.print(data.dht.humidity);
            } else if (data.type == ldr_sensor){
              Serial.println("LDR");  
              lcd.setCursor(0,2);
              lcd.print("lux: ");
              lcd.setCursor(6,2);
              lcd.print(data.analog.value);
            }
        }
//        taskYIELD();
        xTaskDelay(10);

    }
}
