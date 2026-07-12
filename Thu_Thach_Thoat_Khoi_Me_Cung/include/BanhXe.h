class BanhXe
{
private:
    int chanPwm;    // Chân cắm PWM để điều khiển tốc độ
    int chanPhu;    // Chân cắm phụ để điều khiển hướng quay (ví dụ: tiến/lùi)
    int pwmChannel; // Kênh PWM để điều khiển tốc độ
public:
    BanhXe(int pwm, int phu, int channel);
    void quay(int tocDo);
};
