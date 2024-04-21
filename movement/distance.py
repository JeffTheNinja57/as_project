import RPi.GPIO as GPIO
import time


def measure_distance():
    # Trigger ultrasonic sensor
    GPIO.output(TRIG, True)
    time.sleep(0.00001)
    GPIO.output(TRIG, False)

    # Wait for the echo signal
    while GPIO.input(ECHO) == 0:
        pulse_start = time.time()

    while GPIO.input(ECHO) == 1:
        pulse_end = time.time()

    # Calculate distance based on the time difference
    pulse_duration = pulse_end - pulse_start
    distance = pulse_duration * 17150  # Speed of sound is 343m/s, so 34300cm/s
    distance = round(distance, 2)
    return distance
