%--------------------------------------------------------
% MODELES GEOMETRIQUES DIRECT ET INVERSE D'UN ROBOT UR10
%--------------------------------------------------------

clear all;close all;more off;
USE_OCTAVE=exist('OCTAVE_VERSION')>0;
if USE_OCTAVE
    pkg load symbolic;
end
%----------------------------------------------
% 1.1 Modele Geometrique direct T01,...,T56, et T10...T65
%-----------------------------------------------
disp('question 1.1 le modele geometrique direct est donne');
syms pi d1 a2 a3 d4 d5 d6; % parametres fixes
syms q1 q2 q3 q4 q5 q6;% degres de liberte
syms pi d1 a2 a3 d4 d5 d6; % parametres fixes
T01=get_rot_z(q1)*get_trans(0 ,0,d1)*get_rot_x(pi/2);T10=simplify(get_InvT(T01));
T12=get_rot_z(q2)*get_trans(a2,0,0 )*get_rot_x(0   );T21=simplify(get_InvT(T12));
T23=get_rot_z(q3)*get_trans(a3,0,0 )*get_rot_x(0   );T32=simplify(get_InvT(T23));
T34=get_rot_z(q4)*get_trans(0,0,d4 )*get_rot_x(pi/2);T43=simplify(get_InvT(T34));
T45=get_rot_z(q5)*get_trans(0,0,d5 )*get_rot_x(pi/2);T54=simplify(get_InvT(T45));
T56=get_rot_z(q6)*get_trans(0,0,d6 )*get_rot_x(0   );T65=simplify(get_InvT(T56));
func_MGD=matlabFunction(T01,T12,T23,T34,T45,T56,'File','MGD_ur10','Vars',[q1;q2;q3;q4;q5;q6;d1;a2;a3;d4;d5;d6;pi]);
% a completer : calcul de T02 a T06 et inverses (utiliser eventuellement la fonction simplify )
T02=T01 * T12;T20=simplify(get_InvT(T02));
T03=T02 * T23;T30=simplify(get_InvT(T03));
T04=T03 * T34;T40=simplify(get_InvT(T04));
T05=T04 * T45;T50=simplify(get_InvT(T05));
T06=T05 * T56;T60=simplify(get_InvT(T06))
% a analyser : calcul de T01 a T06 pour le point de repos
q      =[q1  ;q2  ;q3  ;q4  ;q5 ;q6];
q_repos=[pi/2;pi/2;0   ;pi/2;0  ;0 ];
T01_repos=simplify(subs(T01,q,q_repos))
T02_repos=simplify(subs(T02,q,q_repos))
T03_repos=simplify(subs(T03,q,q_repos))
T04_repos=simplify(subs(T04,q,q_repos))
T05_repos=simplify(subs(T05,q,q_repos))
T06_repos=simplify(subs(T06,q,q_repos))
error('calculer T01..T06 et analyser la configuration au repos avant de passer a la suite');
%--------------------------------------------------------
% 1.2 Jacobiennes en position de points lies aux reperes 1 a 6
% (modele de force statique, modele dynamique )
%--------------------------------------------------------
disp('question 1.2.2');
syms px py pz; % coordonnees fixes des points Pi dans leur propre repere i
P01=a_completer;J0P1=a_completer; % a completer, jacobienne de 0P1 / q , P1= point de coordonnees [px;py;pz] fixes dans Repere 1
P02=a_completer;J0P2=a_completer; % a completer, jacobienne de 0P2 / q , P2= point de coordonnees [px;py;pz] fixes dans Repere 2
P03=a_completer;J0P3=a_completer; % a completer, jacobienne de 0P3 / q , P3= point de coordonnees [px;py;pz] fixes dans Repere 3
P04=a_completer;J0P4=a_completer; % a completer, jacobienne de 0P4 / q , P4= point de coordonnees [px;py;pz] fixes dans Repere 4
P05=a_completer;J0P5=a_completer; % a completer, jacobienne de 0P5 / q , P5= point de coordonnees [px;py;pz] fixes dans Repere 5
P06=a_completer;J0P6=a_completer; % a completer, jacobienne de 0P6 / q , P6= point de coordonnees [px;py;pz] fixes dans Repere 6
% fcts matlab generant les jacobiennes
func_J0P1=matlabFunction(J0P1,'File','clcJ0P1','Vars',[q1;q2;q3;q4;q5;q6;d1;a2;a3;d4;d5;d6;px;py;pz]);
func_J0P2=matlabFunction(J0P2,'File','clcJ0P2','Vars',[q1;q2;q3;q4;q5;q6;d1;a2;a3;d4;d5;d6;px;py;pz]);
func_J0P3=matlabFunction(J0P3,'File','clcJ0P3','Vars',[q1;q2;q3;q4;q5;q6;d1;a2;a3;d4;d5;d6;px;py;pz]);
func_J0P4=matlabFunction(J0P4,'File','clcJ0P4','Vars',[q1;q2;q3;q4;q5;q6;d1;a2;a3;d4;d5;d6;px;py;pz]);
func_J0P5=matlabFunction(J0P5,'File','clcJ0P5','Vars',[q1;q2;q3;q4;q5;q6;d1;a2;a3;d4;d5;d6;px;py;pz]);
func_J0P6=matlabFunction(J0P6,'File','clcJ0P6','Vars',[q1;q2;q3;q4;q5;q6;d1;a2;a3;d4;d5;d6;px;py;pz]);
%---------------------------------------------
% 1.3.1 calcul direct de la jacobienne en orientation
% on peut en deduire d 0WRj/R0 / dvqi = d 0uRj/R0 /dqi en selectionnant les composantes adaptees de dR06/dqi.R60
%---------------------------------------------
disp('question 1.3.1');
R01=get_R(T01);R10=R01.';
R02=get_R(T02);R20=R02.';
R03=get_R(T03);R30=R03.';
R04=get_R(T04);R40=R04.';
R05=get_R(T05);R50=R05.';
R06=get_R(T06);R60=R06.';
q=[q1;q2;q3;q4;q5;q6];
for i=1:length(q),
   qi=q(i);
  % pour chaque qi on calcule [d0Rj/dqi] . jR0 = [d S(0wRj/R0) ]/dvqi  = [d S(0uRj/R0) ]/dqi
  dS0u1dqi=a_completer; % exp tres compliqueee, difficile a simplifier
  dS0u2dqi=a_completer; % exp tres compliqueee, difficile a simplifier
  dS0u3dqi=a_completer; % exp tres compliqueee, difficile a simplifier
  dS0u4dqi=a_completer; % exp tres compliqueee, difficile a simplifier
  dS0u5dqi=a_completer; % exp tres compliqueee, difficile a simplifier
  dS0u6dqi=a_completer; % exp tres compliqueee, difficile a simplifier
  % on en deduit [ d uRj/R0 ] / dqi = [ d wRj/R0 ] / dvqi en selectionnant les bonnes composantes
  du01dqi=a_completer;
  du02dqi=a_completer;
  du03dqi=a_completer;
  du04dqi=a_completer;
  du05dqi=a_completer;
  du06dqi=a_completer;
  % on range du0j/dqi dans la i eme colonne de la Jacobienne en orientation
  J0U1(:,i)=du01dqi;
  J0U2(:,i)=du02dqi;
  J0U3(:,i)=du03dqi;
  J0U4(:,i)=du04dqi;
  J0U5(:,i)=du05dqi;
  J0U6(:,i)=du06dqi;
end
% generation fct matlab calculant les jacobiennes des origines exprimees
% dans le repere 0
func_J0Ui=matlabFunction(J0U1,J0U2,J0U3,J0U4,J0U5,J0U6,'File','clcJ0Ui','Vars',[q1;q2;q3;q4;q5;q6;d1;a2;a3;d4;d5;d6]);
%---------------------------------------------------------------------------------
% 1.3.2 calcul de la jacobienne en orientation avec denavit Hartenberg
% on peut en deduire d 0Uj dqi = 0zi-1 ( ce qui est beaucoup plus simple)
%------------------------------------------------------------------------------
disp('question 1.3.2, jacobiennes avec Denavit Hartenberg');
oz0=a_completer;J0U1_dh=a_completer;
oz1=a_completer;J0U2_dh=a_completer;
oz2=a_completer;J0U3_dh=a_completer;
oz3=a_completer;J0U4_dh=a_completer;
oz4=a_completer;J0U5_dh=a_completer;
oz5=a_completer;J0U6_dh=a_completer;
% generation fct matlab
func_J0Ui_dh=matlabFunction(J0U1_dh,J0U2_dh,J0U3_dh,J0U4_dh,J0U5_dh,J0U6_dh,'File','clcJ0Ui_dh','Vars',[q1;q2;q3;q4;q5;q6;d1;a2;a3;d4;d5;d6]);

