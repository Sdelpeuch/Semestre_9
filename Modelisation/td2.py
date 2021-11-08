"""Sujet : sdelpeuch.github.io/assets/pdf/semestre9/modelisation/exo2.1.pdf"""

from tool import *
from sympy import *

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


if __name__ == '__main__':
    scara()
