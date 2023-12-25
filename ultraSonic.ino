const int trigPin = 4;    // 초음파 발신핀
const int echoPin = 5;   // 초음파 수신핀
//const int ledPin = 10;
#define ledPin 10

void setup() {
  Serial.begin(115200);   // 시리얼 통신 초기화
  pinMode(trigPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  digitalWrite(trigPin, LOW);  // 초음파 발신핀 초기화
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);  // 초음파 발신 시작
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);  // 초음파 수신시간 측정
  float distance = duration * 0.034 / 2;  // 거리 계산
  Serial.print("거리: ");  // 거리 값 시리얼 통신으로 출력
  Serial.print(distance);
  Serial.println(" cm");
  if (distance < 50) 
    digitalWrite(ledPin,HIGH);
  else
    digitalWrite(ledPin,LOW);
  delay(500);  // 0.5초 지연
}
