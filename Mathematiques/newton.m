function [sol,err,iter, xx] = newton(p, c, l, maxiter, precision)
    X=p';
    [F,J] = circle_equation(p,c,l);
    err=norm(F);
    iter=0;
    xx=[];
    while err>precision && iter<maxiter
        [F,J]= circle_equation(X,c,l);
        iter=iter+1;
        err=norm(F);
        X = X - J\F;
        xx = [xx X];

    end
    sol = X';
end

function [F,J]=circle_equation(p,c,l)
    [n,m]=size(c);
    F=[];
    J=[];
    for i=1:n
        F=[F;sqrt((p(1)-c(i,1))^2+(p(2)-c(i,2))^2)-l(i)];
        J=[J;(p(1)-c(i,1))/l(i) (p(2)-c(i,2))/l(i)];
    end
end
