#include "ServoClass.h"
#include <Servo.h>
#include "PotentiometerClass.h"

// Constructor implementation
ServoClass::ServoClass(int pin, int rest, byte addr, int pinPot)
  : MCP(pinPot, addr) {
  _pin = pin + 1;
  _rest = rest;
  thumb = false;
  if (addr == 0) {
    thumb = true;
    _pinpot = pinPot;
  }
  threshold = 1; // Minimum change to consider as a change
  stableTime = 300; // Time in milliseconds to consider stable
}

// Member function implementation
void ServoClass::servoMove(int angle) {
  Serial.println("preping");
  if (_rest == 180) {
    angle = map(angle, 0, 180, 180, 0);
  }
  Servo myservo;
  myservo.attach(_pin);
  Serial.println("attached");
  myservo.write(angle);
  Serial.println("written");
  if (thumb == true) {
    waitForPotentiometerStableThumb();
  } else {
      waitForPotentiometerStable(); 
  }
  Serial.println("detached");
  myservo.detach();
  Serial.println("stuck here");
}

// Function to wait until the potentiometer value has stabilized
void ServoClass::waitForPotentiometerStable() {
  Serial.println("waiting for pot");
  int previousValue = MCP.getValue(); // Initial reading
  Serial.println(previousValue);
  unsigned long lastChangeTime = millis(); // Timestamp of the last change

  while (true) {
    int currentValue = MCP.getValue(); // Initial reading
    if (abs(currentValue - previousValue) > threshold) {
      lastChangeTime = millis(); // Reset the timestamp if there is a change
    }
    previousValue = currentValue; // Update the previous value

    if (millis() - lastChangeTime >= stableTime) {
      break; // Exit the loop if the value has been stable for the specified time
    }
  }
}

// Function to wait until the potentiometer value has stabilized
void ServoClass::waitForPotentiometerStableThumb() {
  Serial.println("waiting for pot thumb");
  int previousValue = analogRead(_pinpot); // Initial reading
  unsigned long lastChangeTime = millis(); // Timestamp of the last change

  while (true) {
    int currentValue = analogRead(_pinpot); // Initial reading
    if (abs(currentValue - previousValue) > threshold) {
      lastChangeTime = millis(); // Reset the timestamp if there is a change
    }
    previousValue = currentValue; // Update the previous value

    if (millis() - lastChangeTime >= stableTime) {
      break; // Exit the loop if the value has been stable for the specified time
    }
  }
}

void ServoClass::servoExtendFull() {
  servoMove(0);
}

void ServoClass::servoContractFull() {
  servoMove(180);
}
