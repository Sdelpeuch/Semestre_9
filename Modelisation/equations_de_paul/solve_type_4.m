%--------------------------------------------------------------
% solution d'une equation de type 4
%--------------------------------------------------------------
  function S=solve_type_4(X1,Y1,X2,Y2)
    S=struct();S.name='equation de type 4 :[1]X1.Rj.sin(Ai)=Y1 ;[2] X2.Rj.cos(Ai)=Y2';
    S.X1=X1;
    S.Y1=Y1;
    S.X2=X2;
    S.Y2=Y2;
    well_posed_1=1;
    if (abs( X1) ==0) 
      well_posed_1=0;
      if (abs(Y1) ==0 ) 
        S.nb_sols=inf;
      else
        S.nb_sols=0;
      end
    end
    well_posed_2=1;
    if (abs( X2) ==0) 
      well_posed_2=0;
      if (abs(Y2) ==0 ) 
        S.nb_sols=inf;
      else
        S.nb_sols=0;
      end
    end
    S.well_posed=well_posed_1 & well_posed_2;
    if (S.well_posed == 0) 
      return;
    end
    Rj=(X2^2*Y1^2 + X1^2 *Y2 ^2)/(X1^2 * X2 ^2);
    Rj=sqrt(Rj);
    S.Rj=[Rj,-Rj];
    S.nb_sols=length(S.Rj);
    S.Ai=zeros(S.nb_sols,1);
    for n=1:S.nb_sols,
      Rj=S.Rj(n);
      Ai=atan2( Y1 * sign( X1 * Rj ) , Y2 * sign ( X2 * Rj ) ) ;
      S.Ai(n)=Ai;
      S.verif_1(n)=X1*Rj*sin(Ai)-Y1;
      S.verif_2(n)=X2*Rj*cos(Ai)-Y2;
    end
    S.Ai=get_arg_nearest_zero(S.Ai);
  % les 2 solutions de sinc(alpha+A)=cte sont  A1 =asin(cte)-alpha, et A2 =pi - asin(cte) -alpha
  end

  