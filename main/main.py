import Rpi.GPIO as GPIO
from color_recognition import color_sensor
from movement import front_patrol


def setup():

    # Define GPIO pins for motor control
    # Assuming the left motor is connected to GPIO pins 17 (input 1) and 18 (input 2)
    # and the right motor is connected to GPIO pins 22 (input 3) and 23 (input 4)
    left_motor_pins = (17, 18)
    right_motor_pins = (22, 23)

    # Define GPIO pins for ultrasonic sensor
    TRIG = 24
    ECHO = 25

    # Set GPIO mode
    GPIO.setmode(GPIO.BCM)

    # Setup motor control pins as outputs
    for pin in left_motor_pins + right_motor_pins:
        GPIO.setup(pin, GPIO.OUT)

    # Setup ultrasonic sensor pins
    GPIO.setup(TRIG, GPIO.OUT)
    GPIO.setup(ECHO, GPIO.IN)


if __name__ == "__main__":
    setup()
    try:
        front_patrol.patrol()
    except KeyboardInterrupt:
        front_patrol.stop()
        GPIO.cleanup()
