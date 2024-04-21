import RPi.GPIO as GPIO
import time

# Define pins
S0 = 8
S1 = 9
S2 = 6
S3 = 7
sensorOut = 2

# Calibration
RED_LOW_PARA = 40
RED_HIGH_PARA = 200
GREEN_LOW_PARA = 50
GREEN_HIGH_PARA = 300
BLUE_LOW_PARA = 50
BLUE_HIGH_PARA = 300

# Variables
blue = 0
red = 0
green = 0
frequency = 0

def setup():
    GPIO.setmode(GPIO.BCM)
    GPIO.setup(S0, GPIO.OUT)
    GPIO.setup(S1, GPIO.OUT)
    GPIO.setup(S2, GPIO.OUT)
    GPIO.setup(S3, GPIO.OUT)
    GPIO.setup(sensorOut, GPIO.IN)

    GPIO.output(S0, GPIO.HIGH)
    GPIO.output(S1, GPIO.LOW)

def loop():
    global red, green, blue, frequency

    GPIO.output(S2, GPIO.LOW)
    GPIO.output(S3, GPIO.LOW)
    frequency = GPIO.input(sensorOut)
    red = frequency
    print("R= ", frequency)

    time.sleep(0.1)

    GPIO.output(S2, GPIO.HIGH)
    GPIO.output(S3, GPIO.HIGH)
    frequency = GPIO.input(sensorOut)
    green = frequency
    print("G= ", frequency)

    time.sleep(0.1)

    GPIO.output(S2, GPIO.LOW)
    GPIO.output(S3, GPIO.HIGH)
    frequency = GPIO.input(sensorOut)
    blue = frequency
    print("B= ", frequency)

    time.sleep(0.1)

    if red > blue and red > green:
        print("RED")
    elif blue > red and blue > green:
        print("BLUE")
    elif green > blue and green > red:
        print("GREEN")

    time.sleep(2)

if __name__ == "__main__":
    setup()
    while True:
        loop()