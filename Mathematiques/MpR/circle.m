function circle(x,y,r)
hold on ;
axis equal;
xp=[];
yp=[];
for angle = 0:10:360
    xp=[xp r*cos(angle*pi/180)];
    yp=[yp r*sin(angle*pi/180)];
    angle
   
end
x+xp
y+xp
plot(x+xp,y+yp,'+');
