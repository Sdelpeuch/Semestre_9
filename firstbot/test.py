import pypot.dynamixel

def move(left_speed, right_speed):
    """Set speed for motors with pypot.dynamixel library"""
    ports = pypot.dynamixel.get_available_ports()
    if not ports:
        raise IOError('No port found!')

    print('Connecting on the first available port:', ports[0])
    dxl_io = pypot.dynamixel.DxlIO(ports[0])
    motors = dxl_io.get_available_motor_ids()
    if not motors:
        raise IOError('No motor found!')

    print('Moving motor on the bus with id:', motors[0])
    dxl_io.set_moving_speed({motors[0]: left_speed})
    dxl_io.set_moving_speed({motors[1]: right_speed})

def test_move():
    """Test move function"""
    move(100, 100)

