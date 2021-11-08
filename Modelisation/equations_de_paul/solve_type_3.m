%--------------------------------------------------------------
% solution d'une equation de type 3
%--------------------------------------------------------------
  function S=solve_type_3(X1,Y1,Z1,X2,Y2,Z2)
    S=struct();S.name='equation de type 3 :[1] X1.sin(Ai)+Y1.cos(Ai)=Z1;[2] X2.sin(Ai)+Y2.cos(Ai)=Z2';
    S.X1=X1;
    S.Y1=Y1;
    S.Z1=Z1;
    S.X2=X2;
    S.Y2=Y2;
    S.Z2=Z2;
    S.sol_type_2_x1y1z1=solve_type_2(X1,Y1,Z1);
    S.sol_type_2_x2y2z2=solve_type_2(X2,Y2,Z2);
    S.well_posed=S.sol_type_2_x1y1z1.well_posed & S.sol_type_2_x2y2z2.well_posed;
    S.nb_sols=min(S.sol_type_2_x1y1z1.nb_sols,S.sol_type_2_x2y2z2.nb_sols);
    if (S.well_posed==0) 
      return;
    end
    S_1=S.sol_type_2_x1y1z1;
    S_2=S.sol_type_2_x2y2z2;
    A1=S_1.Ai;
    A2=S_2.Ai;
  % intersection des angles
  % pour eviter les erreurs dues au modulo 2pi
  % on raisonne sur le module de la fiffrence z1-z2, avec z1=cos(A1)+i.sin(A1),z2=cos(A2)+i.sin(A2)
  % de plus comme numeriquement on n'obtiendra jamais l'egalite z1=z2, on se donne une tolerance
    tol=1e-6; % tolerance
    Ai=[]; %solutions initialisees a matice vide
    for i1=1:S_1.nb_sols,
      A1=S_1.Ai(i1);
      C1=cos(A1);S1=sin(A1);
      z1=C1+1i*S1;
      for i2=1:S_2.nb_sols,
	A2=S_2.Ai(i2);
	C2=cos(A2);S2=sin(A2);
	z2=C2+1i*S2;
        if (abs(z1-z2)<tol) 
        % on ajoute Ai aux solutions
          Ai=[Ai;A1];
        end
      end
    end
    S.nb_sols=length(Ai);
    S.Ai=Ai;
    S.Ai=get_arg_nearest_zero(S.Ai);
  end

  