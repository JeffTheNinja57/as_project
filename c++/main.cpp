// main.cpp

#include <Arduino.h>
#include "movement.h"

void setup() {
    // Initialize serial communication
    Serial.begin(9600);

    // Call setup function from movement module
    setup_movement();
}

void loop() {
    // Call patrol function from movement module
    patrol();
}
