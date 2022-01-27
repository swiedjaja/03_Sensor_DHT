#include <Arduino.h>
#include "DHTesp.h" // Click here to get the library: http://librarymanager/All#DHTesp
#include "device.h"

DHTesp dht;

void OnTimerReadDht()
{
  digitalWrite(LED_BUILTIN, LED_BUILTIN_ON);
  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();
  if (dht.getStatus()==DHTesp::ERROR_NONE)
  {
    Serial.printf("Temperature: %.2f C, Humidity: %.2f %%\n", temperature, humidity);
  }
  digitalWrite(LED_BUILTIN, LED_BUILTIN_OFF);
}

void setup() {
  Serial.begin(115200);
  delay(100);
  pinMode(LED_BUILTIN, OUTPUT);
#if defined(LED_FLASH)    
  pinMode(LED_FLASH, OUTPUT);
#endif  
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(PIN_SW, INPUT);
  dht.setup(PIN_DHT, DHTesp::DHT11);

  Serial.printf("Board: %s\n", ARDUINO_BOARD);
  Serial.printf("DHT Sensor ready, sampling period: %d ms\n", dht.getMinimumSamplingPeriod());  
}

void loop() {
  if (millis()%3000==0)
    OnTimerReadDht();
}