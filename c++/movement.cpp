// movement.cpp

#include "movement.h"
#include <Arduino.h>
#include <random>

// Define motor control pins
const uint8_t dirPin1 = 5, dirPin2 = 10, spdPin1 = 6, spdPin2 = 9;
// Define constant for turning duration (in milliseconds)
const unsigned long turn_duration = 1000; // Adjust as needed
// Define constant for forward distance (in centimeters)
const float forward_distance = 10.0; // Adjust as needed

// Variable to keep track of previous turn direction
String prev_turn = "";

void setSpeed(uint8_t speedLeft, uint8_t speedRight) {
  // We'll scale the speed from 0~100. We'll set the minimum at 55 so the
  // robot actually moves!
  speedLeft = 55+speedLeft*2;
  speedRight = 55+speedRight*2;
  // Send the PWM signal to the speed pins
  analogWrite(spdPin1, speedLeft);
  analogWrite(spdPin2, speedRight);
}

void setup_movement() {
    // Setup motor control pins as outputs
    pinMode(dirPin1, OUTPUT);
    pinMode(dirPin2, OUTPUT);
}

void forward() {
    // Set the direction of the motors to move forward
    digitalWrite(dirPin1, LOW);
    digitalWrite(dirPin2, LOW);
}

void stop() {
    // Stop the motors
    digitalWrite(spdPin1, 0);
    digitalWrite(spdPin2, 0);
    // As a precaution reset the direction of the motors
    digitalWrite(dirPin1, LOW);
    digitalWrite(dirPin2, LOW);
}

void turn(String direction) {
    // Stop the motors
    stop();

    // Turn left or right
    if (direction == "left") {
        digitalWrite(dirPin1, HIGH);
        digitalWrite(dirPin2, LOW);
    } else if (direction == "right") {
        digitalWrite(dirPin1, LOW);
        digitalWrite(dirPin2, HIGH);
    }

    // Record the current turn direction as previous turn
    prev_turn = direction;
}

void patrol() {
    while (true) {
        // Move forward
        forward();
        delay(500);  // Move for a short duration

        // Measure distance to the wall
        float distance = measure_distance();
        Serial.print("Distance to wall: ");
        Serial.print(distance);
        Serial.println(" cm");

        // If close to the wall, turn left or right
        if (distance < 20) {  // Adjust this threshold as needed
            // Determine turn direction
            String direction;
            if (prev_turn == "") {
                // If there was no previous turn, turn randomly
                direction = random(2) == 0 ? "left" : "right";
            } else {
                // If there was a previous turn, turn in the opposite direction
                direction = prev_turn == "left" ? "right" : "left";
            }

            // Perform turn
            turn(direction);
            delay(turn_duration); // Turn for the specified duration

            // Move forward a certain distance
            // Move for 10 cm
            forward();
            delay(1000 * (forward_distance / 10)); // Convert cm to milliseconds

            // Stop the robot
            stop();
            delay(500); // Pause for stability

            // Make another turn (90 degrees) after moving forward
            String next_turn = direction == "left" ? "right" : "left";
            turn(next_turn);
            delay(turn_duration); // Turn for the specified duration

            // Reset previous turn direction
            prev_turn = "";
        }
    }
}
