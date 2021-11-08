
%--------------------------------------------------------------
% solution d'une equation de type 7
%--------------------------------------------------------------
  function S=solve_type_7(W1,W2,X,Y,Z1,Z2)
    S=struct();S.name='equation de type 7 :[1] W2.sin(Ak)+W1.cos(Ak) =X.cos(Ai)+Y.sin(Ai)+Z1;[2] W2.cos(Ak) - W1. sin (Ak)=X.sin(Ai)-Y.cos(Ai)+Z2';
    S.W1=W1;
    S.W2=W2;S.X=X;S.Y=Y;S.Z1=Z1;S.Z2=Z2;
    S.W=sqrt(W1^2+W2^2);
    S.alpha=atan2(W1,W2);
    S.sol_type_6=solve_type_6(S.W,S.X,S.Y,S.Z1,S.Z2);
    S.well_posed=S.sol_type_6.well_posed;
    S.nb_sols=S.sol_type_6.nb_sols;
    if (S.well_posed==0) 
      return;
    end
    S.Ai=S.sol_type_6.Ai;
    S.Ak=S.sol_type_6.Ak-S.alpha;
    S.verif_1=zeros(S.nb_sols,1);
    S.verif_2=zeros(S.nb_sols,1);
    for n=1:S.nb_sols,
      Ai=S.Ai(n);
      Ak=S.Ak(n);
      S.verif_1(n)=  W1 * cos(Ak)   + W2 * sin(Ak) - ( X * cos(Ai) + Y * sin(Ai) + Z1 );
      S.verif_2(n)=(-W1 * sin(Ak) ) + W2 * cos(Ak) - ( X * sin(Ai) - Y * cos(Ai) + Z2 );
    end
    S.Ai=get_arg_nearest_zero(S.Ai);
    S.Ak=get_arg_nearest_zero(S.Ak);
  end

  