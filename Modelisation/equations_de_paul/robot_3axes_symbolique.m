clear all;
close all;
syms th1 th2 th3 d1 a2 a3 D3;
D3 = 0;
Pi = sym(pi);
x0T1 = get_dh(th1, 0, d1, - Pi/2);
x1T2 = get_dh(th2, a2, 0, 0);
x2T3 = get_dh(th3, a3, 0, 0);
x0T3 = x0T1 * x1T2 * x2T3;

x3Ot = [0; -D3/2; 0]; % Position initiale
syms x0 y0 z0;
x0Otd = [x0; y0; z0]; % Objectif
x0Ot = x0T3(1:3, :) * [x3Ot; 1];
% simplify(x0Ot) == simplify(x0Otd) % Trop d'inconnues dans les équations

x1T0 = get_InvT(x0T1);
x1Otd = x1T0(1:3, :) * [x0Otd; 1];
x1T3 = x1T2 * x2T3;
x1Ot = x1T3(1:3, :) * [x3Ot; 1];
eq = simplify(x1Ot) == simplify(x1Otd) % Equations que l'on sait résoudre
matlabFunction(x0T1, x1T2, x2T3, 'File', 'MGDrobot', 'vars', [th1, th2, th3, d1, a2, a3])