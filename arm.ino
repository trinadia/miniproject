#include <Servo.h>

Servo servo1, servo2; servo3, servoBase; 
int servoPin[] = {3,5,6,9};
int buttonPin[] = {2,4,7,8,12,13};
const int switchPin = 10; // NOT PUSHBUTTON
const trigPin = A0;  
const echoPin = A1; 
int angle1, angle2, angle3 = 0;
int baseAngle = 0;

void setup() {
  for (int i = 0; i < 6;i++){ // forward, backward, left, right, up, down
    pinMode(buttonPin[i], INPUT);
    }
  pinMode(switchPin, INPUT);
  servo1.attach(servoPin[0]);
  servo2.attach(servoPin[1]);
  servo3.attach(servoPin[2]);
  servoBase.attach(servoPin[3]);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // servo1.write(0); //set sudut awal
  // servo2.write(0); 
  // servo3.write(0);
  // servoBase.write(0);
  
}

void loop() {
  // SWITCH MODE
  //if (switchState == HIGH) {
    //manualmode();
  //}
  
}
// --------- MANUAL FUNCTIONS --------
void manualMode(){
  /*
  MANUAL TASKS
  */
  int forward = digitalRead(buttonPin[0]);
  int backward = digitalRead(buttonPin[1]);
  int left = digitalRead(buttonPin[2]);
  int right = digitalRead(buttonPin[3]);
  int up = digitalRead(buttonPin[4]);
  int down = digitalRead(buttonPin[5]);

  // FORWARD
  if (forward == HIGH){
    angle1 = angle1 - 10;// CW, -
    angle2 = angle2 + 10; // CCW
    angle3 = angle3 + 10; // CCW
  }
  // BACKWARD
  if (backward == HIGH){
    angle1 = angle1 + 10;// CW, -
    angle2 = angle2 - 10; // CCW
    angle3 = angle3 - 10; // CCW
  }
  if (left == HIGH){
    baseAngle = baseAngle + 10;
  }
  if (right == HIGH){
    baseAngle = baseAngle - 10;
  }
  if (up == HIGH) {
    angle1 = angle1 + 10;// CW, -
    angle2 = angle2 + 10; // CCW
    angle3 = angle3 + 10; // CCW
  }
  if (down == HIGH) {
    angle1 = angle1 - 10;// CW, -
    angle2 = angle2 - 10; // CCW
    angle3 = angle3 - 10; // CCW
  }
  servo1.write(angle1);
  servo2.write(angle2);
  servo3.write(angle3);
  delay(50); 
}
void autoMode() {
  // set base servo to face toward danger zone 1
  // scanning mechanism:
  // if the servo already faces certain zone but no object detected, move to another zone
  // read servo + conditioning distance from sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0342)/2;

  if (distance < 5){
    // give command to gripper
    
  }
  delay(100);
}

// ---------------------------------
/*
void forward(int button){
  
  int buttonState = digitalRead(button); // Read the button state

  if (buttonState == HIGH) {
    angle1 = angle1 + 5;
    
    //int currentRead = myservo.read() + increment;
    //if (currentRead > 180){
      //currentRead = 180;
    //}
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
