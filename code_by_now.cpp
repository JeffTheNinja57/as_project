// Pin configurations for color sensor
#define S0 8
#define S1 9
#define S2 6
#define S3 7
#define sensorOut 2

// Pin configurations for multicolor LED
#define redLEDPin 3
#define greenLEDPin 4
#define blueLEDPin 5

// Define motor pins
const int motorPin1 = A0;  // Pin 14 of L293
const int motorPin2 = A1;  // Pin 10 of L293
const int motorPin3 = A4;  // Pin  7 of L293
const int motorPin4 = A3;  // Pin  2 of L293

// Define ultrasound sensor pins
const int trigPin = 10;
const int echoPin = 11;

// Define variables to store RGB values
int red = 0;
int green = 0;
int blue = 0;

// Function to read RGB values
void readRGB() {
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  // Reading red value
  red = pulseIn(sensorOut, LOW);

  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  // Reading green value
  green = pulseIn(sensorOut, LOW);

  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  // Reading blue value
  blue = pulseIn(sensorOut, LOW);
}

// Function to move the motor backward for a specified duration

void moveREDRIGHT() {
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
  delay(450);  // Delay for half a second
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
  delay(855);  // Delay for half a second
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
  delay(855);
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
  delay(450);  // Delay for half a second
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
}

void moveBLUELEFT() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
  delay(450);  // Delay for half a second
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
  delay(855);  // Delay for half a second
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
  delay(855);
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
  delay(450);
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
}
void moveGREENBACK() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
  delay(900);  // Delay for half a second
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
  delay(850);  // Delay for half a second
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
  delay(850);
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
  delay(900);
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
  float distance = (duration * 0.0343) / 2;  // Divide by 2 because of round trip

  return distance;
}

float stopLED() {
  digitalWrite(redLEDPin, LOW);
  digitalWrite(greenLEDPin, LOW);
  digitalWrite(blueLEDPin, LOW);
}

// Function to check for obstacles, detect color, and take appropriate actions
void checkColorAndObstacle() {

  // Check for obstacles
  float distance = measureDistance();
  if (distance < 5) {
    // Move backward
    // Read RGB values
    readRGB();
    // Display RGB values in the console
    Serial.print("Red: ");
    Serial.print(red);
    Serial.print(" Green: ");
    Serial.print(green);
    Serial.print(" Blue: ");
    Serial.println(blue);

    // Determine color based on RGB values
    if (45 > red && blue > red && green > red && green > 60) {
      digitalWrite(redLEDPin, HIGH);
      digitalWrite(greenLEDPin, LOW);
      digitalWrite(blueLEDPin, LOW);
      delay(1000);
      stopLED();
      moveREDRIGHT();
    } else if (50 > green && red > green && red > blue) {
      digitalWrite(redLEDPin, LOW);
      digitalWrite(greenLEDPin, HIGH);
      digitalWrite(blueLEDPin, LOW);
      delay(1000);
      stopLED();
      moveGREENBACK();
    } else if (50 > blue && red > blue && green > blue && green > 50) {
      digitalWrite(redLEDPin, LOW);
      digitalWrite(greenLEDPin, LOW);
      digitalWrite(blueLEDPin, HIGH);
      delay(1000);
      stopLED();
      moveBLUELEFT();
    } else {
      digitalWrite(redLEDPin, LOW);
      digitalWrite(greenLEDPin, LOW);
      digitalWrite(blueLEDPin, LOW);
      stopLED();
    }
  }
}

void setup() {
  // Set pin modes
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Set sensor frequency to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  // Set LED pin modes
  pinMode(redLEDPin, OUTPUT);
  pinMode(greenLEDPin, OUTPUT);
  pinMode(blueLEDPin, OUTPUT);

  // Set motor pins as outputs
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);

  // Initialize Serial communication
  Serial.begin(9600);
}

void loop() {
  // Check color and obstacle, and take appropriate actions
  checkColorAndObstacle();
}
