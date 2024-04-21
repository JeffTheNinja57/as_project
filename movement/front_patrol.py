from movement import left_turn, right_turn, distance
import RPi.GPIO as GPIO
import time
import random


def forward():
    # Set motor pins for forward motion
    GPIO.output(left_motor_pins[0], GPIO.HIGH)
    GPIO.output(left_motor_pins[1], GPIO.LOW)
    GPIO.output(right_motor_pins[0], GPIO.HIGH)
    GPIO.output(right_motor_pins[1], GPIO.LOW)


def stop():
    # Stop the motors
    for pin in left_motor_pins + right_motor_pins:
        GPIO.output(pin, GPIO.LOW)


def turn(direction):
    # Stop the motors
    stop()

    # Turn left or right
    if direction == 'left':
        left_turn.left_turn()
    elif direction == 'right':
        right_turn.right_turn()
    else:
        raise ValueError("Invalid direction. Expected 'left' or 'right'.")


def patrol():
    while True:
        # Move forward
        forward()
        time.sleep(0.5)  # Move for a short duration

        # Measure distance to the wall
        distance = measure_distance()
        print("Distance to wall:", distance, "cm")

        # If close to the wall, turn left or right randomly
        if distance < 20:  # Adjust this threshold as needed
            direction = 'left' if random.choice([True, False]) else 'right'
            turn(direction)
            time.sleep(1)  # Turn for a short duration
