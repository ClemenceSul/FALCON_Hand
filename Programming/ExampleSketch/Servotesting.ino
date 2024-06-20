#include "ServoClass.h"
ServoClass IndexF(1, 180, 0x49, 2);
ServoClass IndexA(2, 0, 0x49, 0);
ServoClass MiddleF(3, 180, 0x48, 3);
ServoClass RingA(4, 0, 0x4A, 3);
ServoClass RingF(5, 180, 0x4A, 0);
ServoClass LittleF(6, 180, 0x48, 1);
ServoClass LittleA(7, 0, 0x48, 3);
ServoClass ThumbR(9, 180, 0, A1);
ServoClass ThumbA(8, 180, 0, A4);
ServoClass ThumbF(10, 0, 0, A3);

#include "DCmotorClass.h"
DCmotorClass LittleDC(34, 37, 39, 0x4B, 2, 0);
DCmotorClass RingDC(36, 38, 35, 0x4A, 2, 1);
DCmotorClass MiddleDC(33, 31, 29, 0x48, 0, 1);
DCmotorClass IndexDC(28, 30, 32, 0x49, 3, 1);
DCmotorClass ThumbDC(23, 25, 27, 0, A0, A2);

void setup() {
  Serial.begin(9600);
  Serial.println("Ready");
}

void touchLittle() {
  Serial.println("touch pinky");
  Serial.println("ThumbR");
  ThumbR.servoMove(180);
  Serial.println("LittleA");
  LittleA.servoMove(50);
  Serial.println("ThumbA");
  ThumbA.servoMove(70);
  Serial.println("ThumbF");
  ThumbF.servoMove(180);
  Serial.println("LittleF");
  LittleF.servoMove(100);
  Serial.println("LittleDC");
  LittleDC.reachAnglePIP(40);
  //ThumbDC.reachAnglePIP(80); 
  Serial.println("finished");
}

void extendHand() {
  Serial.println("extend back");
  LittleF.servoMove(0);
  LittleDC.resetFinger();
  //ThumbDC.resetFinger();
  ThumbR.servoMove(0);
  LittleA.servoMove(0);
  ThumbA.servoMove(0);
  ThumbF.servoMove(0);
  LittleF.servoMove(0);
}


void loop() {
  IndexF.servoMove(0);
  
  touchLittle();
  
  Serial.println("waiting");
  delay(5000);
  extendHand();

  Serial.println("done");
  delay(10000000000);
}
