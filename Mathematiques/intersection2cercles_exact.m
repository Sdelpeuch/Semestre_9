function [sol] = intersection2cercles_exact(c,l)
e=c(2,1)-c(1,1);
f=c(2,2)-c(1,2);
sol=[];

if e==0 | f==0
    if e==0 & f==0
        sol=[];
    else
        if e==0
            y=(l(1)^2-l(2)^2-e^2+f^2)/(2*f)
            if l(1)^2-y^2 < 0
                sol=[];
            else
                sol1=[sqrt(l(1)^2-y^2) y]+ c(1,:);
                sol2=[-sqrt(l(1)^2-y^2) y]+ c(1,:);
                sol=[sol1;sol2];
            end
        else
            x=(l(1)^2-l(2)^2+e^2+f^2)/(2*e);
            if l(1)^2-x^2 < 0
                sol=[];
            else
                sol1=[x sqrt(l(1)^2-x^2)]+c(1,:);
                sol2=[x -sqrt(l(1)^2-x^2)]+c(1,:);
                sol=[sol1;sol2];
            end
        end
    end
end 


