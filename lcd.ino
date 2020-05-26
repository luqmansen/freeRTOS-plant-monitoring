
void lcd_task(void *pvParameter)
{
    struct dhtData data;
    lcd.begin(16, 2);
    while (1)
    {
//        lcd.clear();
        if (xQueueReceive(queue_1, &data, portMAX_DELAY == pdPASS))
        {
            lcd.setCursor(0, 0);
            lcd.print("temp (C):");
            lcd.setCursor(9,0);
            lcd.print(data.temp);
            lcd.setCursor(0, 1);
            lcd.print("humidity (%):");
            lcd.setCursor(13,1);
            lcd.print(data.humidity);
        }
    }
}
