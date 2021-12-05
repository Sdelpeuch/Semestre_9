%--------------------------------------------------------------
% rotation de theta autour de l'axe u ( formule de Rodrigues )
%--------------------------------------------------------------
  function T=get_rot_u(U,theta)
    if (nargin <2),
       theta=norm(U);
       if (theta>0)
           U=U/theta;    
       end
    end    
    c=cos(theta);
    s=sin(theta);
    S=[[  0       ,-U(3)  , U(2) ];...
           [ U(3) , 0         ,-U(1) ];...
          [ -U(2) ,U(1)   ,      0  ]];
    R=U*U.'*(1-c) +eye(3,3)*c+S*s;
    T=[R,[0;0;0]];
    T=[T;[0,0,0,1]];
  end