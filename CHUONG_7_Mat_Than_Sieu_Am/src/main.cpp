#include <Arduino.h>
#include <ESP32Servo.h> // Sử dụng thư viện (Lớp có sẵn)
Servo coRobot;          // Khai báo ĐỐI TƯỢNG từ LỚP Servo
const int trigPin = 18;
const int echoPin = 5;
const int redPin = 13;
const int greenPin = 14;
void setup()
{
  Serial.begin(9600);
  // Sử dụng PHƯƠNG THỨC của đối tượng để điều khiển
  coRobot.attach(19);       // Gắn Servo vào chân GPIO 19
  pinMode(trigPin, OUTPUT); // Cấu hình chân trigPin là OUTPUT
  pinMode(echoPin, INPUT);  // Cấu hình chân echoPin là INPUT
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
}
float doKhoangCach() // Hàm đo khoảng cách bằng cảm biến siêu âm HC-SR04
{
  // Gửi 1 xung tín hiệu siêu âm từ chân trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Đo thời gian phản hồi từ chân echoPin
  long duration = pulseIn(echoPin, HIGH);
  // Tính toán khoảng cách (Số thực - float)
  return duration * 0.034 / 2;
}
void loop()
{
  for (int goc = 0; goc <= 180; goc += 45)
  {
    coRobot.write(goc); // Xoay cổ Robot
    delay(500);
    float kc = doKhoangCach(); // Biến cục bộ để lưu khoảng cách đo được
    if(kc < 20)
    {
      digitalWrite(redPin, LOW);
      digitalWrite(greenPin, HIGH);
      Serial.print("Khoang cach be: ");
      Serial.println(kc);
    }
    else
    {
      digitalWrite(redPin, HIGH);
      digitalWrite(greenPin, LOW);
      Serial.print("Khoang cach lon: ");
      Serial.println(kc);
    }
  }
}
