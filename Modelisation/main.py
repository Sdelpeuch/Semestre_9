# This is a sample Python script.

# Press Maj+F10 to execute it or replace it with your code.
# Press Double Shift to search everywhere for classes, files, tool windows, actions, and settings.
import numpy
from sympy import *


def rot_z(theta):
    return Matrix([[cos(theta), -sin(theta), 0, 0],
                   [sin(theta), cos(theta), 0, 0],
                   [0, 0, 1, 0],
                   [0, 0, 0, 1]])


def rot_y(theta):
    return Matrix([[cos(theta), 0, sin(theta), 0],
                   [0, 1, 0, 0],
                   [-sin(theta), 0, cos(theta), 0],
                   [0, 0, 0, 1]])


def rot_x(theta):
    return Matrix([[1, 0, 0, 0],
                   [0, cos(theta), -sin(theta), 0],
                   [0, sin(theta), cos(theta), 0],
                   [0, 0, 0, 1]])


def trans(l_x, l_y, l_z):
    return Matrix([[1, 0, 0, l_x],
                   [0, 1, 0, l_y],
                   [0, 0, 1, l_z],
                   [0, 0, 0, 1]
                   ])


def td1():
    theta_1 = Symbol('theta_1')
    theta_2 = Symbol('theta_2')
    theta_3 = Symbol('theta_3')
    alpha_1 = Symbol('alpha_1')
    alpha_2 = Symbol('alpha_2')
    alpha_3 = Symbol('alpha_3')
    a_1 = Symbol('a_1')
    a_2 = Symbol('a_2')
    a_3 = Symbol('a_3')
    d_1 = Symbol('d_1')
    d_2 = Symbol('d_2')
    d_3 = Symbol('d_3')
    D_3 = Symbol('D_3')
    x_0 = Symbol('x_0')
    y_0 = Symbol('y_0')
    z_0 = Symbol('z_0')
    O_0_T = Matrix([x_0], [y_0], [z_0])
    O_3_T = Matrix([0], [-D_3 / 2], [0])
    T_0_1 = rot_z(theta_1) * (trans(a_1, 0, d_1) * (rot_x(alpha_1)))
    T_1_2 = rot_z(theta_2) * (trans(a_2, 0, d_2) * (rot_x(alpha_2)))
    T_2_3 = rot_z(theta_3) * (trans(a_3, 0, d_3) * (rot_x(alpha_3)))
    T_0_3 = T_0_1 * (T_1_2 * (T_2_3))
    print(T_0_3)


def scara():
    theta_1 = Symbol('theta_1')
    theta_2 = Symbol('theta_2')
    theta_4 = Symbol('theta_4')
    x_0 = Symbol('x_0')
    y_0 = Symbol('y_0')
    z_0 = Symbol('z_0')
    L_1 = Symbol('L_1')
    L_2 = Symbol('L_2')
    L_3 = Symbol('L_3')
    d_3 = Symbol('d_3')
    T_0_1 = rot_z(theta_1) * (trans(L_1, 0, L_3)) * (rot_x(0))
    T_1_2 = rot_z(theta_2) * (trans(L_2, 0, 0)) * (rot_x(0))
    T_2_3 = rot_z(0) * (trans(0, 0, d_3)) * (rot_x(0))
    T_3_4 = rot_z(theta_4) * (trans(0, 0, 0)) * (rot_x(0))
    T_0_3 = T_0_1 * (T_1_2) * (T_2_3)
    T_0_4 = T_0_3 * (T_3_4)  # useless no translation
    print(T_0_3)
    eq = Eq(T_0_3 * Matrix([[x_0], [y_0], [z_0], [1]]), Matrix([[0], [0], [0], [1]]))
    print(solve(eq, (theta_1, theta_2, d_3)))

def abb():
    theta_1 = Symbol('theta_1')
    theta_2 = Symbol('theta_2')
    theta_3 = Symbol('theta_3')
    theta_4 = Symbol('theta_4')
    theta_5 = Symbol('theta_5')
    theta_6 = Symbol('theta_6')
    L_0 = Symbol('L_0')
    L_1 = Symbol('L_1')
    L_2 = Symbol('L_2')
    alpha_1 = Symbol('alpha_1')
    alpha_2 = Symbol('alpha_2')
    alpha_3 = Symbol('alpha_3')
    alpha_4 = Symbol('alpha_4')
    alpha_5 = Symbol('alpha_5')
    d_4 = Symbol('d_4')
    d_6 = Symbol('d_6')
    T_0_1 = rot_z(theta_1) * (trans(0, 0, L_0+L_1)) * (rot_x(-pi/2))
    T_1_2 = rot_z(theta_2) * (trans(L_2, 0, 0)) * (rot_x(0))
    T_2_3 = rot_z(theta_3) * (trans(0, 0, 0)) * (rot_x(-pi/2))
    T_3_4 = rot_z(theta_4) * (trans(0, 0, d_4)) * (rot_x(-pi/2))
    T_4_5 = rot_z(theta_5) * (trans(0, 0, 0)) * (rot_x(-pi/2))
    T_5_6 = rot_z(theta_5) * (trans(0, 0, 0)) * (rot_x(0))
    T_0_6 = T_0_1 * T_1_2 * T_2_3 * T_3_4 * T_4_5 * T_5_6
    print(T_0_6)


if __name__ == '__main__':
    # td1()
    # scara()
    abb()
