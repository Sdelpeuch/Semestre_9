%-------------------------------------------------------------------
% fonction renvoyant l'angle le plus proche de 0 modulo 2 pi
%-------------------------------------------------------------------------
  function a0=get_arg_nearest_zero(a)
    q= round(a/(2*pi));
    a0=a-2*pi*q;
  end
  