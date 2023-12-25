int analogPin = A0;     // 아날로그 입력핀 A0에 연결된 NTCT 센서
float resistance, temperature;  // 저항값, 온도 변수

void setup() {
  Serial.begin(115200);   // 시리얼 통신 초기화
}

void loop() {
  int rawValue = analogRead(analogPin);  // 아날로그 입력핀에서 센서의 저항값 읽기
  resistance = 10000.0 / (1023.0 / rawValue - 1);  // 저항값 계산
  temperature = log(resistance / 10000.0) / 3950.0 + 1.0 / (25.0 + 273.15);  // 온도 계산
  temperature = 1.0 / temperature - 273.15;  // 온도 계산
  Serial.print("Temperature: ");  // 온도 값 시리얼 통신으로 출력
  Serial.print(temperature);
  Serial.println(" C");
  delay(1000);  // 1초 지연
}
