
%--------------------------------------------------------------
% solution d'une equation de type 5
%--------------------------------------------------------------
  function S=solve_type_5(X1,Y1,Z1,X2,Y2,Z2)
    S=struct();S.name='equation de type 5 :[1]X1.sin(Ai)=Y1 +Z1 .Rj ;[2] X2. cos(Ai)=Y2 + Z2 . Rj ';
    S.X1=X1;
    S.Y1=Y1;
    S.Z1=Z1;
    S.X2=X2;
    S.Y2=Y2;
    Z.Z2=Z2;
    well_posed_1=1;
    if (abs( X1) ==0) 
      well_posed_1=0;
      S.nb_sols=inf;
    end
    well_posed_2=1;
    if (abs( X2) ==0) 
      well_posed_2=0;
      S.nb_sols=inf;
    end
    S.well_posed=well_posed_1 & well_posed_2;
    if (S.well_posed == 0) 
      return;
    end
    S.a0= X2^2 * Y1 ^2 + X1^2 * Y2^2 - X1^2 * X2^2;
    S.a1=2 * ( X2^2 * Y1 * Z1 + X1^2 * Y2 * Z2 );
    S.a2=X2^2 * Z1^2 + X1^2 * Z2^2;
    if (S.a2==0) 
    % ordre 1
      S.well_posed=S.a1~=0;
      if (S.well_posed==0) 
        S.nb_sols=0;
        return;
      end
      S.Rj=-S.a0/S.a1;
    else
    % ordre 2
      S.delta=S.a1^2 - 4 * S.a2 * S.a0;
      if (S.delta<0) 
      % pas de solutions
       S.Rj=[];
      end
      if (S.delta==0) 
      % 1 solution
        S.Rj=-S.a1/( 2 * S.a2);
      end
      if (S.delta>0) 
      % 2 solutions
        S.Rj1 = ( -S.a1 - sqrt( S.delta) ) / ( 2 * S.a2);
        S.Rj2 = ( -S.a1 + sqrt( S.delta) ) / ( 2 * S.a2);
        S.Rj=[S.Rj1;S.Rj2];
      end
    end % else if S.a2==0
    S.nb_sols=length(S.Rj);
    S.Ai=zeros(S.nb_sols,1);
    S.verif_1=zeros(S.nb_sols,1);
    S.verif_2=zeros(S.nb_sols,1);
    for n=1:S.nb_sols,
      Rj = S.Rj(n);
      im = ( Y1 + Z1 * Rj ) / X1;
      re = ( Y2 + Z2 * Rj ) / X2;
      Ai=atan2( im , re ) ;
      S.Ai(n)=Ai;
      S.verif_1(n)=X1*sin(Ai)- ( Y1 + Z1 * Rj );
      S.verif_2(n)=X2*cos(Ai)- ( Y2 + Z2 * Rj );
    end
    S.Ai=get_arg_nearest_zero(S.Ai);
  end

  