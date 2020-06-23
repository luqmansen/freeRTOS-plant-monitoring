#include <Arduino_FreeRTOS.h>
#include <dht.h>
#include <queue.h>
#include <MemoryFree.h>
//#include <SimpleTimer.h>
#include <LiquidCrystal.h>
#include <semphr.h>
#include <BlynkSimpleStream.h>
#include <Servo.h> 
#include <timers.h>

#define RST 12
#define EN 11
#define D4 5
#define D5 4
#define D6 3
#define D7 2
#define MQ9 7
#define LDR A0
#define DHT11PIN 6
#define TESTPIN 8
#define V_TERMINAL V0
#define VIRT_DHT_TEMP V4
#define VIRT_DHT_HUMID V5
#define VIRT_FLUX V1
#define BLYNK 1
//#define DEBUG 1/

#if BLYNK
  #define PRINTI(s)   { Blynk.virtualWrite(V_TERMINAL, "\n[INFO] "); Blynk.virtualWrite(V_TERMINAL, s); Blynk.virtualWrite(V_TERMINAL, "\n");}
  #define PRINTW(s)   { Blynk.virtualWrite(V_TERMINAL, "\n[WARNING] "); Blynk.virtualWrite(V_TERMINAL, s); Blynk.virtualWrite(V_TERMINAL, "\n");}
  #define PRINTE(s)   { Blynk.virtualWrite(V_TERMINAL, "\n[ERR] "); Blynk.virtualWrite(V_TERMINAL, s); Blynk.virtualWrite(V_TERMINAL, "\n");}
  #define PRINT(s,v)  { Blynk.virtualWrite(V_TERMINAL, "\n[INFO] "); Blynk.virtualWrite(V_TERMINAL, s); Blynk.virtualWrite(V_TERMINAL, v); Blynk.virtualWrite(V_TERMINAL, "\n");}
#else
  #define PRINTI(s) 
  #define PRINTW(s) 
  #define PRINTE(s) 
  #define PRINT(s,v)
#endif

#if DEBUG
  #define PRINTI(s)   { Serial.print(F("[INFO] ")); Serial.println(F(s));}
  #define PRINTW(s)   { Serial.print(F("[WARNING] ")); Serial.println(F(s));}
  #define PRINTE(s)   { Serial.print(F("[ERR] ")); Serial.println(F(s));}
  #define PRINT(s,v)  { Serial.print(F("[INFO] ")); Serial.print(F(s)); Serial.println(v);}  
#endif

enum sensor_msg_type{dht_sensor, ldr_sensor, mq9_sensor};

typedef struct{
  bool valid;
  long temp;
  long humidity;
} dhtData;

typedef struct{
  float value;
} analogData;

typedef struct{
  int value;
} digitalData;

typedef struct{
  enum sensor_msg_type type;
  union {
    dhtData dht;
    analogData analog;
    digitalData digital;
  };
} sensorData;

const TickType_t xDelay = 500 / portTICK_PERIOD_MS;
//const mainAUTO_RELOAD_TIMER_PERIOD pdMS_TO_TICKS( 1000 );/ // every 1 second

BaseType_t xReturned, xFlushTimerStarted;
TimerHandle_t xFlushAutoTimer;
QueueHandle_t queue_1;
//SemaphoreHandle_t xMutex;

LiquidCrystal lcd(RST, EN, D4, D5, D6, D7);
dht dht;
Servo Servo1;  

char auth[] = "KcNQ-krkm7DRXxjPd0nvBwsgDtlJzlm2";

#ifdef BLYNK
  BLYNK_WRITE(V3) 
  {
    int pinValue = param.asInt();
    if (pinValue == 1) {    
      BlynkFlushPlant();             
      Blynk.run(); 
      int pinValue = 0;  
      Blynk.syncVirtual(V3); 
    }
  }
#endif

void setup()
{

  Serial.begin(9600);
  lcd.begin(16, 4);
  lcd.write("Plant-monitor");
  #ifdef BLYNK
    Blynk.begin(Serial, auth);
  #endif
  lcd.clear();
  Servo1.attach(9);
//  timer.setInterval(1000/L, BlynkFlushPlant);
  initRTOS();
}


void loop()
{
  #ifdef BLYNK
    Blynk.run();
  #endif
}
