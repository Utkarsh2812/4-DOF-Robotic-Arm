#include <Servo.h>

const int numServos = 4;  // Number of servos
Servo servos[numServos];  // Create an array of Servo objects

int servoPins[numServos] = {3, 5, 6, 9};  // Pin numbers for each servo

void setup() {
  Serial.begin(9600);  // Initialize serial communication
  Serial.println("Enter the servo index (0-3) and angle (0-180), separated by a space, and press Enter:");
  
  // Attach each servo to its corresponding pin
  for (int i = 0; i < numServos; ++i) {
    servos[i].attach(servoPins[i]);
  }
}

void loop() {
  if (Serial.available() > 0) {
    // Read the servo index and angle from serial input
    int servoIndex = Serial.parseInt();
    int angle = Serial.parseInt();
    
    // Ensure the servo index is within valid bounds
    if (servoIndex >= 0 && servoIndex < numServos) {
      // Ensure the angle is within valid bounds (0-180)
      if (angle < 0) {
        angle = 0;
      } else if (angle > 180) {
        angle = 180;
      }
      
      servos[servoIndex].write(angle);  // Set servo angle
      Serial.print("Moving servo ");
      Serial.print(servoIndex);
      Serial.print(" to angle: ");
      Serial.println(angle);
    } else {
      Serial.println("Invalid servo index. Enter a value between 0 and 3.");
    }

    // Clear the serial input buffer to prevent repeated reading of the same value
    while (Serial.available() > 0) {
      Serial.read();
    }
  }
}
