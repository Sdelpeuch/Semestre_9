import math
import time

from motors import Motors

class Odometry:
    #entra = 121.8
    entra = 128
    radius = 25.95
    x_pos = 0
    y_pos = 0
    orientation = 0

    def convert_degrees_meters(self, left_degrees, right_degrees):
        angular_speed_left = math.radians(left_degrees)
        angular_speed_right = math.radians(right_degrees)

        linear_speed_left = angular_speed_left * self.radius
        linear_speed_right = angular_speed_right * self.radius

        return linear_speed_left, linear_speed_right

    def compute_odometry(self, left_speed_degrees, right_speed_degrees, delta_time):
        linear_speed_left, linear_speed_right = self.convert_degrees_meters(left_speed_degrees, right_speed_degrees)
        if not linear_speed_left == linear_speed_right:
            phi = (linear_speed_right * delta_time - linear_speed_left * delta_time) / self.entra
            r_center = (linear_speed_left / (linear_speed_right - linear_speed_left) + 0.5) * self.entra

            self.x_pos = self.x_pos + r_center * (-math.sin(self.orientation) + math.sin(phi) * math.cos(self.orientation) + math.sin(self.orientation) * math.cos(phi))
            self.y_pos = self.y_pos + r_center * (math.cos(self.orientation) - math.cos(phi) * math.cos(self.orientation) + math.sin(self.orientation) * math.sin(phi))
            self.orientation = self.orientation + phi
        else:
            norm = linear_speed_left * delta_time
            self.x_pos = self.x_pos + norm * math.cos(self.orientation)
            self.y_pos = self.y_pos + norm * math.sin(self.orientation)

    def get_x(self):
        return self.x_pos

    def get_y(self):
        return self.y_pos

    def get_orientation(self):
        return self.orientation


if __name__ == "__main__":
    motors = Motors()
    odometry = Odometry()
    prevTime = time.time()
    motors.compliant()
    while True:
        time.sleep(0.01)
        speed = motors.get_speed()
        leftSpeed = speed[0]
        rightSpeed = speed[1]
        odometry.compute_odometry(leftSpeed, rightSpeed, time.time() - prevTime)
        prevTime = time.time()

        print(odometry.get_x())
        print(odometry.get_y())
        print(math.degrees(odometry.get_orientation()))
        print(" ")
