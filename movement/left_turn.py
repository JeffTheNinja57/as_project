def left_turn():
    stop()
    GPIO.output(left_motor_pins[0], GPIO.LOW)
    GPIO.output(left_motor_pins[1], GPIO.HIGH)
    GPIO.output(right_motor_pins[0], GPIO.HIGH)
    GPIO.output(right_motor_pins[1], GPIO.LOW)
    time.sleep(0.5)
    stop()

