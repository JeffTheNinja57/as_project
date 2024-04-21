// movement.cpp

#include "movement.h"
#include <Arduino.h>
#include <random>

void setup_movement() {
    // Setup motor control pins as outputs
    for (int pin : left_motor_pins) {
        pinMode(pin, OUTPUT);
    }
    for (int pin : right_motor_pins) {
        pinMode(pin, OUTPUT);
    }

    // Setup ultrasonic sensor pins
    pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);
}

void forward() {
    // Set motor pins for forward motion
    digitalWrite(left_motor_pins[0], HIGH);
    digitalWrite(left_motor_pins[1], LOW);
    digitalWrite(right_motor_pins[0], HIGH);
    digitalWrite(right_motor_pins[1], LOW);
}

void stop() {
    // Stop the motors
    for (int pin : left_motor_pins) {
        digitalWrite(pin, LOW);
    }
    for (int pin : right_motor_pins) {
        digitalWrite(pin, LOW);
    }
}

void turn(String direction) {
    // Stop the motors
    stop();

    // Turn left or right
    if (direction == "left") {
        left_turn();
    } else if (direction == "right") {
        right_turn();
    }
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

        // If close to the wall, turn left or right randomly
        if (distance < 20) {  // Adjust this threshold as needed
            String direction = random(2) == 0 ? "left" : "right";
            turn(direction);
            delay(1000);  // Turn for a short duration
        }
    }
}

float measure_distance() {
    // Trigger ultrasonic sensor
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);

    // Wait for the echo signal
    unsigned long pulse_start, pulse_end;
    pulse_start = micros();
    while (digitalRead(ECHO) == LOW) {
        pulse_start = micros();
    }
    while (digitalRead(ECHO) == HIGH) {
        pulse_end = micros();
    }

    // Calculate duration based on the time difference
    float pulse_duration = pulse_end - pulse_start;
    float distance = pulse_duration * 0.034 / 2;  // Speed of sound is 34 cm/ms
    return distance;
}

void left_turn() {
    stop();
    digitalWrite(left_motor_pins[0], LOW);
    digitalWrite(left_motor_pins[1], HIGH);
    digitalWrite(right_motor_pins[0], HIGH);
    digitalWrite(right_motor_pins[1], LOW);
    delay(500);
    stop();
}

void right_turn() {
    stop();
    digitalWrite(left_motor_pins[0], HIGH);
    digitalWrite(left_motor_pins[1], LOW);
    digitalWrite(right_motor_pins[0], LOW);
    digitalWrite(right_motor_pins[1], HIGH);
    delay(500);
    stop();
}
