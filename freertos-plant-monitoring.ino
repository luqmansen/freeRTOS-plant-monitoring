#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <LiquidCrystal.h>

#define RST 12
#define EN 11
#define D4 5
#define D5 4
#define D6 3
#define D7 2

QueueHandle_t queue_1;
LiquidCrystal lcd(RST, EN, D4, D5, D6, D7);

struct dhtData {
  long temp;
  long humidity;
};


void setup()
{
    Serial.begin(9600);
    Serial.println("Plant-monitor");


    lcd.begin(16, 2);
    lcd.print("Plant-monitor");
    queue_1 = xQueueCreate(3, sizeof(dhtData));
    if (queue_1 == NULL)
    {
        Serial.println("Can't create queue");
    }

//    xTaskCreate(lcd_task, "LCD TASK", 200, NULL, 1, NULL);
    xTaskCreate(dht11_task, "TEMPERATURE TASK", 200, NULL, 1, NULL);
    vTaskStartScheduler();
}

void loop(){}



 
