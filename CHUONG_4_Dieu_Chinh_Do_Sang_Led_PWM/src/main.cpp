#include <Arduino.h>
const int ledPin = 13; // Chân LED Đỏ
void setup()
{
  // Cài đặt PWM cho chân LED
  ledcSetup(0, 5000, 8);    // Kênh 0, tần số 5kHz, độ phân giải 8 bit (độ mịn = 256 nấc)
  ledcAttachPin(ledPin, 0); // Gắn chân LED vào kênh PWM 0
}
void loop()
{
  // Hiệu ứng "Nhịp thở Robot"
  for (int dutyCycle = 0; dutyCycle <= 255; dutyCycle++)
  {                          // Sáng dần
    ledcWrite(0, dutyCycle); // Ghi giá trị PWM vào kênh 0
    delay(10);               // Tăng độ sáng mỗi 10ms
  }
  for (int dutyCycle = 255; dutyCycle >= 0; dutyCycle--)
  {                          // Mờ dần
    ledcWrite(0, dutyCycle); // Ghi giá trị PWM vào kênh 0
    delay(10);               // Giảm độ sáng mỗi 10ms
  }
}

