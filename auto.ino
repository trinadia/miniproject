#include <Servo.h>
//const int grip_pin = 2;
const int servopin1 = 3; //servo1
const int servopin2 = 5; //servo2
const int servopin3 = 6; //servo3
const int servopin4 = 9; //base
const int servopin5 = 10; //base
const int trigPin = 7;
const int echoPin = 8;

int angle1, angle2, angle3, angleBase, moveTo, safezone = 0;
int detected_distance = 5;

Servo servo1, servo2, servo3, servoBase, gripper;
void setup() {
  Serial.begin(9600);
  servo1.attach(servopin1);
  servo2.attach(servopin2);
  servo3.attach(servopin3);
  servoBase.attach(servopin4);
  gripper.attach(servopin5);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  servo1.write(0);
  servo2.write(0);
  servo3.write(0);
  servoBase.write(0);
  gripper.write(0);
}
void loop() {
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
      servo2.write(i);
      servo3.write(i);

      delay(20); // Adjust the delay as needed to control servo speed.
    }
    if (servo1.read() == 120 && servoBase.read() == 0 && distance > detected_distance) {
      servoBase.write(90);
    }
    else if (servo1.read() == 120 && servoBase.read() == 90 && distance > detected_distance) {
      servoBase.write(45);
    }
    else if (servo1.read() == 120 && servoBase.read() == 45 && distance > detected_distance) {
      servoBase.write(0);
    }
  }
  delay(100);
} // Delay before the next scan

void stopServos() {
  servo1.write(servo1.read()); // Stop servo1.
  servo2.write(servo2.read()); // Stop servo2.
  servo3.write(servo3.read()); // Stop servo3.
}

void rescue() {
  int gripAngle = 45;
  int liftAngle = 180;
  int liftPlace = 90;
  int moveFrom = servoBase.read();
  if (moveFrom == 0) {
    safezone = 25; // safe zone 1
    moveTo = 90;
  }
  if (moveFrom == 90) {
    safezone = 65;
    moveTo = 45;
  }
  if (moveFrom == 45) {
    safezone = moveFrom;
    liftPlace = 45;
    moveTo = 0;
  }

  // GRIP
  gripper.write(90); // ready to grip
  servo1.write(servo1.read());
  servo2.write(servo2.read());
  servo3.write(servo3.read());
  delay(1000);
  gripper.write(10); // taken
  delay(1000);

  // LIFT
  servo1.write(liftAngle);
  servo2.write(liftAngle);
  servo3.write(liftAngle);
  delay(1000);

  // PLACE ON SAFE ZONE
  servoBase.write(safezone);
  delay(1000);

  // PLACE
  servo1.write(liftPlace);
  servo2.write(liftPlace);
  servo3.write(liftPlace);
  gripper.write(90); // Open
  delay(1000);

  //MOVE
  servoBase.write(moveTo);
  delay(1000);
}
void searching() {
  if (servoBase.read() == 0) {
    servoBase.write(90);
  }
  if (servoBase.read() == 90) {
    servoBase.write(45);
  }
  if (servoBase.read() == 45) {
    servoBase.write(0);
  }
}
