function mat = get_dh(th, a, d, al)
    mat = get_rot_z(th) * get_trans(0, 0, d) * get_rot_x(al) * get_trans(a, 0, 0);
end
