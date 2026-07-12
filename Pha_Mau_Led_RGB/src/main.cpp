#include <Arduino.h>
int redPin = 13;   // Biến toàn cục gán chân GPIO cho màu đỏ
int greenPin = 14; // Biến toàn cục gán chân GPIO cho màu xanh lá
int bluePin = 27;  // Biến toàn cục gán chân GPIO cho màu xanh dương
void phaMau(uint8_t do_, uint8_t xanhLa, uint8_t xanhDuong)
{
  // Thiết lập giá trị PWM cho từng màu
  ledcWrite(0, do_);       // Kênh 0 cho red color
  ledcWrite(1, xanhLa);    // Kênh 1 cho green color
  ledcWrite(2, xanhDuong); // Kênh 2 cho blue color
}
void setup()
{
  // Khởi tạo PWM cho các chân LED RGB
  ledcSetup(0, 5000, 8);      // Kênh 0, tần số 5kHz, độ phân giải 8 bit
  ledcSetup(1, 5000, 8);      // Kênh 1, tần số 5kHz, độ phân giải 8 bit
  ledcSetup(2, 5000, 8);      // Kênh 2, tần số 5kHz, độ phân giải 8 bit
  ledcAttachPin(redPin, 0);   // Gắn chân đỏ vào kênh 0
  ledcAttachPin(greenPin, 1); // Gắn chân xanh lá vào kênh 1
  ledcAttachPin(bluePin, 2);  // Gắn chân xanh dương vào kênh 2
  delay(1000);                // Đợi 1 giây trước khi bắt đầu thay đổi màu sắc
}
void loop()
{
  // Thay đổi màu sắc của đèn LED RGB
  int time_delay = 1000; // Biến cục bộ gán thời gian chờ
  phaMau(0, 255, 255);   // Màu đỏ
  delay(time_delay);
  phaMau(255, 0, 255); // Màu xanh lá
  delay(time_delay);
  phaMau(255, 255, 0); // Màu xanh dương
  delay(time_delay);
  phaMau(0, 0, 255); // Màu vàng
  delay(time_delay);
  phaMau(0, 255, 0); // Màu tím
  delay(time_delay);
  phaMau(255, 0, 0); // Màu cyan
  delay(time_delay);
}
