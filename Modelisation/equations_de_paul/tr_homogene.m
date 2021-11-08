1; % indispensable sous octave si on veut plusieurs fonctions dans le meme fichier
%--------------------------------------------------------------
% rotation  autour de l'axe x
%--------------------------------------------------------------
  function T=get_rot_x(theta_rad)
    c=cos(theta_rad); s=sin(theta_rad);
    T=[[ 1, 0, 0,0]
       [ 0, c,-s,0]
       [ 0, s, c,0]       
       [ 0, 0, 0,1]       
      ]; 
  end
%--------------------------------------------------------------
% rotation autour de l'axe y
%--------------------------------------------------------------
  function T=get_rot_y(theta_rad)
    c=cos(theta_rad); s=sin(theta_rad);
    T=[[ c, 0, s,0]
       [ 0, 1, 0,0]
       [-s, 0, c,0]       
       [ 0, 0, 0,1]       
      ]; 
  end
%--------------------------------------------------------------
% rotation autour de l'axe z
%--------------------------------------------------------------
  function T=get_rot_z(theta_rad)
    c=cos(theta_rad); s=sin(theta_rad);
    T=[[ c,-s, 0,0]
       [ s, c, 0,0]
       [ 0, 0, 1,0]       
       [ 0, 0, 0,1]       
      ]; 
  end
%--------------------------------------------------------------
% Translation Lx,Ly,Lz le long des axes X,Y,Z
%--------------------------------------------------------------
  function T=get_trans(Lx,Ly,Lz)
    T=[[ 1, 0, 0,Lx]
       [ 0, 1, 0,Ly]
       [ 0, 0, 1,Lz]       
       [ 0, 0, 0,1]       
      ]; 
  end
%--------------------------------------------------------------
% rotation de theta autour de l'axe u ( formule de Rodrigues )
%--------------------------------------------------------------
  function T=get_rot_u(U,theta)
    c=cos(theta);
    s=sin(theta);
    R=U*U.'*(1-c) +eye(3,3)*c+get_S_from_U(U)*s
    T=[R,[0;0;0]];
    T=[T;[0,0,0,1]];
  end

%--------------------------------------------------------------
% repere [xj,yj,zj] suivant  [xi,yi,zi]
%--------------------------------------------------------------
  function rij=get_R(Tij)
    rij=Tij(1:3,1:3);
  end
%---------------------------------------------
% origine repere j exprimee dans le repere i
%---------------------------------------------
  function oij=get_O(Tij)
    oij=Tij(1:3,4);
  end
%-----------------------------------------------------------------------------
% renvoie la matrice anti symetrique liée au produit vectoriel a gauche par u
%-----------------------------------------------------------------------------
  function S=get_S_from_U(u)
    ux=u(1);uy=u(2);uz=u(3);
    S=[ [0  ,-uz,uy ]
        [uz ,0  ,-ux]
        [-uy,ux ,0  ]        
      ];        
  end
%-----------------------------------------------------------------------------
% coordonnees du point P dans le repere i, en fonction de ses coordonnees dans le repere j
%--------------------------------------------------------------
  function Pi=get_Pi(Tij,pj)
    pj_1=[pj;1];   % on rajoute un 1 en dessous de Pj, pour former pj_1
    pi_1=Tij*pj_1;
    Pi=pi_1(1:3,1);
  end
%--------------------------------------------------------------
% coordonnees du vecteur V dans le repere i, en fonction de ses coordonnees dans le repere j
%--------------------------------------------------------------
  function vi=get_Vi(Tij,vj)
    vj_0=[vj;0];   % on rajoute un 0 en dessous de vj, pour former vj_0
    vi_0=Tij*vj_0;
    vi=vi_0(1:3,1);
  end
%--------------------------------------------------------------
% matrice de transformation homogene inverse
%--------------------------------------------------------------
  function Tji=get_InvT(Tij)
    Oij=Tij(1:3,4);   % origine repere j exprimee dans repere i= Tij, lignes 1 a 3, colonne 4
    Rij=Tij(1:3,1:3); % Rij=vecteurs [xj,yj,zj] exprimes suivant [xi,yi,zi]=Tij lignes 1 a 3, colonnes 1 a 3
    Rji=Rij.';         % Rji=vecteurs [xi,yi,zi] exprimes suivant [xj,yj,zj] = transposee de Rij
    Oji=-Rji*Oij;     % Oji = origine repere i exprimee dans repere j = Rji . [-Oij]
    Tji=[[ Rji,Oji];[0,0,0,1 ] ];
  end
