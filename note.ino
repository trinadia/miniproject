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
