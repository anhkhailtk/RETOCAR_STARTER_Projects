#include "BanhXe.h"
#include <Arduino.h>

BanhXe::BanhXe(int pwm, int phu, int channel)
{
    chanPwm = pwm;
    chanPhu = phu;
    pwmChannel = channel;
    ledcSetup(pwmChannel, 5000, 8);     // Cài đặt kênh PWM với tần số 5kHz và độ phân giải 8 bit
    ledcAttachPin(chanPwm, pwmChannel); // Gắn chân PWM vào kênh PWM đã thiết lập
    pinMode(chanPhu, OUTPUT);           // Đặt chân phụ làm OUTPUT
}
void BanhXe::quay(int tocDo)
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
void BanhXe::tienThang(int tocDo)
{
    quay(tocDo);
}

void BanhXe::dungLai()
{
    quay(0);
}