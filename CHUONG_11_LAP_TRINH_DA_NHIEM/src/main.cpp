#include <Arduino.h>
#include "BanhXe.h"

const int sensorLeftPin = 23;   // Cảm biến trái
const int sensorCenterPin = 17; // Cảm biến giữa
const int sensorRightPin = 16;  // Cảm biến phải
const int motorPinPWM_A = 25;   const int motorPinHuong_A = 26;
const int motorPinPWM_B = 32;   const int motorPinHuong_B = 33;

const int tocDoChay = 150;      const int tocDoRe = 200;
const int left_led_pin = 2;     // Chân LED trái (GPIO 2)
const int right_led_pin = 4;    // Chân LED phải (GPIO 4)
unsigned long previousMillis = 0; // Biến lưu thời gian trước đó

enum RobotState {
  ON_TRACK,     // Đang ở giữa vạch
  SLIGHT_LEFT,  // Lệch trái nhẹ
  SLIGHT_RIGHT, // Lệch phải nhẹ
  LOST          // Mất dấu vạch
};

BanhXe banhXeTrai(motorPinPWM_A, motorPinHuong_A, 0);
BanhXe banhXePhai(motorPinPWM_B, motorPinHuong_B, 1);

void setup() {
  Serial.begin(9600);
  pinMode(sensorLeftPin, INPUT);  pinMode(sensorCenterPin, INPUT);
  pinMode(sensorRightPin, INPUT);
  pinMode(left_led_pin, OUTPUT);  pinMode(right_led_pin, OUTPUT);
}

void loop() {
  // Nhấp nháy led sau mỗi 500ms liên tục không dùng delay
  if (millis() - previousMillis >= 500) {
    digitalWrite(left_led_pin, !digitalRead(left_led_pin));
    digitalWrite(right_led_pin, !digitalRead(right_led_pin));
    previousMillis = millis();
  }

  bool sensorLeft = digitalRead(sensorLeftPin);
  bool sensorCenter = digitalRead(sensorCenterPin);
  bool sensorRight = digitalRead(sensorRightPin);

  RobotState state; // Xác định trạng thái robot dựa trên cảm biến

  if (sensorCenter == LOW && sensorLeft == HIGH && sensorRight == HIGH) {
    state = ON_TRACK; // Đang ở giữa vạch
  } else if (sensorLeft == LOW) {
    state = SLIGHT_LEFT; // Lệch trái nhẹ
  } else if (sensorRight == LOW) {
    state = SLIGHT_RIGHT; // Lệch phải phải
  } else {
    state = LOST; // Mất dấu vạch
  }

  switch (state) { // Hành động dựa trên trạng thái
    case ON_TRACK:
      banhXeTrai.tienThang(tocDoChay); // Tiến thẳng với tốc độ tối đa
      banhXePhai.tienThang(tocDoChay);
      break;

    case SLIGHT_LEFT:
      banhXeTrai.tienThang(0); // Rẽ trái nhẹ
      banhXePhai.tienThang(tocDoRe);
      break;

    case SLIGHT_RIGHT:
      banhXeTrai.tienThang(tocDoRe); // Rẽ phải nhẹ
      banhXePhai.tienThang(0);
      break;

    case LOST:
      banhXeTrai.dungLai(); // Dừng lại ngay lập tức
      banhXePhai.dungLai();
      break;
  }

  delay(10); // Thời gian phản hồi nhanh, có thể điều chỉnh nếu cần thiết
}