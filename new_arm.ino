// consider usingn potentiometer
#include <Servo.h>

Servo servo1, servo2, servo3, servoBase, gripper; 
int servoPin[] = {3,5,6,9,10};
// int buttonPin[] = {2,4,7,8,12,13};
const int potpin1 = A0;
const int potpin2 = A1;
const int potpin3 = A2;
const int potpin4 = A3;
//const int pin_left = 2;
//const int pin_right = 4;
const int grip_pin = 12;
const int switchPin = 11; // NOT PUSHBUTTON
const int trigPin = 7;  
const int echoPin = 8; 

int angle1, angle2, angle3, angle4;
int baseAngle = 0;
bool isManual = true;
bool lastButtonState = LOW;

void setup() {
  //for (int i = 0; i < 6;i++){ // forward, backward, left, right, up, down
    //pinMode(buttonPin[i], INPUT);
    //}
  pinMode(grip_pin, INPUT);
  pinMode(switchPin, INPUT);
  servo1.attach(servoPin[0]);
  servo2.attach(servoPin[1]);
  servo3.attach(servoPin[2]);
  servoBase.attach(servoPin[3]);
  gripper.attach(servoPin[4]);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  //set sudut awal
  servo1.write(0); 
  servo2.write(0); 
  servo3.write(0);
  servoBase.write(0);
  gripper.write(0);
  
}

void loop() {
  // SWITCH MODE
  //if (switchState == HIGH) {
    //manualmode();
  //}

  // EVALUATE!!!!!!!!!!
  int buttonState = digitalRead(switchPin);

  if (buttonState == HIGH && lastButtonState == LOW) {
    isManual = !isManual; //becomes automatic?
  }
  lastButtonState = buttonState;
  
  if (isManual) {
    manualMode();
  } //else {
    //autoMode();
  //}
  
}
// --------- MANUAL FUNCTIONS --------
void manualMode(){
  
  // MANUAL TASKS
  // control individual servos
  int potentio1 = analogRead(potpin1);
  int potentio2 = analogRead(potpin2);
  int potentio3 = analogRead(potpin3);
  int potentio4 = analogRead(potpin4);
  // int left = digitalRead(pin_left);
  // int right = digitalRead(pin_right);
  int gripping = digitalRead(grip_pin);
  
  angle1 = map(potentio1, 0, 1023, 0, 180);
  angle2 = map(potentio2, 0, 1023, 0, 180);
  angle3 = map(potentio3, 0, 1023, 0, 180);
  angle4 = map(potentio4, 0, 1023, 0, 180);
  

  if (gripping == 1){
    gripper.write(90);
  }
  else if (gripping == 0){
    gripper.write(10);
  }
  
  servo1.write(angle1);
  servo2.write(angle2);
  servo3.write(angle3);
  servoBase.write(angle4);
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
  servo1.write(0);
  servo2.write(0);
  servo3.write(0);
  gripper.write(0);
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  long distance = (duration*.0342)/2;

  // while loop to add the angle gradually
  int max_angle = 120;
  int i = 0;
  while (i < max_angle){
    servo1.write(i);
    servo2.write(i);
    servo3.write(i);
    i++;
    if (distance < 5){
      i = 120;
    }
  }
  

  // ZONE 1
  if (distance < 5 && readBase == 0){
    // give command to gripper
    rescue(90);
    searching(90);
  } else if (distance > 10 && readBase == 0){ // no target found
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
  int gripAngle = 45;
  int liftAngle = 180;
  int liftPlace = 90;
  // GRIP
  gripper.write(90); // hold
  servo1.write(gripAngle);
  servo2.write(gripAngle);
  servo3.write(gripAngle);
  delay(50);
  // LIFT
  servo1.write(liftAngle);
  servo2.write(liftAngle);
  servo3.write(liftAngle);
  // MOVE
  servoBase.write(degree);
  // PLACE
  servo1.write(liftPlace);
  servo2.write(liftPlace);
  servo3.write(liftPlace);
  gripper.write(90); //open
  delay(1000);
}
void searching(int setpoint){
  servoBase.write(setpoint);
  servo1.write(10);
  servo2.write(10);
  servo3.write(10);
  gripper.write(90);
}
