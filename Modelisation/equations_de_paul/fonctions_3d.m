[x, y, z] = cylinder (10:-1:0, 50);
surf (x, y, z);
title ("a cone");

[x, y, z] = sphere (40);
surf (3*x, 3*y, 3*z);
axis equal;
title ("sphere of radius 3");