// Pin configurations for ultrasonic sensor
const int trigPin = 11;
const int echoPin = 12;

// Pin configurations for touch sensor and LED
const int touch_pin = 1;
int LED = 13;

// Pin configurations for color sensor
#define S0 8
#define S1 9
#define S2 6
#define S3 7
#define sensorOut 2

// Calibration values
#define BLUE_LOW_PARA 50
#define BLUE_HIGH_PARA 300
#define RED_LOW_PARA 50
#define RED_HIGH_PARA 300
#define GREEN_LOW_PARA 50
#define GREEN_HIGH_PARA 300

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Initialize ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Initialize touch sensor and LED pins
  pinMode(touch_pin, INPUT);
  pinMode(LED, OUTPUT);

  // Initialize color sensor pins
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  // Set initial state for color sensor pins
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  // Initialize LED pins for color output
  pinMode(5, OUTPUT); // For blue
  pinMode(3, OUTPUT); // For green
  pinMode(4, OUTPUT); // For red
}

void loop() {
  long duration = getUltrasonicDistance();
  printUltrasonicDistance(duration);

  int red, green, blue;
  getColorSensorValues(red, green, blue);
  controlLEDs(red, green, blue);

  detectTouch();
  
  delay(500); // Delay for stability
}

// Function to get ultrasonic sensor distance
long getUltrasonicDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  return microsecondsToCentimeters(duration);
}

// Function to print ultrasonic sensor distance
void printUltrasonicDistance(long duration) {
  Serial.print(duration);
  Serial.println("cm");
}

// Function to get color sensor values
void getColorSensorValues(int& red, int& green, int& blue) {
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  red = map(pulseIn(sensorOut, LOW), RED_HIGH_PARA, RED_LOW_PARA, 255, 0);

  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  green = map(pulseIn(sensorOut, LOW), GREEN_HIGH_PARA, GREEN_LOW_PARA, 255, 0);

  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  blue = map(pulseIn(sensorOut, LOW), BLUE_HIGH_PARA, BLUE_LOW_PARA, 255, 0);
}

// Function to control LEDs based on color sensor readings
void controlLEDs(int red, int green, int blue) {
  digitalWrite(4, LOW);  // Green LED
  digitalWrite(3, LOW);  // Blue LED
  digitalWrite(5, LOW);  // Red LED
  if (red > blue && red > green) {
    digitalWrite(5, HIGH); // Red LED
    Serial.println("Detected color: Red");
  } else if (blue > red && blue > green) {
    digitalWrite(3, HIGH); // Blue LED
    Serial.println("Detected color: Blue");
  } else if (green > blue && green > red) {
    digitalWrite(4, HIGH); // Green LED
    Serial.println("Detected color: Green");
  }
}

// Function to detect touch
void detectTouch() {
  if (digitalRead(touch_pin) == HIGH) {
    digitalWrite(LED, HIGH); // Turn on the LED
    Serial.println("Touch detected!");
  } else {
    digitalWrite(LED, LOW); // Turn off the LED
  }
}

// Function to convert microseconds to centimeters
long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}
