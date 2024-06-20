#include "PotentiometerClass.h"
#include <Adafruit_ADS1X15.h>
Adafruit_ADS1115 ads1115;
#include <Wire.h>

PotentiometerClass::PotentiometerClass(int pin, byte addr) {
  _pin = pin;
  _addr = addr;
  initialised = false;
}

PotentiometerClass::potValue() {
  Serial.println("get pot value");
  ads1115.begin(_addr);
  if (initialised == false) {
    Serial.println("initialised");
    maxValue = ads1115.readADC_SingleEnded(_pin);
    Serial.println(maxValue);
    initialised = true;
  }
  Serial.println("reached");
  return ads1115.readADC_SingleEnded(_pin);
}

PotentiometerClass::getValue() {
  Serial.println(potValue());
  return map(potValue(), 0, maxValue, 0, 90);
}
