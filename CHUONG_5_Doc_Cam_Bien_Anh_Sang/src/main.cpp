#include <Arduino.h> // Thư viện chính cho lập trình Arduino

int ldrPin = 36; // GPIO 36 cho LDR
int redPin = 13; // GPIO 13 cho Red LED
int greenPin = 14; // GPIO 14 cho Green LED
int bluePin = 27; // GPIO 27 cho Blue LED
int lightThreshold = 2000; // Ngưỡng ánh sáng để bật/tắt đèn

void setup() {
  Serial.begin(9600);
  pinMode(ldrPin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}
void loop() {
  int lightLevel = analogRead(ldrPin); // Đọc mức độ ánh sáng từ LDR
  Serial.print("Light Level: ");
  Serial.println(lightLevel);
  if (lightLevel < lightThreshold) {
    // Trời tối - bật đèn trắng
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, LOW);
    Serial.println("Trời tối! Bật đèn trắng.");
  } else {
    // Trời sáng - tắt đèn
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, HIGH);
    digitalWrite(bluePin, HIGH);
    Serial.println("Trời sáng! Tắt đèn.");
  }
  delay(1000); // Kiểm tra mỗi giây
}