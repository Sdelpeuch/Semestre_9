clear all; clf; 

U=2;
r1=1;
r2=2;
l=[r1;r2];
c1O=[0;0];
c2O=[U;0];
cO=[c1O';c2O'];
circle(c1O(1,1), c1O(2,1), r1)
circle(c2O(1,1), c2O(2,1), r2)
c1W=[2;2];
solutionO = intersection2cercles_exact(cO,l)



if ~isempty(solutionO)
    teta = atan2((solutionO(2,2)-solutionO(1,2)),(solutionO(2,1)-solutionO(1,1)));
    R=[cos(teta) -sin(teta);sin(teta) cos(teta)];
    T=c1W;
    c1Wv=T+R*c1O;
    c2W=T+R*c2O;
else 
    disp("This case can't be solved")
end 
