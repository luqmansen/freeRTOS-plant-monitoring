#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <LiquidCrystal.h>
#include <dht11.h>
#include <semphr.h>
#include <MemoryFree.h>


#define RST 12
#define EN 11
#define D4 5
#define D5 4
#define D6 3
#define D7 2
#define MQ9 7
#define LDR A0
#define DHT11PIN 6

enum sensor_msg_type{dht_sensor, ldr_sensor, mq9_sensor};

typedef struct{
  bool valid;
  long temp;
  long humidity;
}dhtData;

typedef struct{
  float value;
}analogData;

typedef struct{
  int value;
}digitalData;

typedef struct{
  enum sensor_msg_type type;
  union {
    dhtData dht;
    analogData analog;
    digitalData digital;
  };
}sensorData;

QueueHandle_t queue_1;
SemaphoreHandle_t xMutex;
BaseType_t xReturned;
LiquidCrystal lcd(RST, EN, D4, D5, D6, D7);

void setup()
{
    Serial.begin(9600);
    checkMemory();
    lcd.begin(16, 4);
    lcd.print("Plant-monitor");

    pinMode(MQ9, INPUT);
    initRTOS();
}

void StreamPrint_progmem(Print &out,PGM_P format,...)
{
  // program memory version of printf - copy of format string and result share a buffer
  // so as to avoid too much memory use
  char formatString[128], *ptr;
  strncpy_P( formatString, format, sizeof(formatString) ); // copy in from program mem15
  // null terminate - leave last char since we might need it in worst case for result's \0
  formatString[ sizeof(formatString)-2 ]='\0';
  ptr=&formatString[ strlen(formatString)+1 ]; // our result buffer...
  va_list args;
  va_start (args,format);
  vsnprintf(ptr, sizeof(formatString)-1-strlen(formatString), formatString, args );
  va_end (args);
  formatString[ sizeof(formatString)-1 ]='\0';
  out.print(ptr);
}
#define Serialprint(format, ...) StreamPrint_progmem(Serial,PSTR(format),##__VA_ARGS__)
#define Streamprint(stream,format, ...) StreamPrint_progmem(stream,PSTR(format),##__VA_ARGS__)

void loop(){}



 
