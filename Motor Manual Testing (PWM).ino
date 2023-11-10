#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver robot_arm = Adafruit_PWMServoDriver(); //creating object (robot_arm)

#define servoMIN 150  //min pulse of servos
#define servoMAX 600  //max pulse of servos
int servo = 0;

void setup() {
  Serial.begin(9600);  // Initialize serial communication at 9600 bits per second
  Serial.println("Enter the servo index (0-5) and pulse, separated by a space, and press Enter:");
  robot_arm.begin();  // sets up communication with servo driver
  robot_arm.setPWMFreq(60);
  delay(1000);
}

void loop()
{
    if (Serial.available() > 0) 
    {
    // Read the servo index and angle from serial input
    int servoIndex = Serial.parseInt();
    int angle = Serial.parseInt();
    
    // Ensure the servo index is within valid bounds
   
      
    robot_arm.setPWM(servoIndex, 0, angleToPulse(angle));  // Set servo angle
    Serial.print("Moving servo ");
    Serial.print(servoIndex);
    Serial.print(" to angle: ");
    Serial.println(angle);
    

    // Clear the serial input buffer to prevent repeated reading of the same value
    while (Serial.available() > 0) 
    {
      Serial.read();
    }
    }
}

int angleToPulse(int ang)
{
   int pulse = map(ang,0, 180, servoMIN,servoMAX); 
   //Serial.println("Angle: ");Serial.print(ang);
   //Serial.println(" pulse: ");Serial.println(pulse);
   return pulse;
}
