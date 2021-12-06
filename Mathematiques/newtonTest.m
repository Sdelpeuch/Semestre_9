function newtonTest(sol1, sol2, c, r, eps, maxiter)
    sol1
    sol2
    for i=-10:0.1:10
        for j=-10:0.1:10
            cp=[i,j];
            [sol,err,iter, xx] = newton(cp, c, r, maxiter, eps);
            if norm(sol-sol1)<0.1
                plot(i,j, 'r+');
            elseif norm(sol-sol2)<0.1
                plot(i,j, 'b+');
            else
                plot(i,j, 'g+');
            end
        end
    end
    title('Newton Method')
    shg()
end