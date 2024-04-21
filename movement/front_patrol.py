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
