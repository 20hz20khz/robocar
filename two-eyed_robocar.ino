
/*
 Two-eyed Robocar
 Using two HC-SR04 Ping Distance sensors: Left eye & Right eye
 Both VCC to Arduino 5v
 Both GND to Arduino GND
 Echo (of Right eye) to Arduino pin 13
 Trig (of Right eye) to Arduino pin 12
 Echo (of Left eye) to Arduino pin 11
 Trig (of Left eye) to Arduino pin 10
 Right servo control to Arduino pin 9
 Left servo control to Arduino pin 8

 Original code improvements to the Ping sketch sourced from Trollmaker.com
 Some code and wiring inspired by http://en.wikiversity.org/wiki/User:Dstaub/robotcar
 */

#include <Servo.h> 

Servo rightServo;
Servo leftServo;

#define rightTrigPin 13
#define rightEchoPin 12
#define leftTrigPin 11
#define leftEchoPin 10

void setup() {
  Serial.begin (9600);
  pinMode(rightTrigPin, OUTPUT);
  pinMode(rightEchoPin, INPUT);
  pinMode(leftTrigPin, OUTPUT);
  pinMode(leftEchoPin, INPUT);
  rightServo.attach(9);
  rightServo.write(90);  // set servo to mid-point
  leftServo.attach(8);
  leftServo.write(90);  // set servo to mid-point
}

int checkEye(int trigPin, int echoPin, long distance){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  if ( distance <= 0){
    distance =999;
  }
  return distance;
}

void goForwardBot(){ 
   rightServo.write(180);  // right anticlockwise
   leftServo.write(1);  // left clockwise
}

void reverseBot(){ 
   rightServo.write(90);  // slowly reverse
   leftServo.write(90);  // slowly reverse
}

void turnRightBot(){
   rightServo.write(90);  // ?????
   leftServo.write(90);  // ?????
}

void turnLeftBot(){
   rightServo.write(90);  // ?????
   leftServo.write(90);  // ?????
}

void loop() {
  
  // Check the right eye
  int rightDistance = checkEye(rightTrigPin, rightEchoPin, rightDistance);
  
  // Check the left eye
  int leftDistance = checkEye(leftTrigPin, leftEchoPin, leftDistance);

  // If this, then that
  if (rightDistance < 5 && leftDistance < 5) {  // Both eyes see obstacle
    
  }
  else if (rightDistance < 5) { // Only right eye sees obstacle
    
  }
  else if (leftDistance < 5) { // Only left eye sees obstacle
    
  }
  else {
    
  }


  // The following code is for troubleshooting. When plugged into computer, open the Serial Monitor
  if (rightDistance >= 200 || rightDistance <= 0 || leftDistance >= 200 || leftDistance <= 0){
    if (leftDistance >= 200 || leftDistance <= 0){
      Serial.println("Left eye out of range");
    }
    if (rightDistance >= 200 || rightDistance <= 0){
      Serial.println("Right eye out of range");
    }
  }
  else {
    Serial.print("Left eye = ");
    Serial.print(leftDistance);
    Serial.print(" cm, Right eye = ");
    Serial.print(rightDistance);
    Serial.println(" cm");
  }
  delay(250); // This was set to 500 before. Let's try 250.
}
