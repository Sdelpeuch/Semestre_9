%clear all; clf;
%
%% Define constants
%U=2;
%r1=2;
%r2=2;
%l=[r1;r2];
%c1O=[0;0];
%c2O=[U;0];
%
%% Define circles
%circle(c1O(1,1), c1O(2,1), r1);
%circle(c2O(1,1), c2O(2,1), r2);
%
%% Convert initial coordonates to world coordonates
%c1W=[0;0];
%theta = atan2((c2O(2,1)-c1O(2,1)),(c2O(1,1)-c1O(1,1)));
%R = [cos(theta) -sin(theta); sin(theta) cos(theta)];
%T = c1W;
%c1W = R*c1O + T;
%c2W = R*c2O + T;
%cW = [c1W';c2W'];
%solutionW = intersection2cercles_exact(cW,l)

clear ; close all; clf;
hold on;

syms x y r1 r2;
c1=[0 1]; %coordonnées cercle 1
c2=[1 0];  %coordonnées cercle 2
r=[3 3]; % rayon cercle 1 puis rayon cercle 2
c = [c1;c2];
cp1=[0 0];
cp2=[norm(c2-c1) 0];

circle(c1(1),c1(2), r(1));
circle(c2(1),c2(2), r(2));
[sol1, err, it]=newton(cp1,c,r, 1000, 10^-6);
[sol2, err, it]=newton(cp2,c,r, 1000, 10^-6);

sol1, sol2

plot(sol1(1),sol1(2),'+b')
plot(sol2(1),sol2(2),'+b')