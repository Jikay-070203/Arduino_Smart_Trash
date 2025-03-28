#include <Servo.h>

// Chân kết nối cảm biến
const int trig = 8;
const int echo = 7;

// Chân servo
const int servoPin = 11;

// Góc servo
#define GOC_DONG 0
#define GOC_MO 110

// Biến điều khiển
Servo myservo;
unsigned long autoMillis = 0;
bool autoTrigger = false;

void setup() {
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  myservo.attach(servoPin);
  myservo.write(GOC_DONG); // Servo ở trạng thái đóng ban đầu
}

void loop() {
  long duration;
  int distance;

  // Phát xung từ chân trig
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  // Đo thời gian Echo
  duration = pulseIn(echo, HIGH);
  distance = duration * 0.034 / 2; // Tính khoảng cách theo cm

  Serial.print("Khoảng cách: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Nếu khoảng cách nhỏ hơn 10cm thì mở nắp
  if (distance > 0 && distance < 10 && !autoTrigger) {
    myservo.write(GOC_MO);
    autoTrigger = true;
    autoMillis = millis();
  }

  // Sau 2s đóng lại
  if (autoTrigger && millis() - autoMillis >= 2000) {
    myservo.write(GOC_DONG);
    autoTrigger = false;
  }

  delay(100); // Giảm tần suất đo để tránh nhiễu
}
