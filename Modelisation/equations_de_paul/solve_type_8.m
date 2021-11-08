%--------------------------------------------------------------
% solution d'une equation de type 8
%--------------------------------------------------------------
  function S=solve_type_8(X,Y,Z1,Z2)
    S=struct();S.name='equation de type 8 :[1] X.cos (Ai)+Y.cos(Ak)=Z1;[2] X.sin(Ai)+Y.sin(Ak)=Z2';
    S.X=X;
    S.Y=Y;
    S.Z1=Z1;
    S.Z2=Z2;
   % parametres et resolution de l'equation de type 2 deduite de [1]^2+[2]^2
    XT2=-2*X*Z2;
    YT2=-2*X*Z1;
    ZT2=Y^2-X^2-Z1^2-Z2^2;
    S.sol_type_2=solve_type_2(XT2,YT2,ZT2);
    S.well_posed=S.sol_type_2.well_posed;
    S.nb_sols=S.sol_type_2.nb_sols;
    if (S.well_posed==0) 
      return;
    end
    S.Ai=S.sol_type_2.Ai;
    S.Ak=zeros(S.nb_sols,1);
    S.verif_1=zeros(S.nb_sols,1);
    S.verif_2=zeros(S.nb_sols,1);
    for n=1:S.nb_sols,
      Ai=S.Ai(n);
      im=Z2-X*sin(Ai);
      re=Z1-X*cos(Ai);
      Ak=atan2(im*sign(Y),re*sign(Y));
      S.Ak(n)=Ak;
      S.verif_1(n)=X * cos(Ai) + Y * cos(Ak) - Z1 ;
      S.verif_2(n)=X * sin(Ai) + Y * sin(Ak) - Z2 ;
    end
    S.Ai=get_arg_nearest_zero(S.Ai);
    S.Ak=get_arg_nearest_zero(S.Ak);
  end
  
  