//float ADC_value=0.0048828125;
//float analogReading;
//
//void ldr_task(void *pvParameters){
//
//  (void) pvParameters;
//    for (;;)
//    {
//      sensorData data;
//      data = readLDR();
//      #ifdef BLYNK
//       Blynk.virtualWrite(VIRT_FLUX, data.analog.value);
//      #endif
//      sendQueue(data);
//      vTaskDelay( xDelay );
//    }
//}
//
//sensorData readLDR(){
//    sensorData data;
//    data.type = ldr_sensor;
//    analogReading = analogRead(LDR);
//    data.analog.value = calculateLux(analogReading);
//    PRINT("raw: ", analogReading );
//    PRINT("lux: ", data.analog.value);
//    return data;
//}
//
//float calculateLux(float val){
//  if (val != 0){
//    return (250.000000/(ADC_value*val))-50.000000;
//  }
//  return 0.0;
//}
