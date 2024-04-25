#include <NewPing.h>

// Motor pin definitions
const int motorPin1 = 2;  // Motor 1 control pin 1
const int motorPin2 = 3;  // Motor 1 control pin 2
const int motorPin3 = 4;  // Motor 2 control pin 1
const int motorPin4 = 5;  // Motor 2 control pin 2

// Ultrasonic sensor pin definitions
const int trigPin = 6;    // Ultrasonic sensor trigger pin
const int echoPin = 7;    // Ultrasonic sensor echo pin
NewPing sonar(trigPin, echoPin, 200);  // NewPing object with a maximum distance of 200cm

// Variables
int turning = 0;  // 0 = turn left, 1 = turn right
boolean wallDetected = false;

void setup() {
  // Initialize motor control pins as outputs
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);

  // Serial communication for debugging
  Serial.begin(9600);
}

void loop() {
  // Move the robot forward
  moveForward();

  // Check if wall is detected
  if (!wallDetected) {
    int distance = sonar.ping_cm();  // Get distance from the ultrasonic sensor in cm

    if (distance < 20) {
      // Wall detected
      stopMoving();
      delay(500); // Wait for a moment
      
      // Perform turn
      if (turning == 0) {
        turnLeft();
        turning = 1; // Change turning direction
      } else {
        turnRight();
        turning = 0; // Change turning direction
      }
      
      delay(1000); // Adjust this delay to change the turn angle (simulate a 90-degree turn)
      wallDetected = true; // Wall is detected and turned, now check again
    }
  } else {
    // Check distance after turning
    int distance = sonar.ping_cm();
    
    if (distance < 100) {
      // Keep the current turning direction (do not change turning variable)
      wallDetected = false; // Reset wall detection flag for next cycle
    }
  }
}

void moveForward() {
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
}

void stopMoving() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
}

void turnLeft() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
}

void turnRight() {
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
}
