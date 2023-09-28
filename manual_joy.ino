#include <Servo.h>
#define joyX1 A0
#define joyY1 A1
#define joyX2 A2
#define joyY2 A3
const int servopin1 = 3; //servo1
const int servopin2 = 5; //servo2
const int servopin3 = 6; //servo3
const int servopin4 = 9; //base
int angle1 = 0;
int angle2 = 0;
int angle3 = 0; 
int angleBase = 0;

Servo servo1, servo2, servo3, servoBase;
void setup() {
  Serial.begin(9600);
  //Serial.begin(9600);
  servo1.attach(servopin1);
  servo2.attach(servopin2);
  servo3.attach(servopin3);
  servoBase.attach(servopin4);

  servo1.write(0);
  servo2.write(0);
  servo3.write(0);
  servoBase.write(0);
}
 
void loop() {
  // put your main code here, to run repeatedly:
  int xValue1 = analogRead(joyX1);
  int yValue1 = analogRead(joyY1);
  int xValue2 = analogRead(joyX2);
  int yValue2 = analogRead(joyY2);
 
  //print the values with to plot or view
  Serial.print(xValue1);
  Serial.print("\t");
  Serial.println(yValue1);

  //int degreeX = map(xValue, 0, 1023, 0, 180);
  //int degreeY = map(yValue, 0, 1023, 0, 180);
  int degreeX = 10;
  int degreeY = 10;
  
  if (xValue1 > 512){ // right
    angleBase = angleBase + degreeX;
  }
  if (xValue1 < 512){ // left
    angleBase = angleBase - degreeX;
  }
  if (yValue1 > 512){ // forward
    angle1 = angle1 - degreeY; // lower
    angle2 = angle2 + degreeY; 
    angle3 = angle3 + degreeY;
  }
  if (yValue1 < 512){ // backward
    angle1 = angle1 + degreeY;
    angle2 = angle2 - degreeY;
    angle3 = angle3 - degreeY;
  }
  // joystick 2
  if (yValue2 > 512){ // up
    angle1 = angle1 + degreeY;
    angle2 = angle2 - degreeY;
    angle3 = angle3 + degreeY;
  } 
  if (yValue2 < 512){ // down
    angle1 = angle1 - degreeY;
    angle2 = angle2 + degreeY;
    angle3 = angle3 + degreeY;
  }
  servo1.write(angle1);
  servo2.write(angle2);
  servo3.write(angle3);
  servoBase.write(angleBase);
  delay(10);
}
