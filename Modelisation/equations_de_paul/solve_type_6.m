
%--------------------------------------------------------------
% solution d'une equation de type 6
%--------------------------------------------------------------
   function S=solve_type_6(W,X,Y,Z1,Z2)
     S=struct();S.name='equation de type 6 :[1] W.sin (Ak)=X.cos(Ai)+Y.sin(Ai)+Z1;[2] W.cos(Ak)=X.sin(Ai)-Y.cos(Ai)+Z2';
     S.W=W;
     S.X=X;
     S.Y=Y;
     S.Z1=Z1;
     S.Z2=Z2;
    % parametres et resolution de l'equation de type 2 deduite de [1]^2+[2]^2
     ZT2=W^2-Z1^2-Z2^2-X^2-Y^2;
     XT2=2*X*Z2+2*Y*Z1;
     YT2=2*X*Z1-2*Y*Z2;
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
       im=X*cos(Ai)+Y*sin(Ai)+Z1;
       re=X*sin(Ai)-Y*cos(Ai)+Z2;
       Ak=atan2(im*sign(W),re*sign(W));
       S.Ak(n)=Ak;
       S.verif_square(n)=( X*cos(Ai)+Y*sin(Ai)+Z1 )^2+( X*sin(Ai)-Y*cos(Ai)+Z2 )^2;
       S.verif_1(n)=W * sin(Ak) - ( X*cos(Ai)+Y*sin(Ai)+Z1 );
       S.verif_2(n)=W * cos(Ak) - ( X*sin(Ai)-Y*cos(Ai)+Z2 );
     end
     S.Ai=get_arg_nearest_zero(S.Ai);
     S.Ak=get_arg_nearest_zero(S.Ak);
   end

  