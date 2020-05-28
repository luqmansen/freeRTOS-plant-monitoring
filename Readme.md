# Free-RTOS Plant Monitoring 
Plant montoring system utilizing real time operating system [FreeRTOS](https://www.freertos.org/)

## Info
- Still work in progress.
- Proteus project included for simulation purpose
- Proteus version is 8.6 SP 2 
- Compiled binary included for ease of use

## What's working now
- DHT11, MQ9, LCD, LDR

## Issues
- If `lcd_task` has higher priority than other task (currently `dht11_task`), sensor reading will throw `DHTlib_error_timeout`, this can be solved by setting the priority for lcd task lower than other, but LCD data update will show noticeable delay
- if two task that input to queue has same priority, the simulation will stuck 
- Memory not sufficient, need help to optimize the code

## Todo
- Implementing semaphore for task
- [x] Humidity sensor (DHT11, TMP36 will be replaced)
- [ ] Soil Moisture sensor (SEN-13322)
- [x] Sunlight sensor (LDR)
- [ ] Actuator (DC motor and servo)

## Component 
- Arduino UNO
- DHT11
- MQ-9 (should be MQ-811, but for the sake of simulation changed to this)
- LCD 16x4
- LDR
- ....(add more soon)

## Task
1. LCD Task (`lcd_task`)
2. DHT11 Task (`dht11_task`)
3. MQ-9 GAS TASK (`mq9_task`)
4. LDR task (`ldr_task`)

## Simulation
![image](./docs/proteus.png)
