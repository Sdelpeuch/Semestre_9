%--------------------------------------------------------
% JACOBIENNES ET MODELES CINEMATIQUES DIRECT ET INVERSE D'Un ROBOT UR10
%--------------------------------------------------------

clear all;close all;more off;clc;
USE_OCTAVE=exist('OCTAVE_VERSION')>0;
if USE_OCTAVE
    % rien a faire, code compatible Matlab / Octave
end
% parametres du robot
d1=0.128;a2=0.612;a3=0.5722;d4=0.1639;d5=0.1157;d6=0.1047;

%---------------------------------------------------
% 2.1-verification correspondances des jacobiennes
%---------------------------------------------------
disp('--partie 2.1, verification des jacobiennes en orientation(vous n avez rien a ecrire pour cette partie)');
q=2*pi*rand(6,1);% q, vecteurs aleatoires 6X1 a dsp uniforme entre 0 et 2pi
% calculer les jacobiennes  J0U1,J0U2,J0U3,J0U4,J0U5,JU06
[J0U1,J0U2,J0U3,J0U4,J0U5,JU06] = clcJ0Ui(q(1),q(2),q(3),q(4),q(5),q(6),d1,a2,a3,d4,d5,d6);
% calculer les jacobiennes  J0U1_dh,J0U2_dh,J0U3_dh,J0U4_dh,J0U5_dh,JU06_dh
[J0U1_dh,J0U2_dh,J0U3_dh,J0U4_dh,J0U5_dh,JU06_dh] = clcJ0Ui_dh(q(1),q(2),q(3),q(4),q(5),q(6),d1,a2,a3,d4,d5,d6);
% verification des erreurs entre les 2 expressions ( direct, Denavit Hartenberg)
err1=max(max(abs(J0U1_dh-J0U1)));
err2=max(max(abs(J0U2_dh-J0U2)));
err3=max(max(abs(J0U3_dh-J0U3)));
err4=max(max(abs(J0U4_dh-J0U4)));
err5=max(max(abs(J0U5_dh-J0U5)));
err6=max(max(abs(JU06_dh-JU06)));
err_jacobienne=max ([err1;err2;err3;err4;err5;err6]);
if (err_jacobienne>1e-10),
    err_jac06=[err1;err2;err3;err4;err5;err6]
    error('probleme dans le calcul des jacobiennes en orientation');
else    
    disp('calcul des jacobiennes en orientation OK');
end
%---------------------------------------------------
% 2.2-verification du MCD en position a l'extremite du repere 6
%---------------------------------------------------
disp('--partie 2.2 verification du MCD a la position 0O6= extremite du robot');
q =2*pi*rand(6,1);% q, vecteurs aleatoires 6X1 a dsp uniforme entre 0 et 2pi
dq=1*2*pi/180*rand(6,1); % dq : vecteur aleatoires 6X1 de petites variations
% 22a - calculer T06 (q), et en deduire O06(q)
T06_q=a_completer;
O06_q=a_completer;
% 22b - calculer T06 (q+dq) , et en deduire O06(q+dq)
qdq=q+dq;
T06_qdq=a_completer;
O06_qdq=a_completer;
% 22c - calculer l'ecart reel correspondant O06(q+dq-O06(q)
ecart_O06_reel=a_completer;
% 22d - utiliser la jacobienne (au point q), du point P06 correspondant a O06 pour determiner le meme ecart
J0O6_q = a_completer;% c
ecart_O06_jac=a_completer;
% 22e - affichage des erreurs absoluee et relative entre les 2 ecarts
err_abs=norm(ecart_O06_reel-ecart_O06_jac);
err_rel=norm(ecart_O06_reel-ecart_O06_jac)/norm(ecart_O06_reel);
msg=sprintf('  2.2 : |ecart_reel                                               |=%.3e',norm(ecart_O06_reel)); disp(msg);
msg=sprintf('  2.2 : erreur absolue  = |ecart_reel - ecart estime              |=%.3e',err_abs);disp(msg);
msg=sprintf('  2.2 : erreur relative = |ecart_reel - ecart estimee|/|ecart reel|=%.3e',err_rel);disp(msg);

%---------------------------------------------------
% 2.3-verification du MCD en orientation pour le repere 6
%---------------------------------------------------
disp('--partie 2.3 verification du MCD en orientation pour le repere 6: extremite du robot');
% 23a - connaissant T06 (q),en deduire R06(q), u06_q
R06_q=a_completer;
u06_q=a_completer;
% 23b - connaissant T06_qdq=T06 (q+dq) , en deduire R06(q+dq)
R06_qdq=a_completer;
u06_qdq=a_completer;
% 23c - determiner la matrice de rotation R(d0u6) , telle que R06(q+dq) = R0(d0u6).R06(q)
Rd0u6=a_completer;
% 23d on en deduit le vecteur angle-axe correspondant
du06_reel=a_completer;
% A NE PAS CONFONDRE AVEC LA LIGNE SUIVANTE: FAUX !!! A COMMENTER POUR VERSION DEFINITIVE
du06_reel=get_u(R06_qdq)-get_u(R06_q);
% 22d - utiliser la jacobienne en orientation pour determiner le vecteur angle-axe du06
JU06_q = a_completer;
du06_jac=a_completer;
% 22e - affichage des erreurs absoluee et relative entre les 2 ecarts
err_abs=norm(du06_reel-du06_jac);
err_rel=norm(du06_reel-du06_jac)/norm(du06_reel);
msg=sprintf('  2.3 : |ecart_reel                                               |=%.3e',norm(du06_reel)); disp(msg);
msg=sprintf('  2.3 : erreur absolue  = |ecart_reel - ecart estime              |=%.3e',err_abs);disp(msg);
msg=sprintf('  2.3 : erreur relative = |ecart_reel - ecart estimee|/|ecart reel|=%.3e',err_rel);disp(msg);
%-------------------------------------------------------------------------
% 3 Modele cinematique inverse (la configuration initiale est imposee)
%--------------------------------------------------------------------------
disp('--partie 3 modele cinematique inverse');
q=[80;70;10;70;10;20]*pi/180;% configuration initiale imposee
JU06_q = a_completer;% a recalculer car on a change de pt de fonctionnement
JO06_q = a_completer;% a recalculer car on a change de pt de fonctionnement
%---------------------------------------------
% 3.1 Modele cinematique inverse en position
%---------------------------------------------
disp('--partie 3.1 modele cinematique inverse en position ');
% definition de dO06 voulu
dO06_voulu=[0.01;0;0];
% calcul position initiale O06(q)
[T01,T12,T23,T34,T45,T56] = MGD_ur10(q(1),q(2),q(3),q(4),q(5),q(6),d1,a2,a3,d4,d5,d6);
T06_q=T01*T12*T23*T34*T45*T56;
O06_q=get_O(T06_q);
% calcul position voulue
O06_voulu=O06_q+dO06_voulu;
% calcul de dq( a adapter )
dq=a_completer;
% calcul position obtenue O06(q+dq)
qdq=q+dq;
[T01,T12,T23,T34,T45,T56] = MGD_ur10(qdq(1),qdq(2),qdq(3),qdq(4),qdq(5),qdq(6),d1,a2,a3,d4,d5,d6);
T06_qdq=T01*T12*T23*T34*T45*T56;
O06_obtenu=get_O(T06_qdq);
% calcul chemin restant a parcourir
O06_restant=a_competer;
% affichage erreur absolue entre position voulue et obtenue
err_abs_31=norm(O06_restant)
%---------------------------------------------
% 3.2 Modele cinematique inverse en orientation
%---------------------------------------------
disp('--partie 3.2 modele cinematique inverse en orientation ');
% definition de dU06 voulu, et de la rotation associee
dU06_voulu=[0.01;0;0];% rotation de 0.01 radian /x0
% calcul orientation initiale R06(q)
[T01,T12,T23,T34,T45,T56] = MGD_ur10(q(1),q(2),q(3),q(4),q(5),q(6),d1,a2,a3,d4,d5,d6);
T06_q=T01*T12*T23*T34*T45*T56;R06_q=get_R(T06_q);
% calcul orientation R06 voulu
Tdu06=get_rot_u(dU06_voulu);RdU06=get_R(Tdu06);
R06_voulu=a_completer;
% calcul de dq ( a adapter )
dq=a_completer;
% calcul orientation obtenue R06(q+dq)
qdq=q+dq;
[T01,T12,T23,T34,T45,T56] = MGD_ur10(qdq(1),qdq(2),qdq(3),qdq(4),qdq(5),qdq(6),d1,a2,a3,d4,d5,d6);
T06_qdq=T01*T12*T23*T34*T45*T56;
R06_obtenu=get_R(T06_qdq);
% calcul du vecteur angle axe correspondant au chemin restant a parcourir
dU06_restant=a_completer;% attention : dU06_restant n'est pas egal a u06_voulu-u06_obtenu
% affichage erreur absolue entre les variations d'orientation voulue et obtenue
err_abs_32=norm(dU06_restant)
%---------------------------------------------
% 3.3 Modele cinematique inverse en position et en orientation
%---------------------------------------------
disp('--partie 3.3 modele cinematique inverse en position et en orientation');
delta_voulu=[dO06_voulu;dU06_voulu]; % [d0O6;dU06]
% calcul position O06(q) et rotation R06(q) initiales
[T01,T12,T23,T34,T45,T56] = MGD_ur10(q(1),q(2),q(3),q(4),q(5),q(6),d1,a2,a3,d4,d5,d6);
T06_q=T01*T12*T23*T34*T45*T56;
O06_q=get_O(T06_q);
R06_q=get_R(T06_q);
% calcul position et orientation voulues O06_voulu, R06_voulu 
O06_voulu=O06_q+dO06_voulu;
Tdu06=get_rot_u(dU06_voulu);RdU06=get_R(Tdu06);
R06_voulu=a_completer;
% calcul de dq
dq=a_completer;
% calcul position O06(q+dq) et rotation R06(q+dq) obtenues
qdq=q+dq;
[T01,T12,T23,T34,T45,T56] = MGD_ur10(qdq(1),qdq(2),qdq(3),qdq(4),qdq(5),qdq(6),d1,a2,a3,d4,d5,d6);
T06_qdq=T01*T12*T23*T34*T45*T56;
O06_obtenu=get_O(T06_qdq);
R06_obtenu=get_R(T06_qdq);
% calcul chemin restant a parcourir 
O06_restant=O06_voulu- O06_obtenu;
dU06_restant=a_completer;
% affichage norme des erreurs de position et d'orientation correspondantes
err_position_33=norm(O06_restant)
err_orient_33=norm(dU06_restant)
%----------------------------------------
% 3.3- (optionnel) iterations pour err < 1 e-6
%----------------------------------------
while ((err_position_33>1e-6)|(err_orient_33>1e-6)),
    % optionnel, a adapter
    % pour le moment, neutralisation => erreurs =0
    err_position_33=norm(O06_restant)*0 ;
    err_orient_33=norm(dU06_restant)*0 ;       
end
%----------------------------------------
% 4 modele de force statique
%----------------------------------------
% proposer des configurations et des forces ou moments illustrant le modele
% de force statique.



