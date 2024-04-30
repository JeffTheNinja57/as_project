

// Pin configurations for color sensor
#define S0 8
#define S1 9
#define S2 6
#define S3 7
#define sensorOut 2


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

void setup() {
  // Set pin modes
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  
  // Set sensor frequency to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
  
  Serial.begin(9600); // Initialize serial communication
}

void loop() {
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
  if (70 > red && blue > red && green > red && green > 100) {
      Serial.println("Color Detected: RED");
  } else if (70 > green && red > green && 70 > blue && red > blue) {
      Serial.println("Color Detected: GREEN");
  } else if (70 > blue && red > blue && green > blue && green > 60) {
      Serial.println("Color Detected: BLUE");
  } else {
    Serial.println("Color: Unknown");
  }
  
  // Wait for half a second before scanning again
  delay(500);
}
