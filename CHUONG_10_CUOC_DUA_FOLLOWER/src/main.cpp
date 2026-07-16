#include <Arduino.h>
#include "BanhXe.h"

const int sensorLeftPin = 23;   // Cảm biến trái
const int sensorCenterPin = 17; // Cảm biến giữa
const int sensorRightPin = 16;  // Cảm biến phải
const int motorPinPWM_A = 25;   // PWM tốc độ động cơ A
const int motorPinHuong_A = 26; // Điều khiển hướng động cơ A
const int motorPinPWM_B = 32;   // PWM tốc độ động cơ B
const int motorPinHuong_B = 33; // Điều khiển hướng động cơ B

const int tocDoChay = 150; // Tốc độ đi thẳng
const int tocDoRe = 200;   // Tốc độ rẽ

enum RobotState {
  ON_TRACK,    // Đang ở giữa vạch
  SLIGHT_LEFT,  // Lệch trái nhẹ
  SLIGHT_RIGHT, // Lệch phải nhẹ
  LOST         // Mất dấu vạch
};

BanhXe banhXeTrai(motorPinPWM_A, motorPinHuong_A, 0);
BanhXe banhXePhai(motorPinPWM_B, motorPinHuong_B, 1);

void setup() {
  Serial.begin(9600);
  pinMode(sensorLeftPin, INPUT);
  pinMode(sensorCenterPin, INPUT);
  pinMode(sensorRightPin, INPUT);
}

void loop() {
  bool sensorLeft = digitalRead(sensorLeftPin);
  bool sensorCenter = digitalRead(sensorCenterPin);
  bool sensorRight = digitalRead(sensorRightPin);
  
  RobotState state; // Xác định trạng thái robot dựa trên cảm biến
  
  if (sensorCenter == LOW && sensorLeft == HIGH && sensorRight == HIGH) {
    state = ON_TRACK; // Đang ở giữa vạch
  } else if (sensorLeft == LOW) {
    state = SLIGHT_LEFT; // Lệch trái
  } else if (sensorRight == LOW) {
    state = SLIGHT_RIGHT; // Lệch phải
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