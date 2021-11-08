"""Sujet : sdelpeuch.github.io/assets/pdf/semestre9/modelisation/exo2.2.pdf"""

from tool import *
from sympy import *

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
    T_0_1 = rot_z(theta_1) * (trans(0, 0, L_0 + L_1)) * (rot_x(-pi / 2))
    T_1_2 = rot_z(theta_2) * (trans(L_2, 0, 0)) * (rot_x(0))
    T_2_3 = rot_z(theta_3) * (trans(0, 0, 0)) * (rot_x(-pi / 2))
    T_3_4 = rot_z(theta_4) * (trans(0, 0, d_4)) * (rot_x(-pi / 2))
    T_4_5 = rot_z(theta_5) * (trans(0, 0, 0)) * (rot_x(-pi / 2))
    T_5_6 = rot_z(theta_5) * (trans(0, 0, 0)) * (rot_x(0))
    T_0_6 = T_0_1 * T_1_2 * T_2_3 * T_3_4 * T_4_5 * T_5_6
    print(T_0_6)

if __name__ == '__main__':
    abb()
