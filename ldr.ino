float ADC_value=0.0048828125;
float analogReading;

void ldr_task(void *pvParameter){

  sensorData data;
    while (1)
    {
      Serial.println("[INFO] LDR TASK");
      data = readLDR();
      sendQueue(&data);
      Serial.println("[INFO] LDR data sent");
      taskYIELD(); 
    }
}

sensorData readLDR(){
    sensorData data;
    data.type = ldr_sensor;
    analogReading = analogRead(LDR);
    data.analog.value = calculateLux(analogReading);
    Serial.print("[INFO] LDR | raw: ");
    Serial.print(analogReading);
    Serial.print("| lux: ");
    Serial.println(data.analog.value);  
    return data;
}

float calculateLux(float val){
  if (val != 0){
    return (250.000000/(ADC_value*val))-50.000000;
  }
  return 0.0;
}
