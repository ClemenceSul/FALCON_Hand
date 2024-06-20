#include "DCmotorClass.h"
#include "PotentiometerClass.h"

// Constructor implementation
DCmotorClass::DCmotorClass(int pinE, int pin1, int pin2, byte addr, int pinPIP, int pinDIP) 
  : DIP(pinDIP, addr), PIP(pinPIP, addr) {
  //Setup motor
  _pinE = pinE;
  pinMode(_pinE, OUTPUT);
  _pin1 = pin1;
  pinMode(_pin1, OUTPUT);
  _pin2 = pin2;
  pinMode(_pin2, OUTPUT);

  _pinPIP = pinPIP;
  _pinDIP = pinDIP;

  thumb = false;
  if (addr == 0) {
    thumb == true;
  }
}

void DCmotorClass::contract() {
  analogWrite(_pinE, 255); // Any value between 0 and 255
  digitalWrite(_pin1, HIGH);
  digitalWrite(_pin2, LOW); 
}

void DCmotorClass::extend() {
  analogWrite(_pinE, 200); // Any value between 0 and 255
  digitalWrite(_pin1, LOW);
  digitalWrite(_pin2, HIGH); 
}

void DCmotorClass::freeze() {
  digitalWrite(_pin1, LOW);
  digitalWrite(_pin2, LOW); 
}


void DCmotorClass::reachAngleDIP(int angle) {
  bool moved = false;
  while (true) {
    int newangle;
    if (thumb == true) {
      newangle=map(analogRead(_pinDIP), 0, 410, 0, 90);
    } else {
      newangle = DIP.getValue();
    }
    if (angle > newangle) {
      extend();
    } else if (angle < newangle) {
      contract();
    } else {
      freeze();
      break;
    }
  }
}

void DCmotorClass::reachAnglePIP(int angle) {
  bool moved = false;
  while (true) {
    int newangle;
    if (thumb == true) {
      newangle=map(analogRead(_pinPIP), 563, 930, 0, 90);
    } else {
      newangle = PIP.getValue();
    }
    if (angle > newangle) {
      extend();
    } else if (angle < newangle) {
      contract();
    } else {
      freeze();
      break;
    }
  }
}


void DCmotorClass::resetFinger() {
  reachAnglePIP(89);
  reachAngleDIP(89);
}
