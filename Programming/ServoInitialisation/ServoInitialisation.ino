#include <Servo.h>
Servo myservo;

void moveServo(int pin, int angle) {
  Serial.print("Moving servo ");
  Serial.println(pin);
  myservo.attach(pin+1);
  myservo.write(angle);
  delay(50);
  myservo.detach();
}


void setup() {
  Serial.begin(9600);
  Serial.println("Ready to start");
  moveServo(1, 180);
  moveServo(2, 0);
  moveServo(3, 180);
  moveServo(4, 0);
  moveServo(5, 180);
  moveServo(6, 180);
  moveServo(7, 0);
  moveServo(8, 0);
  moveServo(9, 180);
  moveServo(10, 0);
  Serial.println("Initialisation done.");
}

void loop() {
  // put your main code here, to run repeatedly:

}
