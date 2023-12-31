#include <Servo.h>
#define joyX1 A0
#define joyY1 A1
#define joyX2 A2
#define joyY2 A3
const int switchPin = 2;
const int servopin1 = 9; //servo1 (forward-backward)
const int servopin2 = 10; //servo2 (up-down)
const int servopin4 = 6; //base
const int servopin5 = 11; //gripper
const int trigPin = 4;
const int echoPin = 5;

int angle1, angle2, angleBase, moveTo, safezone = 0;
int detected_distance = 10;

int xValue1 = 0; // To store value of the X axis
int yValue1 = 0;
int xValue2 = 0;
int yValue2 = 0;

Servo servo1, servo2, servoBase, gripper;

int lastButtonState = LOW; 
bool isManual = true;
int modeState = 0;
void setup() {
  Serial.begin(9600);
  servo1.attach(servopin1);
  servo2.attach(servopin2);
  servoBase.attach(servopin4);
  gripper.attach(servopin5);
  pinMode(switchPin, INPUT_PULLUP);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  servo1.write(45);
  servo2.write(45);
  servoBase.write(20);
  gripper.write(90);
  
}

void loop() {
  // SWITCH MODE
  int switchPosition = digitalRead(switchPin);

  // Check if the switch is in the auto position
  if (switchPosition == LOW) {
    isManual = false; // Set to auto mode
  } else {
    isManual = true;  // Set to manual mode
  }
  
  if (isManual) {
    manualMode();
  } else {
    autoMode();
  }
  
}
// --------- MANUAL FUNCTIONS --------
void manualMode(){
  xValue1 = analogRead(joyX1);
  yValue1 = analogRead(joyY1);
  xValue2 = analogRead(joyX2);
  yValue2 = analogRead(joyY2);
 
  //print the values with to plot or view
  Serial.print(xValue1);
  Serial.print("  ");
  Serial.print(yValue1);
  Serial.print("  ");
  Serial.print(xValue2);
  Serial.print("  ");
  Serial.println(yValue2);

  int degreeX = 5;
  int degreeY = 5;
  int centmin = 515;
  int centplus = 400;
  int gripperclose = 120;
  int gripperopen = 90;

  // servo1 (for-ba): 20 (nearest) - 160 (furthest, set to 90).
  // servo1 (up-do): 0 (upmost) - 90 (downmost) 
  // gripper: 90 (open) & 180 (close) 
  // base
  if (xValue1 > centmin){ // right
    angleBase = angleBase + degreeX;
  }
  else if (xValue1 < centplus){ // left
    angleBase = angleBase - degreeX;
  }
  else if (yValue1 > centmin){ // forward
    angle1 = angle1 + degreeY;
    if (angle1 > 110) {
      angle1 = 110;
    }
  }
  else if (yValue1 < centplus){ // backward
    angle1 = angle1 - degreeY;
    if (angle1 < 20) {
      angle1 = 20;
    }
  }
  // joystick 2
  if (yValue2 > centmin){ // up
    angle2 = angle2 - degreeY; // the more it goes to 0, the upper it lifts
    if (angle1 < 20) {
      angle1 = 20;
    }
  } 
  else if (yValue2 < centplus){ // down
    angle2 = angle2 + degreeY;
    if (angle2 > 90) {
      angle2 = 90;
    }
  }
  else if (xValue2 > centmin || xValue2 < centplus){ // ready to pickup/release
    gripper.write(gripperopen);
  }
  else if (xValue2 > centplus && xValue2 < centmin){ // grip
    gripper.write(gripperclose);
  }

  servo1.write(angle1);
  servo2.write(angle2);
  servoBase.write(angleBase);
  delay(50); 
}

void autoMode() {
  int readBase = servoBase.read();

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  long distance = (duration * 0.0342) / 2;

  // Check for target detection within 5 cm
  if (distance < detected_distance) {
    stopServos();
    rescue();
    delay(1000); // Delay for stability (adjust as needed).

  } else {
    // Move servos to 120 degrees until a target is detected
    for (int i = 0; i <= 120; i++) {

      // Check for target detection
      if (distance < detected_distance) {
        // If the target is detected stop scanning and perform rescue.
        stopServos();
        rescue();
        delay(1000); // Delay for stability (adjust as needed).
        break; // Exit the scanning loop.
      }
      servo1.write(i);

      delay(20); // Adjust the delay as needed to control servo speed.
    }
    if (servo1.read() == 120 && servoBase.read() == 20 && distance > detected_distance) {
      servoBase.write(90);
    }
    else if (servo1.read() == 120 && servoBase.read() == 90 && distance > detected_distance) {
      servoBase.write(45);
    }
    else if (servo1.read() == 120 && servoBase.read() == 45 && distance > detected_distance) {
      servoBase.write(20);
    }
    else if (servo1.read() == 120 && servoBase.read() != (20,45,90) && distance > detected_distance) {
      servoBase.write(20);
    }
  }
  delay(100);
}
void stopServos() {
  servo1.write(servo1.read()); // Stop servo1.
  servo2.write(servo2.read()); // Stop servo2.
}
void rescue() {
  int gripAngle = 20; // preparing to grip the target (after scanning)
  int liftAngle = 180;
  int putDown1 = 0; // angle of servo 1 when placing the target down
  int putDown2 = 20; 
  int moveFrom = servoBase.read();
  int back1 = 45;

  if (moveFrom == 20) {
    // gripAngle = ;
    safezone = 25; // safe zone 1
    putDown1 = 20;
    moveTo = 90; //from safe zone 1 to danger zone 2
  }
  if (moveFrom == 90) {
    // gripAngle = ;
    safezone = 65;
    putDown1 = 20;
    moveTo = 45;
  }
  if (moveFrom == 45) {
    // gripAngle = ;
    safezone = moveFrom;
    putDown1 = 45;
    moveTo = 20;
  }

  // GRIP
  gripper.write(90); // ready to grip
  delay(500);
  servo1.write(servo1.read()); // move a bit forward, prepare to grip
  // servo2.write(servo2.read()); //unnecessary
  delay(1000);
  gripper.write(10); // taken
  delay(1000);

  // LIFT
  servo2.write(liftAngle);
  delay(1000);

  // ROTATE TOWARD SAFE ZONE
  servoBase.write(safezone);
  delay(1000);

  // PLACE
  servo1.write(putDown1);
  servo2.write(putDown2);
  delay(1000);
  gripper.write(90); // Open
  delay(1000);
  servo1.write(back1); // move backward, prepare to move
  delay(500);

  //MOVE
  servoBase.write(moveTo);
  delay(1000);
}
/*
void searching() {
  int servoRead =  servoBase.read();
  if ( servoRead == 0) {
    servoBase.write(90);
  }
  if (servoRead == 90) {
    servoBase.write(45);
  }
  if (servoRead == 45) {
    servoBase.write(0);
  }
  else if(servoRead != 0 || servoRead != 45 || servoRead != 90 ){
    servoBase.write(0);
  }
}
*/
