#ifndef PotentiometerClass_H
#define PotentiometerClass_H

#include <Arduino.h>

class PotentiometerClass {
  public:
    // Constructor
    PotentiometerClass(int pin, byte addr);

    // functions
    int getValue();
    int maxValue;
    int _pin;
    byte _addr;

  private:
    int potValue();
    bool initialised;
};

#endif
