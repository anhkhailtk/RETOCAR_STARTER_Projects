#include <Arduino.h>
const int sensorLeftPin = 23;   // Mắt cảm biến bên trái
const int sensorCenterPin = 16; // Mắt cảm biến ở giữa
const int sensorRightPin = 17;  // Mắt cảm biến bên phải

void setup()
{
  // Khởi động Serial Monitor
  Serial.begin(9600);

  // Cấu hình chân cảm biến là đầu vào
  pinMode(sensorLeftPin, INPUT);
  pinMode(sensorCenterPin, INPUT);
  pinMode(sensorRightPin, INPUT);
}
void loop()
{
  bool sensorValues[3];
  sensorValues[0] = digitalRead(sensorLeftPin);
  sensorValues[1] = digitalRead(sensorCenterPin);
  sensorValues[2] = digitalRead(sensorRightPin);
  for (int i = 0; i < 3; i++)
  {
    Serial.print("Sensor ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(sensorValues[i] ? "HIGH" : "LOW");
  }
  if (sensorValues[0] == false && sensorValues[1] == true && sensorValues[2] == false)
  {
    Serial.println("Robot đang đi thẳng.");
  }
  else if (sensorValues[0] == false && sensorValues[1] == true && sensorValues[2] == true)
  {
    Serial.println("Robot đang lệch trái.");
  }
  else if (sensorValues[2] == false && sensorValues[1] == true && sensorValues[0] == true)
  {
    Serial.println("Robot đang lệch phải.");
  }
  else
  {
    Serial.println("Robot đang lạc đường.");
  }
  delay(100);
}
