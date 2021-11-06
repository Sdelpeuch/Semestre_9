"""
Main file for execute firstbot
"""
import math
import sys
import time

from detection import Detection, Color
from motors import Motors
from odometry import Odometry


class Robot:
    """
    robot class with motors and detection initialization
    """

    def __init__(self, average_speed):
        self.detection = Detection()
        self.motors = Motors()
        self.odometry = Odometry()
        self.kp = 0.9
        self.Kd = 0
        self.kpa = 1
        self.kpd = 300
        self.Kp_theta = 100
        self.previous_error = 0
        self.average_speed = average_speed  # degrés/secondes
        self.tmp_prev = time.time()

    def tick(self, color):
        """
        A method for doing the necessary processing for a line-following tick. This method must be encapsulated in a
        while true to allow optimal line tracking
        :param color: The color to follow
        :return: None
        """
        cx, cy = self.detection.detect(color)
        if cx != 0 and cy != 0:
            error = cx - 320

            correction = self.kp * error + self.Kd * (error - self.previous_error) / (time.time() - self.tmp_prev)

            self.previous_error = error
            self.tmp_prev = time.time()

            left_instruction = self.average_speed + correction
            right_instruction = self.average_speed - correction

            if left_instruction > 720:
                right_instruction = right_instruction - (left_instruction - 720)
                left_instruction = 720
            elif left_instruction < -720:
                right_instruction = right_instruction + (-720 - left_instruction)
                left_instruction = -720

            if right_instruction > 720:
                left_instruction = left_instruction - (right_instruction - 720)
                right_instruction = 720
            elif right_instruction < -720:
                left_instruction = left_instruction + (-720 - right_instruction)
                right_instruction = -720
            self.motors.move(left_instruction, right_instruction)
        else:
            self.motors.move(220, 160)

    def tick_tock(self, color, running_time):
        """
        Encapsulates the tick method in a while true sensitive to keyboard interrupts
        :param color: The color to follow
        :param running_time: time before stop while loop
        :return: None
        """
        begin = time.time()
        try:
            while time.time() - begin < running_time:
                self.tick(color)
        except KeyboardInterrupt:
            print("Stopped")
            return

    def tick_tock_odometry(self, color, running_time, odometry):
        """
        Encapsulates the tick method in a while true sensitive to keyboard interrupts
        :param color: The color to follow
        :param running_time: time before stop while loop
        :param odometry: odometry of robot
        :return: None
        """
        begin = time.time()
        prev_time = begin
        f = open("map.txt", "w")
        try:
            while time.time() - begin < running_time:
                self.tick(color)
                if odometry:
                    speed = self.motors.get_speed()
                    left_speed = speed[0]
                    right_speed = -speed[1]
                    current_time = time.time()
                    self.odometry.compute_odometry(left_speed, right_speed, current_time - prev_time)
                    prev_time = current_time
                    f.write(str(self.odometry.get_x()) + "," + str(self.odometry.get_y()))
                    f.write("\n")

            if odometry:
                print("X position :", self.odometry.get_x() / 10)
                print("Y position :", self.odometry.get_y() / 10)
                print("Theta : ", math.degrees(self.odometry.get_orientation()))
                print(" ")
                f.close()
        except KeyboardInterrupt:
            print("Stopped")
            return

    def go_to(self, x=0, y=0, theta=0):
        """
        Go to a specified position
        :param theta: desired angle
        :param x: x position
        :param y: y position
        :return: None
        """
        print("Let's go")
        current_x = self.odometry.get_x()
        current_y = self.odometry.get_y()
        epsilon = 5
        epsilon_theta = math.pi / 100
        prev_time = time.time()
        try:
            while not ((x - epsilon < current_x < x + epsilon) and (y - epsilon < current_y < y + epsilon)):
                speed = self.motors.get_speed()
                left_speed = speed[0]
                right_speed = -speed[1]
                current_time = time.time()
                self.odometry.compute_odometry(left_speed, right_speed, current_time - prev_time)
                prev_time = current_time

                current_x = self.odometry.get_x()
                current_y = self.odometry.get_y()
                current_theta = self.odometry.get_orientation()

                d_theta = math.atan2((y - current_y), (x - current_x))
                delta_theta = d_theta - current_theta
                norm = math.sqrt((x - current_x) ** 2 + (y - current_y) ** 2)

                avg_speed = self.kpa * norm * (1 - (delta_theta / math.pi))
                delta_speed = self.kpd * delta_theta

                left_instruction = avg_speed - delta_speed
                right_instruction = avg_speed + delta_speed

                if left_instruction > 720:
                    right_instruction = right_instruction - (left_instruction - 720)
                    left_instruction = 720
                elif left_instruction < -720:
                    right_instruction = right_instruction + (-720 - left_instruction)
                    left_instruction = -720

                if right_instruction > 720:
                    left_instruction = left_instruction - (right_instruction - 720)
                    right_instruction = 720
                elif right_instruction < -720:
                    left_instruction = left_instruction + (-720 - right_instruction)
                    right_instruction = -720

                self.motors.move(left_instruction, right_instruction)

            current_theta = self.odometry.get_orientation()
            theta = math.radians(theta)
            prev_time = time.time()
            while not (theta - epsilon_theta < current_theta % (2 * math.pi) < theta + epsilon_theta):
                speed = self.motors.get_speed()
                left_speed = speed[0]
                right_speed = -speed[1]
                current_time = time.time()
                self.odometry.compute_odometry(left_speed, right_speed, current_time - prev_time)
                prev_time = current_time
                current_theta = self.odometry.get_orientation()
                error = theta - current_theta

                consigne = self.Kp_theta * error

                self.motors.move(-consigne, +consigne)

        except KeyboardInterrupt:
            print("Stopped")
            return


def circuit(color=None, speed=500, time_coef=1):
    """
    Function for realizing circuit without odometry
    :param color: RED, BLUE or None (entire circuit)
    :param speed: Average speed for motors
    :param time_coef: coefficient for time
    :return: None
    """
    if color is None:
        firstbot = Robot(speed)
        print("Let's Go !")
        color = Color.BLUE
        running_time = 35.5 * time_coef
        firstbot.tick_tock(color, running_time)
        firstbot.motors.stop()
        print("Ending \033[34mBLUE\033[0m circuit")
        color = Color.RED
        running_time = 4.7 * time_coef
        firstbot.tick_tock(color, running_time)
        firstbot.motors.move(30, 580)
        time.sleep(0.5)
        color = Color.RED
        running_time = 35.5 * time_coef
        firstbot.tick_tock(color, running_time)
        firstbot.motors.stop()
        print("Ending \033[31mRED\033[0m circuit")

    elif color == "RED":
        print("Follow \033[31mRED\033[0m line")
        try:
            while True:
                firstbot = Robot(speed)
                color = Color.RED
                running_time = 6.5 * time_coef
                firstbot.tick_tock(color, running_time)
                firstbot.motors.move(0, 640)
                time.sleep(0.5)
                color = Color.RED
                running_time = 35.5 * time_coef
                firstbot.tick_tock(color, running_time)
        except KeyboardInterrupt:
            exit()

    elif color == "BLUE":
        print("Follow \033[34mBLUE\033[0m line")
        firstbot = Robot(speed)
        color = Color.BLUE
        running_time = 2000 * time_coef
        firstbot.tick_tock(color, running_time)


def circuit_odometry(color=None, speed=500, time_coef=1.1):
    """
    Function for realizing circuit with odometry
    :param color: RED, BLUE or None (entire circuit)
    :param speed: Average speed for motors
    :param time_coef: coefficient for time
    :return: None
    """
    if color is None:
        firstbot = Robot(speed)
        print("Let's Go !")
        color = Color.BLUE
        running_time = 35 * time_coef
        firstbot.tick_tock_odometry(color, running_time, firstbot.odometry)
        firstbot.motors.stop()
        print("Ending \033[34mBLUE\033[0m circuit")
        color = Color.RED
        running_time = 4.7 * time_coef
        firstbot.tick_tock_odometry(color, running_time, firstbot.odometry)
        firstbot.motors.move(30, 580)
        time.sleep(0.5)
        color = Color.RED
        running_time = 35.5 * time_coef
        firstbot.tick_tock_odometry(color, running_time, firstbot.odometry)
        firstbot.motors.stop()
        print("Ending \033[31mRED\033[0m circuit")

    elif color == "RED":
        print("Follow \033[31mRED\033[0m line")
        try:
            while True:
                firstbot = Robot(speed)
                color = Color.RED
                running_time = 35.5 * time_coef
                firstbot.tick_tock_odometry(color, running_time, firstbot.odometry)
                firstbot.motors.stop()
        except KeyboardInterrupt:
            exit()

    elif color == "BLUE":
        print("Follow \033[34mBLUE\033[0m line")
        firstbot = Robot(speed)
        color = Color.BLUE
        running_time = 35 * time_coef
        firstbot.tick_tock_odometry(color, running_time, firstbot.odometry)


def compliant_odometry():
    """
    Put robot in compliant mode and then display current odometry
    :return: None
    """
    robot = Robot(500)
    robot.motors.compliant()
    prev_time = time.time()
    while True:
        time.sleep(0.01)
        speed = robot.motors.get_speed()
        left_speed = speed[0]
        right_speed = -speed[1]
        current_time = time.time()
        robot.odometry.compute_odometry(left_speed, right_speed, current_time - prev_time)
        prev_time = current_time

        print("X = ", robot.odometry.get_x() / 10)
        print("Y = ", robot.odometry.get_y() / 10)
        print("THETA = ", math.degrees(robot.odometry.get_orientation()))
        print(" ")


if __name__ == "__main__":
    print(sys.argv)
    if sys.argv[1] == "C":
        if len(sys.argv) < 3:
            circuit()
        else:
            circuit(sys.argv[2])
    elif sys.argv[1] == "O":
        compliant_odometry()
    elif sys.argv[1] == "CO":
        if len(sys.argv) < 3:
            circuit_odometry()
        else:
            circuit_odometry(sys.argv[2])
    else:
        robot = Robot(500)
        robot.go_to(int(sys.argv[1]), int(sys.argv[2]), int(sys.argv[3]))
