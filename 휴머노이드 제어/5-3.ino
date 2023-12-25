#include <SoftwareSerial.h>
#include "Robot.h"

#define trigPin 4
#define echoPin 5
#define buzzerPin 11 // 부저 핀


int SW = 8;
int sw_value = 0, sw_value1 = 0;

int distance;
int cds_value; 

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT); // 부저 핀 설정
  Serial.begin(115200);
  BT.begin(115200);
   pinMode(A0, INPUT);
   pinMode(buzzerPin, OUTPUT); // 부저 핀 설정
  pinMode(SW, INPUT_PULLUP); 


  
}

void loop() {
  // 초음파 센서로 거리 측정
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  distance = pulseIn(echoPin, HIGH) / 58.0; // cm 단위로 변환

  // 거리에 따라 동작 제어
  if (distance < 20) { // 20cm 이내로 가까워지면 11번 행동 수행
    Serial.println("Robot action 11");
    ActionRobot(11);
  } else { // 20cm 이상 멀어지면 49번 행동 수행
    Serial.println("Robot action 49");
    ActionRobot(49);
    digitalWrite(buzzerPin, HIGH); // 부저 울리기
    delay(500); // 0.5초 대기
    digitalWrite(buzzerPin, LOW); // 부저 멈추기
    delay(500); // 0.5초 대기
  }
  cds_value = analogRead(A0);
  if (cds_value < 100) { // 일정 값 이하일 때
    Serial.println("Robot action 23");
    ActionRobot(23);
  }
  delay(500); // 거리 측정 주기



  if (digitalRead(SW) == 1) {
    Serial.println("Robot action 240");
    ActionRobot(240);
    delay(500); // 0.5초 대기
  }
  


  
}
