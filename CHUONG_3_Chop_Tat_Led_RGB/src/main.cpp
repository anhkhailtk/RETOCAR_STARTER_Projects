#include <Arduino.h>
int pinR = 27; // Chân Đỏ
int pinG = 14; // Chân Xanh lá
int pinB = 13; // Chân Xanh dương
void setup()
{
  pinMode(pinR, OUTPUT);
  pinMode(pinG, OUTPUT);
  pinMode(pinB, OUTPUT);
  // Tắt hết đèn lúc khởi động (Dương chung nên xuất HIGH là Tắt)
  digitalWrite(pinR, HIGH);
  digitalWrite(pinG, HIGH);
  digitalWrite(pinB, HIGH);
}
void loop()
{
  digitalWrite(pinB, LOW); // SẴN SÀNG (Hiện màu Xanh lá)
  delay(1000);
  // digitalWrite(pinG, HIGH); // Tắt xanh lá
  // digitalWrite(pinR, LOW); // NGUY HIỂM (Hiện màu Đỏ)
  // delay(2000);
  // digitalWrite(pinR, HIGH); // Tắt đỏ
  // digitalWrite(pinB, LOW); // ĐANG SUY NGHĨ (Hiện màu Xanh dương)
  // delay(3000);
  // digitalWrite(pinB, HIGH); / / Tắt xanh dương
}
