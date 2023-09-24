#include <Servo.h>

Servo myservo;
int servoPin = 6;
int PB_1 = 2;
int PB_2 = 4;
int currentAngle = 0; // variable untuk menyimpan nilai sudut terbaru

void setup() {
  Serial.begin(9600);
  myservo.attach(servoPin);
  pinMode(PB_1, INPUT);
  pinMode(PB_2, INPUT);
  myservo.write(0);
}

void loop() {
  rotate(PB_1, 10);
  rotate(PB_2, -10);
}
void rotate(int buttonPin, int increment) {
  int buttonState = digitalRead(buttonPin); // Read the button state

  if (buttonState == HIGH) {
    currentAngle = currentAngle + increment;
    int currentRead = myservo.read() + increment;
    if (currentRead > 180){
      currentRead = 180;
    }
    else if (currentRead < 0){
      currentRead = 0;
    }
    // 
    Serial.print("Sudut (derajat): ");
    Serial.println(currentRead);
  }
  myservo.write(currentAngle);
  delay(50); 
}