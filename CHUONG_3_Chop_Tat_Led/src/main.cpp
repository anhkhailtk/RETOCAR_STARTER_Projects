#include <Arduino.h>
int led_trai_pin = 4; // Khai báo biến
int led_phai_pin = 2; // Khai báo biến
int thoi_gian_cho = 500;
void setup()
{
  pinMode(led_trai_pin, OUTPUT);
  pinMode(led_phai_pin, OUTPUT);
}
void loop()
{
  // Xe rẽ trái, nháy đèn trái, tắt đèn phải
  digitalWrite(led_phai_pin, LOW);
  digitalWrite(led_trai_pin, LOW);
  delay(thoi_gian_cho); // Đợi 0.5 giây
  digitalWrite(led_phai_pin, HIGH);
  digitalWrite(led_trai_pin, HIGH);
  delay(thoi_gian_cho); // Đợi 0.5 giây
}
