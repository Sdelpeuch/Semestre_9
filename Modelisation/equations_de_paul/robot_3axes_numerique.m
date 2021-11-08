clear all;
close all;

x0 = 1;
y0 = 0.5;
z0 = 2;
L0 = 1;
L1 = 1;
L2 = 1;
L3 = 1;
d1 = L0 + L1;
a2 = L2;
a3 = L3;

th123 = [];

sol_eq3 = solve_type_2(-x0, y0, 0);

for i=1:length(sol_eq3.Ai)
    % ligne 3 -> th1
    th1 = sol_eq3.Ai(i);
    % eq de type 8 en Ai = th2 et Ak = th2 + th3
    Z1 = x0 * cos(th1) + y0 * sin(th1);
    Z2 = d1 - z0;
    X = a2;
    Y = a3;
    sol_eq12 = solve_type_8(X, Y, Z1, Z2);
    for j=1:length(sol_eq12.Ai)
        th2 = sol_eq12.Ai(j);
        th23 = sol_eq12.Ak(j);
        th3 = th23 - th2;
        th123 = [th123, [th1; th2; th3]];
    end
end

th123

% Vérification du MGD pour tous les triplets [th1; th2; th3]
% on voulait que 0OT = [x0; y0; z0]
[m,n] = size(th123);
for j=1:n
    th1 = th123(1,j);
    th2 = th123(2,j);
    th3 = th123(3,j);
    [x0T1, x1t2, x2T3] = MGDrobot(th1, th2, th3, d1, a2, a3)
    % on en déduit x0, y0, z0 = coordonnées de l'outil dans le repère 0
    x3Ot = [0;0;0];
    x0T3 = x0T1 * x1T2 * x2T3;
    x0Ot = x0T3(1:3, :) * [x3Ot;1]
end