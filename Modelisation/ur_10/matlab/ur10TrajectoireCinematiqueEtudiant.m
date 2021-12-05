%--------------------------------------------------------
% MODELES GEOMETRIQUES DIRECT ET INVERSE D'UN ROBOT UR10
%--------------------------------------------------------

clear all;close all;more off;clc;
USE_OCTAVE=exist('OCTAVE_VERSION')>0;
if USE_OCTAVE
    % rien a faire, code compatible Matlab / Octave
end
errMax=0.00001;tolSvd=0.001;
d1=0.128;a2=0.612;a3=0.5722;d4=0.1639;d5=0.1157;d6=0.1047;
%---------------------------------
% interpolation de trajectoires
%------------------------------------
%-----------------------------------------------------------------
% trajectoite operationnelle = tableau des points a atteindre pts(i,:) = [O06.',U06.']
%----------------------------------------------------------------
pts=[];% aucun point pour le moment
%--------------------------------------------------------
% le point de depart est le point de repos, de coordonnees articulaires connues
%-------------------------------------
q1=90*pi/180;q2=90*pi/180;q3=0*pi/180;q4=90*pi/180;q5=0*pi/180;q6=0*pi/180;
q=[q1;q2;q3;q4;q5;q6];
traj_q=q.';% premier point de la trajectoire articulaire
% coordonnees operationnelles correspondantes
[T01,T12,T23,T34,T45,T56]=MGD_ur10(q(1),q(2),q(3),q(4),q(5),q(6),d1,a2,a3,d4,d5,d6);
T04=T01*T12*T23*T34;O04=get_O(T04);
T05=T01*T12*T23*T34*T45;O05=get_O(T05);
T06d=T01*T12*T23*T34*T45*T56;
O06d=get_O(T06d);R06d=get_R(T06d);U06d=get_u(R06d);P=[O06d,U06d].';
pts=[ O06d.',U06d.']; % premier point de la trajectoire operationnelle
%-----------------------------------------------------------------
% A MODIFIER : tableau des points a atteindre pts(i,:) = [O06.',U06.']
%----------------------------------------------------------------
O06=rand(3,1);U06=rand(3,1)*pi ; pts=[pts;[O06.',U06.']];
O06=rand(3,1);U06=rand(3,1)*pi ; pts=[pts;[O06.',U06.']];
O06=rand(3,1);U06=rand(3,1)*pi ; pts=[pts;[O06.',U06.']];
%-----------------------------------------------------------------
%  boucle de suivi de trajectoire
%----------------------------------------------------------------
[nb_pts,tmp]=size(pts);%nb_pts=1;
for i_pt=2:nb_pts
    % coordonnees articulaires et operationnelles du point precedent
    q=traj_q(i_pt-1,:).';
    [T01,T12,T23,T34,T45,T56]=MGD_ur10(q(1),q(2),q(3),q(4),q(5),q(6),d1,a2,a3,d4,d5,d6);
    T06d=T01*T12*T23*T34*T45*T56;
    O06d=get_O(T06d);R06d=get_R(T06d);U06d=get_u(R06d);
    % coordonnees operationnelles du point a atteindre
    O06f=pts(i_pt,1:3).'; % O06 final
    U06f=pts(i_pt,4:6).'; % R06 final
    T06f=get_rot_u(U06f);R06f=get_R(T06f);
    Pf=[O06f;U06f];
    %--------------------------------------------
    % A COMPLETER : trouver dq tel qu'on atteigne ce point  en q+dq, avec une erreur suffisamment petite
    % il sera probablement necessaire de decouper le segment en ''petits deplacements''
    dq=zeros(6,1); % A REMPLACER PAR VOTRE ALGORITHME
    %--------------------------------------------
    % NE RIEN MODIFIER APRES CETTE LIGNE
    %---------------------------------------------
    % stockage de q+dq dans traj_q
    traj_q=[traj_q; (q+dq).'];
end % for i_pt=2:nb_pts
%------------------------------------------------------------------------------
% AFFICHAGE DES RESULTATS DIRECTEMENT EXPLOITABLE AVEC V-REP
%-------------------------------------------------------------------------------
[nb_pts,tmp]=size(traj_q);
for i_pt=1:nb_pts
    msg=sprintf('-------------------------------\n--point numero  %d\n-------------------------------------',i_pt);
    disp(msg);
    qi=traj_q(i_pt,:).';
    qideg=qi*180/pi;
    msg=sprintf('targetPos%d={(%.2f-90)*math.pi/180,(%.2f-90)*math.pi/180,%.2f*math.pi/180,(%.2f-90)*math.pi/180,%.2f*math.pi/180,%.2f*math.pi/180}'...
        ,i_pt,qideg(1),qideg(2),qideg(3),qideg(4),qideg(5),qideg(6)); % sprinf fonctionne comme le sprintf du langage C, permet de fabriquer des affichages formates
        disp(msg);
    msg=sprintf('sim.rmlMoveToJointPositions(jointHandles,-1,currentVel,currentAccel,maxVel,maxAccel,maxJerk,targetPos%d,targetVel)',i_pt);
    disp(msg);

end % for i_pt=1:nb_pts


