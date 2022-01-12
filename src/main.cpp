#include <Arduino.h>
#include <Ticker.h>
#include "DHTesp.h" // Click here to get the library: http://librarymanager/All#DHTesp
#include "device.h"

Ticker timer1Sec, ledOff;
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
  ledOff.once_ms(100, [](){
      digitalWrite(LED_BUILTIN, LED_BUILTIN_OFF);
  });
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
#if defined(ESP32)  
  timer1Sec.attach_ms(2*dht.getMinimumSamplingPeriod(), OnTimerReadDht);
#endif  
}

void loop() {
#if defined(ESP8266)
  OnTimerReadDht();
  delay(2000);
#endif
}