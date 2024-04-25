uint8_t dirPin1 = 5, dirPin2 = 10, spdPin1 = 6, spdPin2 = 9;

void setup() {
  // Configure the pin modes
  pinMode(dirPin1, OUTPUT);
  pinMode(dirPin2, OUTPUT);
  pinMode(spdPin1, OUTPUT);
  pinMode(spdPin2, OUTPUT);
  // Set the speed of the motors (without moving!)
  setSpeed(100, 100);
  // Test forward movement for 0.5 seconds
  moveForward();
  delay(1000);
  // Test backward movement for 0.5 seconds
  moveBackward();
  delay(1000);
  // Test left (ccw) movement for 0.5 seconds
  moveLeft();
  delay(1000);
  // Test right (cw) movement for 0.5 seconds
  moveRight();
  delay(1000);  
  // Test stop any movement
  moveStop();
}

void loop() {
}

void setSpeed(uint8_t speedLeft, uint8_t speedRight) {
  // We'll scale the speed from 0~100. We'll set the minimum at 55 so the 
  // robot actually moves!
  speedLeft = 55+speedLeft*2;
  speedRight = 55+speedRight*2;
  // Send the PWM signal to the speed pins
  analogWrite(spdPin1, speedLeft);
  analogWrite(spdPin2, speedRight);
}

void moveForward() {
  // Set the direction of the motors to move forward
  digitalWrite(dirPin1, LOW);
  digitalWrite(dirPin2, LOW);
}

void moveBackward() {
  // Set the direction of the motors to move backward
  digitalWrite(dirPin1, HIGH);
  digitalWrite(dirPin2, HIGH);
}

void moveLeft() {
  // Set the direction of the motors to move backward
  digitalWrite(dirPin1, HIGH);
  digitalWrite(dirPin2, LOW);
}

void moveRight() {
  // Set the direction of the motors to move backward
  digitalWrite(dirPin1, LOW);
  digitalWrite(dirPin2, HIGH);
}

void moveStop() {
  // Set the speed to 0
  analogWrite(spdPin1, 0);
  analogWrite(spdPin2, 0);
  // As a precaution reset the direction of the motors
  digitalWrite(dirPin1, LOW);
  digitalWrite(dirPin2, LOW);
}