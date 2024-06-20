#ifndef ServoClass_H
#define ServoClass_H

#include <Arduino.h>
#include "PotentiometerClass.h"

class ServoClass {
  public:
    // Constructor
    ServoClass(int pin, int rest, byte addr = 0, int pinPot = 0);

    // functions
    void servoMove(int angle);
    void servoExtendFull();
    void servoContractFull();
    void servoContract(int angle);

  private:
    int _pin;
    bool thumb;
    int _rest;
    int _pinpot;
    int threshold;
    unsigned long stableTime;
    void waitForPotentiometerStable();
    void waitForPotentiometerStableThumb();
    PotentiometerClass MCP;
};

#endif
