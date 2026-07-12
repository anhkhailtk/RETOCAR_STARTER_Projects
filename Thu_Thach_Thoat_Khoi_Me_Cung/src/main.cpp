#include <Arduino.h>
#include <ESP32Servo.h>
#include <BanhXe.h>
// Quét mã QR ở đầu sách để biết cách tạo thư viện BanhXe.h
const int trigPin = 18;         // Pin Trigger của cảm biến siêu âm
const int echoPin = 5;          // Pin Echo của cảm biến siêu âm
const int servoPin = 19;        // Pin kết nối Servo
const int motorPinPWM_A = 25;   // PWM tốc độ động cơ A
const int motorPinHuong_A = 26; // Điều khiển hướng động cơ A
const int motorPinPWM_B = 32;   // PWM tốc độ động cơ B
const int motorPinHuong_B = 33; // Điều khiển hướng động cơ B
enum Trang_Thai
{
  TIEN,
  DUNG,
  KIEM_TRA,
  RE_TRAI,
  RE_PHAI
};
Trang_Thai trangThaiHienTai = TIEN;                   // Khởi đầu với tiến
float distanceLeft = 0;                               // Khoảng cách bên trái
float distanceRight = 0;                              // Khoảng cách bên phải
Servo coRobot;                                        // Tạo đối tượng Servo cho cổ robot
BanhXe banhXeTrai(motorPinPWM_A, motorPinHuong_A, 0); // Tạo đối tượng cho bánh xe trái
BanhXe banhXePhai(motorPinPWM_B, motorPinHuong_B, 1); // Tạo đối tượng cho bánh xe phải
void robotDiChuyen(int tocDo, int huong)
{
  if (huong == 0)
  { // Tiến thẳng
    banhXeTrai.quay(tocDo);
    banhXePhai.quay(tocDo);
  }
  else if (huong == 1)
  { // Rẽ trái
    banhXeTrai.quay(tocDo);
    banhXePhai.quay(-tocDo);
  }
  else if (huong == 2)
  { // Rẽ phải
    banhXeTrai.quay(-tocDo);
    banhXePhai.quay(tocDo);
  }
}
void robotDungLai()
{
  banhXeTrai.quay(0);
  banhXePhai.quay(0);
}
float doKhoangCach()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  uint32_t duration = pulseIn(echoPin, HIGH, 25000); // Đợi tối đa 25ms (tương đương khoảng cách ~4.3m) để tránh treo nếu không có phản hồi
  if (duration == 0)
    return NAN; // timeout
  // sound speed ~ 0.0343 cm/us, round trip, divide by 2
  return (duration * 0.0343f) / 2.0f;
}
void setup()
{
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  coRobot.attach(servoPin); // Gắn Servo vào pin đã định
  coRobot.write(90);        // Đặt Servo ở vị trí trung tâm (90 độ)
  delay(3000);              // Đợi 1 giây để Servo ổn định
}
void loop()
{
  switch (trangThaiHienTai)
  {
  case TIEN:
    Serial.println("Trang thai: TIEN");
    robotDiChuyen(200, 0); // Tiến thẳng với tốc độ tối đa
    // Nếu khoảng cách nhỏ hơn 20 cm, chuyển sang trạng thái dừng
    if (doKhoangCach() < 20)
    { // Nếu gặp vật cản trong khoảng 20 cm
      trangThaiHienTai = DUNG;
    }
    break;
  case DUNG:
    Serial.println("Trang thai: DUNG");
    robotDungLai();
    delay(1000); // Dừng lại 1 giây để quan sát
    trangThaiHienTai = KIEM_TRA;
    break;
  case KIEM_TRA:
    Serial.println("Trang thai: KIEM_TRA");
    coRobot.write(180); // Xoay cổ sang trái
    delay(500);
    distanceLeft = doKhoangCach(); // Đo khoảng cách bên trái
    coRobot.write(0);            // Xoay cổ sang phải
    delay(500);
    distanceRight = doKhoangCach(); // Đo khoảng cách bên phải
    coRobot.write(90);
    delay(500); // Quay lại vị trí trung tâm
    Serial.print("Khoang cach trai: ");
    Serial.print(distanceLeft);
    Serial.print(" cm, Khoang cach phai: ");
    Serial.print(distanceRight);
    Serial.println(" cm");
    if (distanceLeft > distanceRight)
    {
      trangThaiHienTai = RE_TRAI; // Rẽ trái nếu bên trái trống hơn
    }
    else
    {
      trangThaiHienTai = RE_PHAI; // Rẽ phải nếu bên phải trống hơn
    }
    break;
  case RE_TRAI:
    Serial.println("Trang thai: RE_TRAI");
    robotDiChuyen(200, 1);   // Rẽ trái với tốc độ tối đa
    delay(500);             // Rẽ trong 1 giây
    trangThaiHienTai = TIEN; // Quay lại trạng thái tiến thẳng
    break;
  case RE_PHAI:
    Serial.println("Trang thai: RE_PHAI");
    robotDiChuyen(200, 2);   // Rẽ phải với tốc độ tối đa
    delay(500);             // Rẽ trong 1 giây
    trangThaiHienTai = TIEN; // Quay lại trạng thái tiến thẳng
    break;
  }
  delay(10);
}
