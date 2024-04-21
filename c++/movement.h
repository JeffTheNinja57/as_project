// movement.h

#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <Arduino.h>

// Define GPIO pins for motor control
const int left_motor_pins[] = {17, 18};
const int right_motor_pins[] = {22, 23};

// Define GPIO pins for ultrasonic sensor
const int TRIG = 24;
const int ECHO = 25;

void setup_movement();
void forward();
void stop();
void turn(String direction);
void patrol();
float measure_distance();
void left_turn();
void right_turn();

#endif
