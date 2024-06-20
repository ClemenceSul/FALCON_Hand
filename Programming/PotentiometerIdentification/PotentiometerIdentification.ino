#include <Adafruit_ADS1X15.h>
// GOAL: Take picture all extended, then flex one joint at a time, and it tells us which potentiometer pin it is.

#include <Wire.h>

Adafruit_ADS1115 ads1; 
Adafruit_ADS1115 ads2;
Adafruit_ADS1115 ads3;
Adafruit_ADS1115 ads4;


struct ADCModule {
  int A0;
  int A1;
  int A2;
  int A3;
};

struct ADCBlock {
  ADCModule Module1;
  ADCModule Module2;
  ADCModule Module3;
  ADCModule Module4;
};

struct Thumb {
  int A0;
  int A1;
  int A2;
  int A3;
  int A4;
};

ADCBlock HandExtended;
ADCBlock HandFlexed;
Thumb ThumbExtended;
Thumb ThumbFlexed;

void takePotentiometerValues (ADCBlock &data, Thumb &data2) {
  data.Module1.A0 = ads1.readADC_SingleEnded(0);
  data.Module1.A1 = ads1.readADC_SingleEnded(1);
  data.Module1.A2 = ads1.readADC_SingleEnded(2);
  data.Module1.A3 = ads1.readADC_SingleEnded(3);

  data.Module2.A0 = ads2.readADC_SingleEnded(0);
  data.Module2.A1 = ads2.readADC_SingleEnded(1);
  data.Module2.A2 = ads2.readADC_SingleEnded(2);
  data.Module2.A3 = ads2.readADC_SingleEnded(3);

  data.Module3.A0 = ads3.readADC_SingleEnded(0);
  data.Module3.A1 = ads3.readADC_SingleEnded(1);
  data.Module3.A2 = ads3.readADC_SingleEnded(2);
  data.Module3.A3 = ads3.readADC_SingleEnded(3);

  data.Module4.A0 = ads4.readADC_SingleEnded(0);
  data.Module4.A1 = ads4.readADC_SingleEnded(1);
  data.Module4.A2 = ads4.readADC_SingleEnded(2);
  data.Module4.A3 = ads4.readADC_SingleEnded(3);

  data2.A0 = analogRead(A0);
  data2.A1 = analogRead(A1);
  data2.A2 = analogRead(A2);
  data2.A3 = analogRead(A3);
  data2.A4 = analogRead(A4);
  
}

void setup() {
  Serial.begin(9600);
  ads1.begin(0x48);
  ads2.begin(0x49);
  ads3.begin(0x4A);
  ads4.begin(0x4B);
  // Take extend picture of joint angles
  Serial.println("Reading Initial Potentiometer Values");
  takePotentiometerValues(HandExtended, ThumbExtended);
}

void FindDifference (int value1, int value2, int &maxValue, String msg, String &maxMsg) {
  int difference = abs(value1 - value2);
  if (maxValue < difference) {
    maxValue = difference;
    maxMsg = msg;
  }
}

void loop() {
  // Wait for a bit
  // Prompt user to press Enter
  Serial.println("Flex one joint of the hand and press Enter to continue...");

  // Wait for the user to press Enter
  while (Serial.available() == 0) {
    // Do nothing and wait for serial input
  }
  
  // Clear the serial buffer
  while (Serial.available() > 0) {
    char c = Serial.read();
    // Check if Enter (newline character) is received
    if (c == '\n') {
      break;
    }
  }
  // Take new picture
  takePotentiometerValues(HandFlexed, ThumbFlexed);

  // Identify the pin
  int maxDifference = 0;
  String maxJoint;
  FindDifference(HandFlexed.Module1.A0, HandExtended.Module1.A0, maxDifference, "0x48 - A0", maxJoint);
  FindDifference(HandFlexed.Module1.A1, HandExtended.Module1.A1, maxDifference, "0x48 - A1", maxJoint);
  FindDifference(HandFlexed.Module1.A2, HandExtended.Module1.A2, maxDifference, "0x48 - A2", maxJoint);
  FindDifference(HandFlexed.Module1.A3, HandExtended.Module1.A3, maxDifference, "0x48 - A3", maxJoint);

  FindDifference(HandFlexed.Module2.A0, HandExtended.Module2.A0, maxDifference, "0x49 - A0", maxJoint);
  FindDifference(HandFlexed.Module2.A1, HandExtended.Module2.A1, maxDifference, "0x49 - A1", maxJoint);
  FindDifference(HandFlexed.Module2.A2, HandExtended.Module2.A2, maxDifference, "0x49 - A2", maxJoint);
  FindDifference(HandFlexed.Module2.A3, HandExtended.Module2.A3, maxDifference, "0x49 - A3", maxJoint);

  FindDifference(HandFlexed.Module3.A0, HandExtended.Module3.A0, maxDifference, "0x4A - A0", maxJoint);
  FindDifference(HandFlexed.Module3.A1, HandExtended.Module3.A1, maxDifference, "0x4A - A1", maxJoint);
  FindDifference(HandFlexed.Module3.A2, HandExtended.Module3.A2, maxDifference, "0x4A - A2", maxJoint);
  FindDifference(HandFlexed.Module3.A3, HandExtended.Module3.A3, maxDifference, "0x4A - A3", maxJoint);

  FindDifference(HandFlexed.Module4.A0, HandExtended.Module4.A0, maxDifference, "0x4B - A0", maxJoint);
  FindDifference(HandFlexed.Module4.A1, HandExtended.Module4.A1, maxDifference, "0x4B - A1", maxJoint);
  FindDifference(HandFlexed.Module4.A2, HandExtended.Module4.A2, maxDifference, "0x4B - A2", maxJoint);
  FindDifference(HandFlexed.Module4.A3, HandExtended.Module4.A3, maxDifference, "0x4B - A3", maxJoint);

  FindDifference(ThumbFlexed.A0, ThumbExtended.A0, maxDifference, "A0", maxJoint);
  FindDifference(ThumbFlexed.A1, ThumbExtended.A1, maxDifference, "A1", maxJoint);
  FindDifference(ThumbFlexed.A2, ThumbExtended.A2, maxDifference, "A2", maxJoint);
  FindDifference(ThumbFlexed.A3, ThumbExtended.A3, maxDifference, "A3", maxJoint);
  FindDifference(ThumbFlexed.A4, ThumbExtended.A4, maxDifference, "A4", maxJoint);

  Serial.println(maxJoint);
  
}
