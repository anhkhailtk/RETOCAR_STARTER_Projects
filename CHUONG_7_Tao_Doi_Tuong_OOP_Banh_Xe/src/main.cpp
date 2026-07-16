#include <Arduino.h>
class BanhXe
{
private:
  int chanPwm;    // Chân cắm PWM để điều khiển tốc độ
  int chanPhu;    // Chân cắm phụ để điều khiển hướng quay (ví dụ: tiến/lùi)
  int pwmChannel; // Kênh PWM để điều khiển tốc độ
public:
  BanhXe(int pwm, int phu, int channel)
  {
    chanPwm = pwm;
    chanPhu = phu;
    pwmChannel = channel;
    ledcSetup(pwmChannel, 5000, 8);     // Cài đặt kênh PWM với tần số 5kHz và độ phân giải 8 bit
    ledcAttachPin(chanPwm, pwmChannel); // Gắn chân PWM vào kênh PWM đã thiết lập
    pinMode(chanPhu, OUTPUT);           // Đặt chân phụ làm OUTPUT
  }
  void quay(int tocDo)
  {
    if (tocDo > 0)
    {
      digitalWrite(chanPhu, LOW);
      ledcWrite(pwmChannel, tocDo); // tocDo dương,sử dụng giá trị trực tiếp để điều khiển tốc độ
    }
    else if (tocDo < 0)
    {
      digitalWrite(chanPhu, HIGH);
      ledcWrite(pwmChannel, 255 + tocDo); // tocDo âm, nên cộng với 255 để có giá trị PWM phù hợp
    }
    else
    {
      digitalWrite(chanPhu, LOW);
      ledcWrite(pwmChannel, 0); // Dừng động cơ khi tocDo bằng 0
    }
  }
};

BanhXe banhTrai(25, 26, 0); // Khởi tạo bánh xe trái với chân PWM 25, chân phụ 26, kênh PWM 0
BanhXe banhPhai(32, 33, 1); // Khởi tạo bánh xe phải với chân PWM 32, chân phụ 33, kênh PWM 1

void setup()
{
  Serial.begin(9600);
  delay(1000); // Đợi 1 giây trước khi bắt đầu
}
void loop()
{
  banhTrai.quay(200);  // Quay bánh xe trái với tốc độ 200 (dương)
  banhPhai.quay(200);  // Quay bánh xe phải với tốc độ 200 (dương)
  delay(5000);
  banhTrai.quay(0); 
  banhPhai.quay(0);    // Dừng cả hai bánh xe
  delay(2000);         // Đợi 2 giây
  banhTrai.quay(-200); // Quay bánh xe trái với tốc độ -200 (âm)
  banhPhai.quay(-200); // Quay bánh xe phải với tốc độ -200 (âm)
  delay(5000);         // Quay trong 2 giây
  banhTrai.quay(0); 
  banhPhai.quay(0);    // Dừng cả hai bánh xe
  delay(2000);         // Đợi 2 giây
}
