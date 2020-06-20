float ADC_value=0.0048828125;
float analogReading;

void ldr_task(void *pvParameter){

  sensorData data;
    while (1)
    {
      PRINTS("\r[INFO] LDR TASK");
      data = readLDR();
      sendQueue(data);
      PRINTS("[INFO] LDR data sent");
//      taskYIELD(); 
//        xTaskDelay(10);

    }
}

sensorData readLDR(){
    sensorData data;
    data.type = ldr_sensor;
    analogReading = analogRead(LDR);
    data.analog.value = calculateLux(analogReading);
    PRINT("\r[INFO] LDR | raw: ", analogReading );
    PRINT("\r[INFO] LDR | lux: ", data.analog.value);
    return data;
}

float calculateLux(float val){
  if (val != 0){
    return (250.000000/(ADC_value*val))-50.000000;
  }
  return 0.0;
}
