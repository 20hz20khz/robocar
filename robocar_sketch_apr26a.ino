/*
 HC-SR04 Ping distance sensor]
 VCC to arduino 5v
 GND to arduino GND
 Echo to Arduino pin 13
 Trig to Arduino pin 12
 Red POS to Arduino pin 11
 Green POS to Arduino pin 10
 //560 ohm resistor to both LED NEG and GRD power rail
 More info at: http://goo.gl/kJ8Gl
 Original code improvements to the Ping sketch sourced from Trollmaker.com
 Some code and wiring inspired by http://en.wikiversity.org/wiki/User:Dstaub/robotcar
 */

#include <Servo.h> 

Servo myservo;
Servo myservo2;

#define triggerPin 13
#define echoPin 12
#define redLED 11
#define greenLED 10

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  myservo.attach(9);
  myservo.write(90);  // set servo to mid-point
  myservo2.attach(8);
  myservo2.write(90);  // set servo to mid-point
}

void goBot(){ 
   myservo.write(180);  // set servo to 180
   myservo2.write(1);  // set servo to mid-point
}

void stopBot(){ 
   myservo.write(90);  // set servo to mid-point
   myservo2.write(90);  // set servo to mid-point
}

void loop() {
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  if ( distance <= 0){
    distance =999;
  }
  if (distance < 50) {  // This is where the LED On/Off happens, < 50cm
    digitalWrite(redLED,HIGH); // When the Red condition is met, the Green LED should turn off
    digitalWrite(greenLED,LOW);
    goBot();
  }
  else {
    stopBot();
    digitalWrite(redLED,LOW);
    digitalWrite(greenLED,HIGH);
  }
  if (distance >= 200 || distance <= 0){
    Serial.println("Out of range");
  }
  else {
    Serial.print(distance);
    Serial.println(" cm");
  }
  delay(500);
}
