#ifndef DCmotorClass_H
#define DCmotorClass_H

#include <Arduino.h>
#include "PotentiometerClass.h"

class DCmotorClass {
  public:
    // Constructor
    DCmotorClass(int pinE, int pin1, int pin2, byte addr, int pinPIP, int pinDIP);
    
    // functions
    void reachAngleDIP(int angle);
    void reachAnglePIP(int angle);
    void resetFinger();

  private:
    //sensors
    PotentiometerClass DIP;
    PotentiometerClass PIP;
    //motor
    int _pinE;
    int _pin1;
    int _pin2;
    void contract();
    void extend();
    void freeze();
    bool thumb;
    int _pinPIP;
    int _pinDIP;
    int maxDIP;
    int maxPIP;

    int threshold;
    int stableTime;
    void waitForPotentiometerStable();
};

#endif
