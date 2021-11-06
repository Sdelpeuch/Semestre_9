# Firstbot Team 3

## CAD

[OnShape Model](https://cad.onshape.com/documents/0fa4f0b5591305ec041415e5/w/a094658137fcb0b1999fc191/e/d4e1789a509d89ffa6afe0d1)

## Software

The software is organised in different classes allowing to control each part of the robot. Two classes allow to control the physical parts of the robot and the two others allow to assign a behaviour to the robot.

The **Detection** class allows to communicate with the camera, it also allows to apply filters on the image (using the HSV convention) allowing to determine the contours of the lines of a certain colour.

The **Motors** class is used to initialise and communicate with the dynamixel servo motors, it also provides a set of simple prototypes to control the two motors.

The **Robot** class defines the behaviour needed to follow lines globally by implementing mainly a PID.

The **Odometry** class implements the calculations needed to track the position of the robot relative to its home position.

## Circuit 

[Video](circuit.mp4)
