#include <Arduino.h>
int left_motor_A = 25;  // Chân điều khiển động cơ trái
int left_motor_B = 26;  // Chân điều khiển động cơ trái
int right_motor_A = 32; // Chân điều khiển động cơ phải
int right_motor_B = 33; // Chân điều khiển động cơ phải

void chay(int toc_do, int huong)
{
  if (huong == 0)
  { // Tiến thẳng
    ledcWrite(0, toc_do);    ledcWrite(1, 0);
    ledcWrite(2, toc_do);    ledcWrite(3, 0);
  }
  else if (huong == 1)
  { // Rẽ trái
    ledcWrite(0, toc_do);    ledcWrite(1, 0);
    ledcWrite(2, toc_do / 2);    ledcWrite(3, 0);
  }
  else if (huong == 2)
  { // Rẽ phải
    ledcWrite(0, toc_do / 2);    ledcWrite(1, 0);
    ledcWrite(2, toc_do);    ledcWrite(3, 0);
  }
  else if (huong == 3)
  { // Quay đầu (U-turn)
    ledcWrite(0, toc_do);    ledcWrite(1, 0);
    ledcWrite(2, 0);    ledcWrite(3, toc_do);
    delay(1000);
    ledcWrite(0, 0);    ledcWrite(1, 0);
    ledcWrite(2, 0);    ledcWrite(3, 0);
  }
}

void dung()
{
  ledcWrite(0, 0);  ledcWrite(1, 0);
  ledcWrite(2, 0);  ledcWrite(3, 0);
}

// Chường trình trên ở trang trước
void setup()
{
  // Khởi tạo các chân điều khiển động cơ PWM
  ledcSetup(0, 1000, 8);// PWM cho động cơ trái A
  ledcSetup(1, 1000, 8);// PWM cho động cơ trái B
  ledcSetup(2, 1000, 8);// PWM cho động cơ phải A
  ledcSetup(3, 1000, 8);// PWM cho động cơ phải B
  ledcAttachPin(left_motor_A, 0);// Gắn chân điều khiển động cơ trái A vào kênh PWM 0
  ledcAttachPin(left_motor_B, 1);// Gắn chân điều khiển động cơ trái B vào kênh PWM 1
  ledcAttachPin(right_motor_A, 2);// Gắn chân điều khiển động cơ phải A vào kênh PWM 2
  ledcAttachPin(right_motor_B, 3);// Gắn chân điều khiển động cơ phải B vào kênh PWM 3
}

void loop()
{
  chay(160, 0); // Tiến thẳng với tốc độ tối đa
  delay(2000);  // Chạy trong 2 giây
  chay(160, 1); // Rẽ trái với tốc độ tối đa
  delay(2000);  // Rẽ trong 2 giây
  chay(160, 2); // Rẽ phải với tốc độ tối đa
  delay(2000);  // Rẽ trong 2 giây
  chay(160, 3); // Quay đầu (U-turn) với tốc độ tối đa
  dung();       // Dừng lại
  delay(10000);  // Dừng trong 2 giây
}




