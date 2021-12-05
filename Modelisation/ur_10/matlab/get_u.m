%--------------------------------------------------------------
% renvoie le vecteur angle axe correspondant a une rotation R de theta autour de l'axe u ( formule de Rodrigues )
%--------------------------------------------------------------
function [u,th_out]=get_u(R)
th=acos((R(1,1)+R(2,2)+R(3,3)-1)/2);
if (nargout>1)
    th_out=th
end
% cas particulier theta =0
if (abs(th)<1e-14),
    if (nargout>1),
        u=[1;0;0]; th_out=0;
    else
        u=[0;0;0];
    end
    return
end
% cas particulier theta=pi
if (abs(th-pi)<1e-14),
    u=zeros(3,1);
    % rotation de +pi (du coup le sens de l'axe est arbitraire)
    abs_ux=sqrt(max(0,abs(R(1,1)+1)/2)); % 2.ux^2-1=R11
    abs_uy=sqrt(max(0,abs(R(2,2)+1)/2)); % 2.uy^2-1=R22
    abs_uz=sqrt(max(0,abs(R(3,3)+1)/2)); % 2.uz^2-1=R33
    % choix arbitraire : plus grande composante>0
    [mx,k0]=max([abs_ux,abs_uy,abs_uz]);
    u(k0)=mx;
    k1=k0+1;if (k1>3) k1=k1-3; end
    k2=k1;if (k2>3) k2=k2-3; end
    u(k1)=R(k0,k1)/(2* u(k0)) ;% R(k0,k1) =2*u(k0)*u(k1)
    u(k2)=R(k0,k2)/(2* u(k0)) ;% R(k0,k2) =2*u(k0)*u(k2)
    if (nargout>1),
        u=u/norm(u); th_out=pi;
    else
        u=u*pi/norm(u);
    end
    return
end
% cas general
c=cos(th);
s=sin(th);

u(1,1)=(R(3,2)-R(2,3))/(2*s);
u(2,1)=(R(1,3)-R(3,1))/(2*s);
u(3,1)=(R(2,1)-R(1,2))/(2*s);
if (nargout==1),
    u=u*th;
end

end