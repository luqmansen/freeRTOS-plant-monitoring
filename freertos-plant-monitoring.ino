#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <LiquidCrystal.h>

#define RST 12
#define EN 11
#define D4 5
#define D5 4
#define D6 3
#define D7 2

enum sensor_msg_type{dht_sensor, ldr_sensor};

typedef struct{
  bool valid;
  long temp;
  long humidity;
}dhtData;

typedef struct{
  enum sensor_msg_type type;
  union {
    dhtData dht;
  };
}sensorData;

QueueHandle_t queue_1;
LiquidCrystal lcd(RST, EN, D4, D5, D6, D7);

void setup()
{
    Serial.begin(9600);
    lcd.begin(16, 4);
    lcd.print("Plant-monitor");
    
    queue_1 = xQueueCreate(3, sizeof(sensorData));
    
    if (queue_1 == NULL)
    {
        Serial.println("[ERROR] Can't create queue");
    }

    xTaskCreate(dht11_task, "DHT11 TASK", 200, NULL, 2, NULL);
    xTaskCreate(lcd_task, "LCD TASK", 200, NULL, 1, NULL);
    
    vTaskStartScheduler();
}

void loop(){}



 
