/*
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
*/
#include <Servo.h>

Servo servo1, servo2; servo3, servoBase; 
int servoPin[] = {3,5,6,9};
int buttonPin[] = {2,4,7,8,12,13};
float angle1, angle2, angle3;

void setup() {
  for (int i = 0; i < 6;i++){
    pinMode(buttonPin[i], INPUT);
    }
  // forward, backward, left, right, up, down
  servo1.attach(servoPin[0]);
  servo2.attach(servoPin[1]);
  servo3.attach(servoPin[2]);
  servoBase.attach(servoPin[3]);
  // servo1.write(0); //set sudut awal
  // servo2.write(0); 
  // servo3.write(0);
  // servoBase.write(0);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  // forward();
  //
}
void forward(int button){
  
}
void backward(int button){
  
}
void left(int button){
  
}
void right(int button){
  
}
void up(int button){
  
}
void down(int button){
  
}
//---------------------------------------------------------
/*
MANUAL PROGRAM
variables: 
l1 : length 1
l2 : length 2
l3 : length 3
angle1 : near-base servo
angle2 : middle servo
angle3 : near-end-effector servo

set intial position

input (with 2 buttons, up and down): 
- displacement in x
- displacement in y

------ pseudocode: ---------
void setup() {
  // use code from tugas no 4 for pushbutton input
  readAngle1 = servo.read(pinServo1,..); // reading servo's current angle
}
// CAUTION: angle for each servo must be different due to the different initial condition
// RECALL: inverse kinematics means it is end-effector-wise
void loop() {
  
}

void  front(float x){
  // displacement x to angle
  // angle1 = arccos(x/l1)
}
*/
