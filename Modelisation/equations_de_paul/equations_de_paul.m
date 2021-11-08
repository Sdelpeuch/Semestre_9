clear all;close all;
disp('verification des equations de Paul de type 1 a 8');
  %verif type 1
    ST1=solve_type_1(2,1)
  %verif type 2
    ST2=solve_type_2(2,1,1)
  %verif type 3
    X1=2;Y1=1;Z1=1;
    ST21=solve_type_2(X1,Y1,Z1)
    alpha=1;
    K2=3;
    A1=ST2.Ai(2);
    X2=K2*cos(alpha);
    Y2=K2*sin(alpha);
    Z2=K2*sin(alpha+A1);
    ST22=solve_type_2(X2,Y2,Z2);
    ST3=solve_type_3(X1,Y1,Z1,X2,Y2,Z2)
  % verif type 4
    X1T4=1;Y1T4=1;X2T4=1;Y2T4=2;
    ST4=solve_type_4(X1T4,Y1T4,X2T4,Y2T4)
  % exemple  type 5
    X1=1;Y1=1;Z1=1;
    X2=2;Y2=-1;Z2=1;
    S5=solve_type_5(X1,Y1,Z1,X2,Y2,Z2)
    if ( S5.well_posed==0 ) 
      error('l equation est mal posée !..');
    end
    disp( strcat('les ',num2str(S5.nb_sols),' solutions de l equation : ' , S5.name ,' sont '));
    for i=1:S5.nb_sols,
      Ai=S5.Ai(i);
      Rj=S5.Rj(i);
      disp(strcat('solution ',num2str(i),' [ Ai = ' , num2str(Ai) , ', Rj =' , num2str(Rj) ,']'));
    end
  % verif types 6,7,8
    XT2=2;YT2=1;ZT2=1;
    X=0.2;
    Y=sqrt(1-X^2);
    Z2=XT2*sqrt(X^2+Y^2)/2;
    Z1=YT2*sqrt(X^2+Y^2)/2;
    W=sqrt((X^2+Y^2)*(1+ZT2));
    W1=W/sqrt(2);W2=-W/sqrt(2);
    ST6=solve_type_6(W,X,Y,Z1,Z2)
    ST7=solve_type_7(W1,W2,X,Y,Z1,Z2)
    ST8=solve_type_8(X,Y,Z1,Z2)
