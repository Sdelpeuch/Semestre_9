%-------------------------------------------------------
% solution d'une equation de type 1
%--------------------------------------------------------------
  function S=solve_type_1(X,Y)  
    S=struct();S.name='equation de type 1 :X.Li=Y';
    S.X=X;
    S.Y=Y;
    if ((X==0)&(Y==0)) 
      S.well_posed=0;% equation mal posee
      S.nb_sols=inf; % infinite de solutions
      return;
    end
    S.well_posed=1;% equation mal posee
    if (X==0) 
      S.nb_sols=0; 
      S.Li=[];
      return
    end
    S.nb_sols=1;
    S.Li=Y/X;
  end

  