

// Define motor pins
const int motorPin1 = A0;   // Pin 14 of L293
const int motorPin2 = A1;   // Pin 10 of L293
const int motorPin3 = A4;   // Pin  7 of L293
const int motorPin4 = A3;   // Pin  2 of L293

// Define ultrasound sensor pins
const int trigPin = 10;
const int echoPin = 11;

void setup() {
  // Set motor pins as outputs
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  
  // Set ultrasound sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // Initialize Serial communication
  Serial.begin(9600);
}

// Function to move the motor forward
void moveForward() {
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
}

// Function to move the motor backward for a specified duration
void moveBackward() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
}

// Function to stop the motor
void stopMotor() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
}

// Function to measure distance using ultrasound sensor
float measureDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  float duration = pulseIn(echoPin, HIGH);
  // Speed of sound in air = 343 m/s = 0.0343 cm/us
  float distance = (duration * 0.0343) / 2; // Divide by 2 because of round trip
  
  return distance;
}

// Function to check for obstacles and take appropriate action
void checkObstacle() {
  float distance = measureDistance();

  if (distance < 8) {
    // Move backward
    moveBackward(); 
    delay(500); // Delay for half a second
    stopMotor(); // Stop the motor after moving backward
  }
}

void loop() {
  // Check for obstacles
  checkObstacle();
}
