#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver robot_arm = Adafruit_PWMServoDriver();

#define servoMIN 150
#define servoMAX 600
int servo = 0;
const int pingPin = 8; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 7;
int incoming[3];
int c = 1;
int d = 1;
const int numServos = 5;
int pos;
void setup() 
{
  Serial.begin(9600);  // Initialize serial communication
  Serial.println("Enter the servo index (0-3) and pulse, separated by a space, and press Enter:");
  robot_arm.begin();
  robot_arm.setPWMFreq(60);
  //200-350 180= open 350= close (gripper)
  delay(100);
  home();
  delay(3000);
}

int angleToPulse(int ang)
{
   int pulse = map(ang,0, 180, servoMIN,servoMAX); 
   //Serial.println("Angle: ");Serial.print(ang);
   //Serial.println(" pulse: ");Serial.println(pulse);
   return pulse;
}

void loop()
{
  long duration, inches, cm;
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  cm = microsecondsToCentimeters(duration);
  Serial.println(cm);
  if (cm <= 7 && c == 1)
  {
    c = 0;
    main_loop();
  }
  else if (cm >=7 && cm <=10 && d == 1){
    d=0;
    main_loop_2();
  }
}

long microsecondsToCentimeters(long microseconds) 
{
   return microseconds / 29 / 2;
}

void main_loop()
{
    pick();
    delay(2000);
    grab();
    delay(2000);
    home_with_object();
    delay(2000);
    move();
    delay(2000);
    place();
    delay(2000);
    loose();
    delay(2000);
    move_without_object();
    delay(2000);
    home();
    delay(2000);
    c = 1;
}

void main_loop_2()
{
    pick2();
    delay(2000);
    grab2();
    delay(2000);
    home_with_object_2();
    delay(2000);
    move2();
    delay(2000);
    place2();
    delay(2000);
    loose2();
    delay(2000);
    move_without_object2();
    delay(2000);
    home();
    delay(2000);
    d = 1;
}

void home()
{
  robot_arm.setPWM(4, 0, angleToPulse(0));
  delay(100); // base
  robot_arm.setPWM(5, 0, angleToPulse(120));
  delay(100); // 425 = 90  (upper base)
  robot_arm.setPWM(6, 0, angleToPulse(150));
  delay(100);  // 250 = 0  elbow
  robot_arm.setPWM(7, 0, angleToPulse(120));
  delay(100);  // wrist
  robot_arm.setPWM(8, 0, angleToPulse(0));
  delay(100);   //gripper
}

void pick()
{
robot_arm.setPWM(4, 0, angleToPulse(10));
delay(100); // base  
for (int angle = 120; angle >= 20; angle--) //upper base
{
    robot_arm.setPWM(5, 0, angleToPulse(angle));
    delay(10);
}

for (int angle = 150; angle <= 180; angle++) //elbow
{
    robot_arm.setPWM(6, 0, angleToPulse(angle));
    delay(10);
}

for (int angle = 120; angle <= 170; angle++) //wrist
{
    robot_arm.setPWM(7, 0, angleToPulse(angle));
    delay(10);
}
  robot_arm.setPWM(8, 0, angleToPulse(0));  //gripper
  delay(100);
}

void grab()
{
robot_arm.setPWM(4, 0, angleToPulse(10));
delay(100); // base  
for (int angle = 120; angle >= 20; angle--) //upper base
{
    robot_arm.setPWM(5, 0, angleToPulse(angle));
    delay(10);
}

for (int angle = 150; angle <= 180; angle++) //elbow
{
    robot_arm.setPWM(6, 0, angleToPulse(angle));
    delay(10);
}

for (int angle = 120; angle <= 170; angle++) //wrist
{
    robot_arm.setPWM(7, 0, angleToPulse(angle));
    delay(10);
}
  robot_arm.setPWM(8, 0, angleToPulse(100));  //gripper
  delay(100);
}

void home_with_object()
{
  robot_arm.setPWM(4, 0, angleToPulse(10));
  delay(100); // base
  robot_arm.setPWM(5, 0, angleToPulse(120));
  delay(100); // 425 = 90  (upper base)
  robot_arm.setPWM(6, 0, angleToPulse(150));
  delay(100);  // 250 = 0  elbow
  robot_arm.setPWM(7, 0, angleToPulse(120));
  delay(100);  // wrist
  robot_arm.setPWM(8, 0, angleToPulse(100));
  delay(100);   //gripper
}

void move()
{
for (int angle = 10; angle <= 60; angle++) //base
{
    robot_arm.setPWM(4, 0, angleToPulse(angle));
    delay(10);
}
for (int angle = 120; angle >= 60; angle--) //upper base
{
    robot_arm.setPWM(5, 0, angleToPulse(angle));
    delay(10);
}
for (int angle = 150; angle <= 180; angle++) //elbow
{
    robot_arm.setPWM(6, 0, angleToPulse(angle));
    delay(10);
}
for (int angle = 120; angle <= 190; angle++) //wrist
{
    robot_arm.setPWM(7, 0, angleToPulse(angle));
    delay(10);
}
  robot_arm.setPWM(8, 0, angleToPulse(100));  //gripper
  delay(100);
}

void place()
{
  robot_arm.setPWM(4, 0, angleToPulse(60));  //base
  delay(100);
for (int angle = 60; angle >= 20; angle--) //upper base
{
    robot_arm.setPWM(5, 0, angleToPulse(angle));
    delay(10);
}
  robot_arm.setPWM(6, 0, angleToPulse(170));  //elbow
  delay(100);

  robot_arm.setPWM(7, 0, angleToPulse(200));  //wrist
  delay(100);

  robot_arm.setPWM(8, 0, angleToPulse(100));  //gripper
  delay(100);
}

void loose()
{
  robot_arm.setPWM(4, 0, angleToPulse(60));  //base
  delay(100);
for (int angle = 60; angle >= 20; angle--) //upper base
{
    robot_arm.setPWM(5, 0, angleToPulse(angle));
    delay(10);
}
  robot_arm.setPWM(6, 0, angleToPulse(170));  //elbow
  delay(100);

  robot_arm.setPWM(7, 0, angleToPulse(200));  //wrist
  delay(100);

  robot_arm.setPWM(8, 0, angleToPulse(0));  //gripper
  delay(100);
}

void move_without_object()
{
  robot_arm.setPWM(4, 0, angleToPulse(60));  //base
  delay(100);
for (int angle = 20; angle <= 90; angle++) //upper base
{
    robot_arm.setPWM(5, 0, angleToPulse(angle));
    delay(10);
}
for (int angle = 170; angle >= 150; angle--) //elbow
{
    robot_arm.setPWM(6, 0, angleToPulse(angle));
    delay(10);
}
for (int angle = 200; angle >= 120; angle--) //wrist
{
    robot_arm.setPWM(7, 0, angleToPulse(angle));
    delay(10);
}
  robot_arm.setPWM(8, 0, angleToPulse(0));  //gripper
  delay(100);
}

void pick2()
{
robot_arm.setPWM(4, 0, angleToPulse(20));
delay(100); // base  
for (int angle = 120; angle >= 20; angle--) //upper base
{
    robot_arm.setPWM(5, 0, angleToPulse(angle));
    delay(10);
}

for (int angle = 150; angle <= 180; angle++) //elbow
{
    robot_arm.setPWM(6, 0, angleToPulse(angle));
    delay(10);
}

for (int angle = 120; angle <= 170; angle++) //wrist
{
    robot_arm.setPWM(7, 0, angleToPulse(angle));
    delay(10);
}
  robot_arm.setPWM(8, 0, angleToPulse(0));  //gripper
  delay(100);
}

void grab2()
{
robot_arm.setPWM(4, 0, angleToPulse(20));
delay(100); // base  
for (int angle = 120; angle >= 20; angle--) //upper base
{
    robot_arm.setPWM(5, 0, angleToPulse(angle));
    delay(10);
}

for (int angle = 150; angle <= 180; angle++) //elbow
{
    robot_arm.setPWM(6, 0, angleToPulse(angle));
    delay(10);
}

for (int angle = 120; angle <= 170; angle++) //wrist
{
    robot_arm.setPWM(7, 0, angleToPulse(angle));
    delay(10);
}
  robot_arm.setPWM(8, 0, angleToPulse(100));  //gripper
  delay(100);
}

void home_with_object_2()
{
  robot_arm.setPWM(4, 0, angleToPulse(20));
  delay(100); // base
  robot_arm.setPWM(5, 0, angleToPulse(120));
  delay(100); // 425 = 90  (upper base)
  robot_arm.setPWM(6, 0, angleToPulse(150));
  delay(100);  // 250 = 0  elbow
  robot_arm.setPWM(7, 0, angleToPulse(120));
  delay(100);  // wrist
  robot_arm.setPWM(8, 0, angleToPulse(100));
  delay(100);   //gripper
}

void move2()
{
for (int angle = 20; angle <= 90; angle++) //base
{
    robot_arm.setPWM(4, 0, angleToPulse(angle));
    delay(10);
}
for (int angle = 120; angle >= 60; angle--) //upper base
{
    robot_arm.setPWM(5, 0, angleToPulse(angle));
    delay(10);
}
for (int angle = 150; angle <= 180; angle++) //elbow
{
    robot_arm.setPWM(6, 0, angleToPulse(angle));
    delay(10);
}
for (int angle = 120; angle <= 190; angle++) //wrist
{
    robot_arm.setPWM(7, 0, angleToPulse(angle));
    delay(10);
}
  robot_arm.setPWM(8, 0, angleToPulse(100));  //gripper
  delay(100);
}

void place2()
{
  robot_arm.setPWM(4, 0, angleToPulse(90));  //base
  delay(100);
for (int angle = 60; angle >= 20; angle--) //upper base
{
    robot_arm.setPWM(5, 0, angleToPulse(angle));
    delay(10);
}
  robot_arm.setPWM(6, 0, angleToPulse(170));  //elbow
  delay(100);

  robot_arm.setPWM(7, 0, angleToPulse(200));  //wrist
  delay(100);

  robot_arm.setPWM(8, 0, angleToPulse(100));  //gripper
  delay(100);
}

void loose2()
{
  robot_arm.setPWM(4, 0, angleToPulse(90));  //base
  delay(100);
for (int angle = 60; angle >= 20; angle--) //upper base
{
    robot_arm.setPWM(5, 0, angleToPulse(angle));
    delay(10);
}
  robot_arm.setPWM(6, 0, angleToPulse(170));  //elbow
  delay(100);

  robot_arm.setPWM(7, 0, angleToPulse(200));  //wrist
  delay(100);

  robot_arm.setPWM(8, 0, angleToPulse(0));  //gripper
  delay(100);
}

void move_without_object2()
{
  robot_arm.setPWM(4, 0, angleToPulse(90));  //base
  delay(100);
for (int angle = 20; angle <= 90; angle++) //upper base
{
    robot_arm.setPWM(5, 0, angleToPulse(angle));
    delay(10);
}
for (int angle = 170; angle >= 150; angle--) //elbow
{
    robot_arm.setPWM(6, 0, angleToPulse(angle));
    delay(10);
}
for (int angle = 200; angle >= 120; angle--) //wrist
{
    robot_arm.setPWM(7, 0, angleToPulse(angle));
    delay(10);
}
  robot_arm.setPWM(8, 0, angleToPulse(0));  //gripper
  delay(100);
}
