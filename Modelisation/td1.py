"""Sujet : sdelpeuch.github.io/assets/pdf/semestre9/modelisation/exo1.pdf"""

from tool import *
from sympy import *

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

if __name__ == '__main__':
    td1()
