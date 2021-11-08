from sympy import *


def rot_z(theta):
    """
    This function compute a rotation by a theta angle around z axis
    :param theta: the angle
    :return: a 4x4 rotation matrix
    """
    return Matrix([[cos(theta), -sin(theta), 0, 0],
                   [sin(theta), cos(theta), 0, 0],
                   [0, 0, 1, 0],
                   [0, 0, 0, 1]])


def rot_y(theta):
    """
    This function compute a rotation by a theta angle around y axis
    :param theta: the angle
    :return: a 4x4 rotation matrix
    """
    return Matrix([[cos(theta), 0, sin(theta), 0],
                   [0, 1, 0, 0],
                   [-sin(theta), 0, cos(theta), 0],
                   [0, 0, 0, 1]])


def rot_x(theta):
    """
    This function compute a rotation by a theta angle around x axis
    :param theta: the angle
    :return: a 4x4 rotation matrix
    """
    return Matrix([[1, 0, 0, 0],
                   [0, cos(theta), -sin(theta), 0],
                   [0, sin(theta), cos(theta), 0],
                   [0, 0, 0, 1]])


def trans(l_x, l_y, l_z):
    """
    This function compute a translation by l_x l_y l_z
    :param l_z: translation in z direction
    :param l_y: translation in y direction
    :param l_x: translation in x direction
    :return: a 4x4 translation matrix
    """
    return Matrix([[1, 0, 0, l_x],
                   [0, 1, 0, l_y],
                   [0, 0, 1, l_z],
                   [0, 0, 0, 1]
                   ])