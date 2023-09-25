// consider usingn potentiometer
#include <Servo.h>

Servo servo1, servo2, servo3, servoBase, gripper; 
int servoPin[] = {3,5,6,9,10};
// int buttonPin[] = {2,4,7,8,12,13};
const int updown = A0;
const int leftright = A1;
const int forback = A2;
const int switchPin = 10; // NOT PUSHBUTTON
const int trigPin = 7;  
const int echoPin = 8; 
int angle1, angle2, angle3 = 0;
int baseAngle = 0;

void setup() {
  //for (int i = 0; i < 6;i++){ // forward, backward, left, right, up, down
    //pinMode(buttonPin[i], INPUT);
    //}
  
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
  
  // MANUAL TASKS
  int potentio1 = analogRead(updown);
  int potentio2 = analogRead(leftright);
  int potentio3 = analogRead(forback);

  angle1 = map(potentio1, 0, 1023, 0, 180);
  angle2 = map(potentio2, 0, 1023, 0, 180);
  angle3 = map(potentio3, 0, 1023, 0, 180);
  
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
