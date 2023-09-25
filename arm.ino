// consider usingn potentiometer
#include <Servo.h>

Servo servo1, servo2, servo3, servoBase, gripper; 
int servoPin[] = {3,5,6,9,10};
int buttonPin[] = {2,4,7,8,12,13};
const int switchPin = 10; // NOT PUSHBUTTON
const int trigPin = A0;  
const int echoPin = A1; 
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
  gripper.attach(servoPin[4]);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // servo1.write(0); //set sudut awal
  // servo2.write(0); 
  // servo3.write(0);
  // servoBase.write(0);
  // gripper.write(0);
  
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
  int readAngle1 = servo1.read();
  int readAngle2 = servo2.read();
  int readAngle3 = servo3.read();
  int readBase = servoBase.read();
  int readGrip = gripper.read();
  
  // set base servo to face toward danger zone 1 first
  // scanning mechanism:
  // if the servo already faces certain zone but no object detected, move to another zone
  // read servo + conditioning distance from sensor
  
  servoBase.write(0);
  servo1.write();
  servo2.write();
  servo3.write();
  gripper.write();
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0342)/2;

  // ZONE 1
  if (distance < 5 && readBase == 0){
    // give command to gripper
    rescue(90);
    searching(90);
  } else if (readAngle > 120 && readBase == 0){
    searching(45);
  }
  // ZONE 2
  if (distance < 5 && readBase == 90){
    // give command to gripper
    rescue(90);
  }
  
  delay(100);
}
void rescue(int degree){
  // GRIP
  gripper.write(); // hold
  servo1.write();
  servo2.write();
  servo3.write();
  delay(50);
  // LIFT
  servo1.write();
  servo2.write();
  servo3.write();
  // MOVE
  servoBase.write(degree);
  // PLACE
  servo1.write();
  servo2.write();
  servo3.write();
  gripper.write(); //open
  delay(1000);
}
void searching(int setpoint){
  servoBase.write(setpoint);
  servo1.write();
  servo2.write();
  servo3.write();
  gripper.write();
}
