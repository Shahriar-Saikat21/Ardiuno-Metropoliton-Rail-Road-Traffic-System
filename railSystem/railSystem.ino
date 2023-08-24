#include <Servo.h>

#define buzzer 6

Servo servo1;
Servo servo2;

const int trigPin1 = 10;
const int echoPin1 = 11;
const int trigPin2 = 12;
const int echoPin2 = 13;

long duration1, duration2;
int distance1, distance2;

int flag = 0;


void setup() {
  //For Servo
  servo1.attach(9);
  servo2.attach(8);
  //For Sonar 1
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  //For Sonar 2
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  //Button for manual agte open close
  pinMode(3, INPUT_PULLUP);

  //led signal
  pinMode(4, OUTPUT);  //for green
  pinMode(5, OUTPUT);  //for red

  //For buzzer
  pinMode(buzzer, OUTPUT);

  Serial.begin(9600);
}


void loop() {

  // Sonar 1
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = duration1 * 0.034 / 2;

  // Sonar 2
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  distance2 = duration2 * 0.034 / 2;

  

  // Prints the distance on the Serial Monitor
  Serial.print("Distance One: ");
  Serial.println(distance1);
  Serial.print("Distance Two: ");
  Serial.println(distance2);
  delay(100);

  //btn
  byte btn = digitalRead(3);


  if (distance1 < 3 || distance2 < 3 || btn == LOW) {
    if (flag == 0) {
      flag = 1;
      servoGateClose();
      trainSignalOn();
    } else if(distance1 > 3 || distance2 > 3 || btn == LOW){
      flag = 0;
      servoGateOpen();
      trainSignalOff();
    }
  }
}

void servoGateClose() {
  for (int i = 0; i <= 90; i++) {
    servo1.write(i);
    servo2.write(i);
    delay(15);
  }
}

void servoGateOpen() {
  for (int i = 90; i >= 0; i--) {
    servo1.write(i);
    servo2.write(i);
    delay(15);
  }
}

void trainSignalOn() {
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);
  tone(buzzer, 50);
  delay(100);
}

void trainSignalOff() {
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
  noTone(buzzer);
  delay(100);
}
