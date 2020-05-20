#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <LiquidCrystal.h>

#define RST 12
#define EN 11
#define D4 5
#define D5 4
#define D6 3
#define D7 2
#define sensorPin 0

QueueHandle_t queue_1;
LiquidCrystal lcd(RST, EN, D4, D5, D6, D7);

void setup()
{
    lcd.begin(16, 2);
    lcd.print("Plant-monitor");
    queue_1 = xQueueCreate(3, sizeof(float));
    if (queue_1 == NULL)
    {
        Serial.println("Can't create queue");
    }

    xTaskCreate(lcd_task, "LCD TASK", 200, NULL, 1, NULL);
    xTaskCreate(temp_task, "TEMPERATURE TASK", 200, NULL, 1, NULL);

    vTaskStartScheduler();
}

void lcd_task(void *pvParameter)
{
    float temperature = 0.0;
    lcd.begin(16, 2);
    while (1)
    {
        if (xQueueReceive(queue_1, &temperature, portMAX_DELAY == pdPASS))
        {
            lcd.setCursor(0, 0);
            lcd.print("temp:");
            lcd.setCursor(5,0);
            lcd.print(temperature);
        }
    }
}

void temp_task(void *pvParameters)
{
    float current_temp;
    while (1)
    {
        current_temp = read_temperature();
        xQueueSend(queue_1, &current_temp, portMAX_DELAY);
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

float read_temperature()
{
    //the resolution is 10 mV / degree centigrade with a
    //500 mV offset to allow for negative temperatures
    int reading = analogRead(sensorPin);
    // converting that reading to voltage, for 3.3v arduino use 3.3
    float voltage = (reading * 5.0) / 1024;
    //converting from 10 mv per degree wit 500 mV offset
    //to degrees ((voltage - 500mV) times 100)
    float temperatureC = (voltage - 0.5) * 100;
    return temperatureC;
}

void loop(){}
