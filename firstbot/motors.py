"""
File for dynamixel motors control
"""
import time

import pypot.dynamixel


class Motors:
    """
    Class to define motor and communication with dynamixel
    """
    dxl_io = None

    def __init__(self):
        ports = pypot.dynamixel.get_available_ports()
        if not ports:
            exit('No port')

        self.dxl_io = pypot.dynamixel.DxlIO(ports[0])
        self.dxl_io.set_wheel_mode([1])

        self.left = 2
        self.right = 1

    def move(self, left_move, right_move):
        """
        Send instruction to motors
        :param left_move: laps per seconds (-720 / 720)
        :param right_move:laps per seconds (-720 / 720)
        :return: None
        """

        self.dxl_io.set_moving_speed({self.left: left_move})
        self.dxl_io.set_moving_speed({self.right: (-1) * right_move})

    def stop(self):
        """
        Send stop instruction to motors
        :return: None
        """
        self.dxl_io.set_moving_speed({self.left: 0})
        self.dxl_io.set_moving_speed({self.right: 0})

    def get_speed(self):
        """
        Get the actual speed of the motors
        :return:
        """
        return self.dxl_io.get_present_speed([self.left, self.right])  # in degrees / s

    def compliant(self):
        """
        Disable torque on motors
        :return:
        """
        self.dxl_io.disable_torque([self.left, self.right])

    def noncompliant(self):
        """
        Enable torque on motors
        :return:
        """
        self.dxl_io.enable_torque([self.left, self.right])

    
    def __del__(self):
        self.stop()


if __name__ == "__main__":
    bot = Motors()

    left_speed = int(input("Enter left speed: \n"))
    right_speed = int(input("Enter right speed: \n"))

    bot.move(left_speed, right_speed)

    time.sleep(10)

    bot.stop()
