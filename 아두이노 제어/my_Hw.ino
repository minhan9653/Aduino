#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
#include "FaceLook.h"
#include "U8glib.h"


// 핀 번호 정의
#define TRIGGER_PIN 4
#define ECHO_PIN 5

#define LED_PIN_G 10

#define BUZZER_PIN 9

const int cdsPin = A0;  // CDS 센서 연결 핀
const int ledPin = 8;   // LED 연결 핀



// 초음파 센서와 CDS 센서의 값, LED, 부저 초기화
int cdsValue = 0;
float distance = 0;
unsigned long previousMillis = 0;
unsigned long personDuration = 0;
unsigned long personStartTime = 0; // 사람 감지 시작 시간을 저장하는 변수


bool isPersonPresent = false; // 사람이 있는지 여부를 나타내는 변수
#include <wiring_private.h>     // i2c
#include <SPI.h>
#include "U8glib.h"
#include "FaceLook.h"

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);
#define MAX_FACE_LOOK 24

int _width  = 96 ;// 86
int _height = 32 ;// 32


void draw_face(int n) 
{ 
  
  u8g.firstPage();  
  do {
    //u8g2.drawXBMP(16, 16, _width , _height, face[n]); 
    u8g.drawBitmapP( 16, 16, 12, _height, face[n]);
  } while( u8g.nextPage() );
  
}


void setup() {


 display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // OLED 디스플레이 초기화
display.clearDisplay();
display.setTextColor(WHITE);
display.setTextSize(1); // 글자 크기를 1로 설정
display.setCursor(0, 0);




display.print("표정: ");Serial.println(1);
draw_face(1); 
display.display();





  
  Serial.begin(115200); // 시리얼 통신 시작
  pinMode(TRIGGER_PIN, OUTPUT); // 트리거 핀을 출력 모드로 설정
  pinMode(ECHO_PIN, INPUT); // 에코 핀을 입력 모드로 설정
   pinMode(ledPin, OUTPUT); // CDS 핀을 입력 모드로 설정
  pinMode(LED_PIN_G, OUTPUT); // 초록색 LED 핀을 출력 모드로 설정
  
  pinMode(BUZZER_PIN, OUTPUT); // 부저 핀을 출력 모드로 설정
  


}





void loop() {


    int cdsValue = analogRead(cdsPin);  // CDS 센서의 아날로그 값 읽기
  Serial.print("CDS Value: ");        // 시리얼 모니터에 CDS 값 출력 (디버깅용)
  Serial.println(cdsValue);
  
  if (cdsValue <= 400) {   // CDS 값이 400 이하인 경우
    digitalWrite(ledPin, HIGH);  // LED 켜기
  } else {
    digitalWrite(ledPin, LOW);  // LED 끄기
  }

  
  // 초음파 센서로 거리 측정
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.0343 / 2;

  // CDS 센서로 어둠 감지
  

  // 거리가 30cm 이내인 경우 부저를 1초 간격으로 울림
  if (distance <= 30) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= 1000) {
      previousMillis = currentMillis;
      tone(BUZZER_PIN, 1000);
      delay(100);
      noTone(BUZZER_PIN);
    }
  }






  

  // 거리가 1미터 이내인 경우 GREEN LED를 켬
  if (distance < 100) { // 거리가 100cm(1미터) 이내인 경우
    digitalWrite(LED_PIN_G, HIGH); // 초록색 LED를 켬
    Serial.println("Person Detected!"); // 시리얼 모니터에 감지 메시지 출력
  } else { // 거리가 1미터 이상인 경우
    digitalWrite(LED_PIN_G, LOW); // 초록색 LED를 끔
  }
   if (distance <= 100 && distance >= 30 && cdsValue > 400) {
  delay(1000);  // 1초 딜레이

 if (distance <= 100 && distance >= 30) {
    if (cdsValue > 400) {
      if (personStartTime == 0) {
        personStartTime = millis();
      }
      personDuration = millis() - personStartTime;
    } else {
      personStartTime = 0;
      personDuration = 0;
    }
  } else {
    personStartTime = 0;
    personDuration = 0;
  }



  // personDuration이 1초 이상인 경우 OLED에 웃는 표정 출력
  if (personDuration >= 100) {
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.print("표정: ");Serial.println(1);
    draw_face(21); 
    delay(300);

display.display(); 
     
    display.display();
  } else {
    // personDuration이 1초 미만인 경우 이전의 표현을 유지
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.setCursor(0, 0);
   
    display.display();
  }


  

 
  
 
}





}
